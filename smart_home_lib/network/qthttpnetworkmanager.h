#ifndef QTHTTPNETWORKMANAGER_H
#define QTHTTPNETWORKMANAGER_H

#include "networkmanager.h"
#include <QList>
#include <QMap>
#include <QObject>
#include <QPair>
#include <QSharedPointer>
#include <QUrl>

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

#include <functional>

#include "qhttpserver.hpp"
#include "qhttpserverresponse.hpp"
#include "qhttpserverrequest.hpp"

#include "connection.h"
#include "requestmessage.h"
#include "responsemessage.h"

namespace network {

/**
 * @brief The QtHttpNetworkManager class implements the NetworkManager interface
 * over the lightweight QHttpServer and Qt's client networking API.
 *
 * This is the class you will need to instantiate, but you do NOT need to modify it.
 * If there appear to be any errors, let me (Matt Selway) know.
 */
class QtHttpNetworkManager : public NetworkManager
{
  Q_OBJECT
public:
  QtHttpNetworkManager(QObject *parent = nullptr);
  ~QtHttpNetworkManager() override;

  // NetworkManager interface, see NetworkManager for documentation.
public:
  void start(const QUrl &bindAddress = QUrl{"http://localhost"},
             const QList<quint16> &portRange = {80, 8101, 8102, 8103} ) override;
  void stop() override;
  const QUrl &boundAdress() const override;
  bool isRunning() const override;
  bool addConnection(const QString &id, const QUrl &targetAddress) override;
  void removeConnection(const QString &id) override;
  void sendRequest(const QString &id, const RequestMessage &request) override;
  QSharedPointer<ResponseMessage> sendRequestWait(const QString &id, const RequestMessage &request) override;
  void sendResponse(QSharedPointer<const RequestMessage> request, const ResponseMessage &response) override;
  void registerHandler(const QPair<QString, HttpMethod> &path, const RequestGenerator &requestHandler) override;
  void registerHandler(const QPair<QString, HttpMethod> &path, const ResponseGenerator &responseHandler) override;
  void removePath(const QPair<QString, HttpMethod> &path) override;

private:
  qhttp::server::QHttpServer* _server;
  QNetworkAccessManager* _client;
  QUrl _boundAddress;
  QMap<QString, Connection> _connections;
  QMap<QSharedPointer<const RequestMessage>, qhttp::server::QHttpResponse *> _requestsBeingProcessed;
  QMap<QPair<QString, HttpMethod>, RequestGenerator> _requestHandlers;
  QMap<QPair<QString, HttpMethod>, ResponseGenerator> _responseHandlers;

  QHostAddress resolveAddressFromUrl(const QUrl &targetAddress);
  QNetworkReply* doRequest(QNetworkRequest &qRequest, const RequestMessage& request);
  QNetworkRequest prepareQRequest(const QString &id, const RequestMessage &request);
  const RequestGenerator *findRequestHandler(QString path, HttpMethod method);
  const ResponseGenerator *findResponseHandler(QString path, HttpMethod method);

  constexpr static const QNetworkRequest::Attribute METHOD_ATTRIBUTE = QNetworkRequest::Attribute::User;

private slots:
  void qhttpHandler(qhttp::server::QHttpRequest *qRequest, qhttp::server::QHttpResponse *qResponse);
  void qreplyHandler();

};

} // namespace network

#endif // QTHTTPNETWORKMANAGER_H
