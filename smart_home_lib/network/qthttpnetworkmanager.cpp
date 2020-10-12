#include "qthttpnetworkmanager.h"

#include <QDebug>
#include <QEventLoop>
#include <QHostAddress>
#include <QHostInfo>
#include <QSharedPointer>
#include <QTimer>

#include <algorithm>

#include "qhttpserver.hpp"
#include "qhttpserverresponse.hpp"
#include "qhttpserverrequest.hpp"

using namespace network;
using qhttp::server::QHttpServer;
using qhttp::server::QHttpRequest;
using qhttp::server::QHttpResponse;

QtHttpNetworkManager::QtHttpNetworkManager(QObject *parent)
  : NetworkManager{parent}, _server{new qhttp::server::QHttpServer{this}},
    _client{new QNetworkAccessManager{}}, _boundAddress{}, _connections{},
    _requestsBeingProcessed{}, _requestHandlers{}, _responseHandlers{}
{
  // Connect the server up, we will only be notified after it successfully starts listening
  QObject::connect(_server, &QHttpServer::newRequest, this,  &QtHttpNetworkManager::qhttpHandler);
}

QtHttpNetworkManager::~QtHttpNetworkManager()
{
  _client->deleteLater();
  stop();
}


void QtHttpNetworkManager::start(const QUrl &bindAddress, const QList<quint16> &portRange)
{
  QHostAddress address{resolveAddressFromUrl(bindAddress)};
  quint16 usedPort{};

  for (auto port{portRange.begin()}; not _server->isListening() and port != portRange.end(); ++port) {
    usedPort = *port;
    _server->listen(address, usedPort);
  }

  if (_server->isListening()) {
    _boundAddress = QStringLiteral("http://%1:%2/").arg(address.toString()).arg(usedPort);
    qDebug() << "Server listening on " << _boundAddress;
  }
  else {
    _boundAddress.clear();
    qDebug() << "Unable to start QHttpServer.";
  }
}


void QtHttpNetworkManager::stop()
{
  if (isRunning()) _server->stopListening();
  _boundAddress.clear();
}


const QUrl &QtHttpNetworkManager::boundAdress() const
{
  return _boundAddress;
}


bool QtHttpNetworkManager::isRunning() const
{
  return _server and _server->isListening();
}


bool QtHttpNetworkManager::addConnection(const QString &id, const QUrl &targetAddress)
{
  if (_connections.find(id) != _connections.end()) return false;

  QHostAddress address{resolveAddressFromUrl(targetAddress)};
  quint16 port{targetAddress.port() < 0 ? static_cast<quint16>(80) : static_cast<quint16>(targetAddress.port())};

  // Resolution failed, give up
  if (address.isNull()) return false;

  qDebug() << "Adding connection: " << id << " @ " << address << ":" << port;

  _connections.insert(id, {id, address, port});
  return true;
}


void QtHttpNetworkManager::removeConnection(const QString &id)
{
  _connections.remove(id);
}


void QtHttpNetworkManager::sendRequest(const QString &id, const network::RequestMessage &request)
{
  if (not _connections.contains(id)) return;

  QNetworkRequest qRequest{prepareQRequest(id, request)};

  // Send the request and get the placeholder reply object.
  QNetworkReply *qReply{doRequest(qRequest, request)};

  // Connect a slot to the reply so we can handle the responses
  QObject::connect(qReply, &QNetworkReply::finished, this, &QtHttpNetworkManager::qreplyHandler);
}

QSharedPointer<ResponseMessage> network::QtHttpNetworkManager::sendRequestWait(const QString &id, const RequestMessage &request)
{
  if (not _connections.contains(id)) return nullptr;

  QNetworkRequest qRequest{prepareQRequest(id, request)};

  // Send the request and get the placeholder reply object.
  QNetworkReply *reply{doRequest(qRequest, request)};

//  qDebug() << "Request sent";

  // This is a bit of a hack to make the QNetworkAccessManager of Qt
  // operate synchronously instead of its default ansynchronous method
  // Note: the timer is a quick hack to timeout the request, I'm sure
  // the Qt framework must handle that more nicely, but I cannot see it.
  QEventLoop syncLoop{};
  QObject::connect(reply, &QNetworkReply::finished, &syncLoop, &QEventLoop::quit);
  QTimer::singleShot(1000, reply, &QNetworkReply::abort);
  syncLoop.exec();

//  qDebug() << "Exited sync loop";
  if (not reply->isReadable()) {
    qDebug() << "request cancelled due to timeout    " << reply->errorString();
    reply->deleteLater();
    return QSharedPointer<ResponseMessage>::create(reply->url(), StatusCode::SERVER_ERROR);
  }

  // Retrieve the data once (we use in the logging below)
  QByteArray data{reply->readAll()};

  // Convert the way status is reported by the Qt networking stuff into our enum
  StatusCode status{ResponseMessage::statusCodeFrom(reply)};

  // Recover the original HTTP method
  HttpMethod method{reply->request().attribute(METHOD_ATTRIBUTE).value<HttpMethod>()};

  qDebug() << "Received synchronous reponse: " << status << endl
           << "  from: " << reply->url() << "  method: " << method << endl
           << "  content: " << data;

  // Read the response using our messages
  const ResponseGenerator *generator{findResponseHandler(reply->url().path(), method)};

//  qDebug() << "retrieved response handler " << generator;

  QSharedPointer<ResponseMessage> response{};
  if (generator) {
    response.reset(generator->operator()(reply->url(), data));
  }
  else {
    response.reset(new ResponseMessage{reply->url(), status});
  }

//  qDebug() << "created response " << response;

  if (reply->error() != QNetworkReply::NoError) {
    qDebug() << "The request failed " << reply->url() << ": " << reply->errorString();
  }

  reply->deleteLater();

  return response;
}

void QtHttpNetworkManager::sendResponse(QSharedPointer<const RequestMessage> request, const network::ResponseMessage &response)
{
  // Remove it from the map so that the request will be deallocated
  QHttpResponse *const qResponse{_requestsBeingProcessed.take(request)};
  if (not qResponse) return;

  // Configure and send the QHttp response using our response message.
  // response status code: e.g., 200 OK
  qResponse->setStatusCode(response.qhttpStatusCode());

  // HTTP headers, e.g., Content-Type: text/plain
  for (auto k : response.headers().keys()) {
    qResponse->addHeader(k.toUtf8(), response[k].toUtf8());
  }

  // Specify the Content-Length, it is good practice, and necessary if we
  // were usign Keep-Alive.
  qResponse->addHeaderValue("Content-Length", response.data().size());

  // Response body data
  qResponse->end(response.data());
}

void QtHttpNetworkManager::registerHandler(const QPair<QString, HttpMethod> &path, const RequestGenerator &requestHandler)
{
  _requestHandlers.remove(path);
  _requestHandlers.insert(path, requestHandler);

  if (path.first == "*") {
    QList<HttpMethod> methods{GET, PUT, POST, DELETE};
    methods.removeOne(path.second);
    for (auto m : methods) {
      _requestHandlers.remove({path.first, m});
    }
  }
}

void QtHttpNetworkManager::registerHandler(const QPair<QString, HttpMethod> &path, const ResponseGenerator &responseHandler)
{
  _responseHandlers.remove(path);
  _responseHandlers.insert(path, responseHandler);

  if (path.first == "*") {
    QList<HttpMethod> methods{GET, PUT, POST, DELETE};
    methods.removeOne(path.second);
    for (auto m : methods) {
      _responseHandlers.remove({path.first, m});
    }
  }
}

void QtHttpNetworkManager::removePath(const QPair<QString, HttpMethod> &path)
{
  _requestHandlers.remove(path);
  _responseHandlers.remove(path);

  if (path.first == "*") {
    QList<HttpMethod> methods{GET, PUT, POST, DELETE};
    for (auto m : methods) {
      _requestHandlers.remove({path.first, m});
      _responseHandlers.remove({path.first, m});
    }
  }
}

QHostAddress QtHttpNetworkManager::resolveAddressFromUrl(const QUrl &targetAddress)
{
  // Check if it is already an IP address
  QHostAddress address{targetAddress.host()};
  if (not address.isNull()) return address;

  // Now try resolving
  QHostInfo hostInfo{QHostInfo::fromName(targetAddress.host())};
  if (hostInfo.error() or hostInfo.addresses().isEmpty()) {
    qDebug() << "Failed to resolve " << hostInfo.errorString();
    return QHostAddress{};
  }

  auto addresses{hostInfo.addresses()};
  qDebug() << "Domain name resolution successful: " << addresses;

  // We prefer IPv4 if available
  auto ip4Address = std::find_if(addresses.begin(), addresses.end(), [] (const QHostAddress &a){
    return a.protocol() == QAbstractSocket::NetworkLayerProtocol::IPv4Protocol;
  });

  return ip4Address == addresses.end() ? addresses.first() : *ip4Address;
}

QNetworkReply *QtHttpNetworkManager::doRequest(QNetworkRequest& qRequest, const RequestMessage &request)
{
  switch (request.httpMethod()) {
  case GET:
    qDebug() << "GETing resource";
    qRequest.setAttribute(METHOD_ATTRIBUTE, QVariant::fromValue(HttpMethod::GET));
    return _client->get(qRequest);
  case PUT:
    qDebug() << "PUTing resource";
    qRequest.setAttribute(METHOD_ATTRIBUTE, QVariant::fromValue(HttpMethod::PUT));
    return _client->put(qRequest, request.data());
  case POST:
    qDebug() << "POSTing resource";
    qRequest.setAttribute(METHOD_ATTRIBUTE, QVariant::fromValue(HttpMethod::POST));
    return _client->post(qRequest, request.data());
  case DELETE:
    qDebug() << "DELETEing resource";
    qRequest.setAttribute(METHOD_ATTRIBUTE, QVariant::fromValue(HttpMethod::DELETE));
    return _client->deleteResource(qRequest);
  default:
    // should never happen
    qDebug() << "Warning: unexpected HTTP methods, have we expanded the allowable set? " << request.httpMethod();
    return nullptr;
  }
}

QNetworkRequest QtHttpNetworkManager::prepareQRequest(const QString &id, const RequestMessage &request)
{
  Connection connection{_connections[id]};

  // Construct the complete URL
  QUrl target{"http://localhost/"};
  target.setHost(connection.address.toString());
  target.setPort(connection.port);
  target.setPath(request.urlPath());
  request.applyQueryParameters(target);

  qDebug() << "Sending request to : " <<  target;

  // Set the url: e.g., http://localhost:8101/sayHello
  QNetworkRequest qRequest{target};

  // HTTP headers, e.g., Content-Type: text/plain
  for (auto k : request.headers().keys()) {
    qRequest.setRawHeader(k.toUtf8(), request[k].toUtf8());
  }

  return qRequest;
}

const NetworkManager::RequestGenerator *QtHttpNetworkManager::findRequestHandler(QString path, HttpMethod method)
{
  QPair<QString, HttpMethod> pathPair{path, method};
  auto result{_requestHandlers.find(pathPair)};

  if (result == _requestHandlers.end()) {
    // check for default
    auto keyMatch = std::find_if(_requestHandlers.keyBegin(), _requestHandlers.keyEnd(), [] (const QPair<QString, HttpMethod> &k) {
      return k.first == "*";
    });
    if (keyMatch != _requestHandlers.keyEnd()) return &(_requestHandlers[*keyMatch]);
  }

  return result == _requestHandlers.end() ? nullptr : &(*result);
}

const NetworkManager::ResponseGenerator *QtHttpNetworkManager::findResponseHandler(QString path, HttpMethod method)
{
  QPair<QString, HttpMethod> pathPair{path, method};
  auto result{_responseHandlers.find(pathPair)};

  if (result == _responseHandlers.end()) {
    // check for default
    auto keyMatch = std::find_if(_responseHandlers.keyBegin(), _responseHandlers.keyEnd(), [] (const QPair<QString, HttpMethod> &k) {
      return k.first == "*";
    });
    if (keyMatch != _responseHandlers.keyEnd()) return &(_responseHandlers[*keyMatch]);
  }

  return result == _responseHandlers.end() ? nullptr : &(*result);
}

void QtHttpNetworkManager::qhttpHandler(qhttp::server::QHttpRequest *qRequest, qhttp::server::QHttpResponse *qResponse)
{
  // This just logs some details so we can see what is going on.
  qDebug("Received Request\n  from %s:%d\n  method: %s url: %s",
         qRequest->remoteAddress().toUtf8().constData(),
         qRequest->remotePort(),
         qhttp::Stringify::toString(qRequest->method()),
         qPrintable(qRequest->url().toString()) );

  qRequest->collectData();

  qRequest->onEnd([qRequest, qResponse, this]() {
    qDebug() << "data? " << qRequest->collectedData();

    const RequestGenerator *generator{findRequestHandler(qRequest->url().path(), RequestMessage::httpMethodFrom(qRequest))};

    QSharedPointer<RequestMessage> request{};
    if (generator) {
      request.reset(generator->operator()(qRequest->url(), qRequest->collectedData()));
    }
    else {
      request.reset(new RequestMessage{qRequest->url(), RequestMessage::httpMethodFrom(qRequest)});
    }

    _requestsBeingProcessed.insert(request, qResponse);
    emit requestReceived(request);
  } );
}

void QtHttpNetworkManager::qreplyHandler()
{
  // Not 100% sure how this will hold up under load, but otherwis we cannot
  // differentiate the synchronous vs. asynchronous easily.
  QNetworkReply* reply{static_cast<QNetworkReply*>(sender())};

  // Retrieve the data once (we use in the logging below)
  QByteArray data{reply->readAll()};

  // Convert the way status is reported by the Qt networking stuff into our enum
  StatusCode status{ResponseMessage::statusCodeFrom(reply)};

  // Recover the original HTTP method
  HttpMethod method{reply->request().attribute(METHOD_ATTRIBUTE).value<HttpMethod>()};

  qDebug() << "Received reponse: " << status << endl
           << "  from: " << reply->url() << "  method: " << method << endl
           << "  content: " << data;

  // Read the response using our messages
  const ResponseGenerator *generator{findResponseHandler(reply->url().path(), method)};

//  qDebug() << "retrieved response handler " << generator;

  QSharedPointer<ResponseMessage> response{};
  if (generator) {
    response.reset(generator->operator()(reply->url(), data));
  }
  else {
    response.reset(new ResponseMessage{reply->url(), status});
  }

//  qDebug() << "created response " << response;

  if (reply->error() == QNetworkReply::NoError) {
    emit responseReceived(response);
  }
  else {
    qDebug() << "The request failed " << reply->url() << ": " << reply->errorString();
    emit responseReceived(response);
  }

  reply->deleteLater();
}
