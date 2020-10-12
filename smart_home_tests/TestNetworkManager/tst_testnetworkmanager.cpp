#include <QtTest>
#include <QCoreApplication>
#include <QList>
#include <QPair>
#include <QUrl>
#include <QScopedPointer>
#include <QSharedPointer>
#include <QMutex>

#include "network/qthttpnetworkmanager.h"
#include "requeststub.h"
#include "responsestub.h"
#include "fakemessagefactory.h"

using namespace network;

class TestNetworkManager : public QObject
{
  Q_OBJECT

public:
  TestNetworkManager();
  ~TestNetworkManager();

private slots:
  void test_localhostNameResolution_data();
  void test_localhostNameResolution();
  void test_serverStartup();
  void test_serverSimpleRequestResponse();
  void test_serverSynchronousRequestResponse();
  void test_serverSynchronousAsynchronousInterleaved();
  void test_multipleServers();
  void test_unmatchedRequest();
  void test_requestHandler();
  void test_responseHandler();
  void test_catchallRequestHandler();
  void test_catchallResponseHandler();
  void test_queryParameters();
  void test_handlersWithMessageFactory();

};

TestNetworkManager::TestNetworkManager()
{

}

TestNetworkManager::~TestNetworkManager()
{

}

void TestNetworkManager::test_localhostNameResolution_data() {
  QTest::addColumn<QString>("id");
  QTest::addColumn<QUrl>("url");

  QTest::newRow("localhost:80") << QStringLiteral("localhost:80")
                                << QUrl{QStringLiteral("http://localhost:80")};

  QTest::newRow("127.0.0.1:80") << QStringLiteral("127.0.0.1:80")
                                << QUrl{QStringLiteral("http://127.0.0.1:80")};

  QTest::newRow("localhost:default") << QStringLiteral("localhost:default")
                                     << QUrl{QStringLiteral("http://localhost")};

  QTest::newRow("127.0.0.1:default") << QStringLiteral("127.0.0.1:default")
                                << QUrl{QStringLiteral("http://127.0.0.1")};

  QTest::newRow("localhost:https") << QStringLiteral("localhost:https")
                                     << QUrl{QStringLiteral("https://localhost")};

  QTest::newRow("127.0.0.1:https") << QStringLiteral("127.0.0.1:https")
                                     << QUrl{QStringLiteral("https://127.0.0.1")};

  QTest::newRow("::1:80") << QStringLiteral("::1:80")
                          << QUrl{QStringLiteral("https://[::1]:80")};

  QTest::newRow("0.0.0.0:80") << QStringLiteral("0.0.0.0:80")
                          << QUrl{QStringLiteral("https://0.0.0.0:80")};

//  QTest::newRow("google") << QStringLiteral("google")
//                          << QUrl{QStringLiteral("http://google.com.au")};
}

void TestNetworkManager::test_localhostNameResolution()
{
  QFETCH(QString, id);
  QFETCH(QUrl, url);

  QtHttpNetworkManager manager{};
  bool result{manager.addConnection(id, url)};
  QVERIFY2(result, "Failed to resolve connection");
}

void TestNetworkManager::test_serverStartup()
{
  QtHttpNetworkManager manager{};
  manager.start();
  QVERIFY2(manager.isRunning(), "Server is running");
  manager.stop();
  QVERIFY2(not manager.isRunning(), "Server has been stopped");
}

void TestNetworkManager::test_serverSimpleRequestResponse()
{
  bool doneRequest{false};
  bool doneResponse{false};

  QtHttpNetworkManager manager{};
  manager.start();

  manager.addConnection("self", manager.boundAdress());

  // prep a simple response when the request is received
  QObject::connect(&manager, &NetworkManager::requestReceived,
                   [&manager, &doneRequest](QSharedPointer<RequestMessage> request) {
    doneRequest = true;
    qDebug() << "received request: " << request->urlPath()
             << " method: " << request->httpMethod()
             << " data: " << request->data();
    QCOMPARE(request->httpMethod(), HttpMethod::GET);
    QCOMPARE(request->urlPath(), "/simpleTest");

    QScopedPointer<ResponseMessage> response{new ResponseMessage{request->urlPath()}};
    manager.sendResponse(request, *response);
  });

  // Preparation to handle the receipt of the response
  QObject::connect(&manager, &NetworkManager::responseReceived,
                   [&doneResponse](QSharedPointer<ResponseMessage> response) {
    doneResponse = true;
    qDebug() << "received response: " << response->urlPath()
             << " status: " << response->statusCode()
             << "data: " << response->data();
    QCOMPARE(response->statusCode(), StatusCode::NO_CONTENT);
    QCOMPARE(response->urlPath(), "/simpleTest");

    QCoreApplication::instance()->quit();
  });


  // Send initial request to self (the timer is just to put in on the event
  // queue so that this function can finish executing and the server can
  // actually respond; you will not need to use the timer in the real code).
  QTimer::singleShot(1, [&manager]() {
    manager.sendRequest("self", RequestMessage{"/simpleTest"}); // really simple example
  } );

  // This just ensures the test will finish if there is an error with request/response
  QTimer::singleShot(2000, [&manager]() { manager.stop(); QCoreApplication::instance()->quit(); } );
  QCoreApplication::instance()->exec();

  QVERIFY2(doneRequest, "Request was never received");
  QVERIFY2(doneResponse, "Response was never received");
}


void TestNetworkManager::test_serverSynchronousRequestResponse()
{
  bool doneRequest{false};

  QtHttpNetworkManager manager{};
  manager.start();

  manager.addConnection("self", manager.boundAdress());

  // prep a simple response when the request is received
  QObject::connect(&manager, &NetworkManager::requestReceived,
                   [&manager, &doneRequest](QSharedPointer<RequestMessage> request) {
    doneRequest = true;
    qDebug() << "received request: " << request->urlPath()
             << " method: " << request->httpMethod()
             << " data: " << request->data();
    QCOMPARE(request->httpMethod(), HttpMethod::GET);
    QCOMPARE(request->urlPath(), "/simpleTest");

    QScopedPointer<ResponseMessage> response{new ResponseMessage{request->urlPath()}};
    manager.sendResponse(request, *response);
  });

  QSharedPointer<ResponseMessage> response{};
  response = manager.sendRequestWait("self", RequestMessage{"/simpleTest"});
  qDebug() << "received response: " << response->urlPath()
           << " status: " << response->statusCode()
           << "data: " << response->data();
  QCOMPARE(response->statusCode(), StatusCode::NO_CONTENT);
  QCOMPARE(response->urlPath(), "/simpleTest");
}

void TestNetworkManager::test_serverSynchronousAsynchronousInterleaved()
{
  int requestCount{0};
  int responseCount{0};
  int syncResponseCount{0};
  QMutex mutex{};

  QtHttpNetworkManager manager{};
  manager.start();

  manager.addConnection("self", manager.boundAdress());

  // prep a simple response when the request is received
  QObject::connect(&manager, &NetworkManager::requestReceived,
                   [&manager, &requestCount, &mutex](QSharedPointer<RequestMessage> request) {
    mutex.lock();
    ++requestCount;
    mutex.unlock();
    QCOMPARE(request->httpMethod(), HttpMethod::GET);

    QScopedPointer<ResponseMessage> response{new ResponseMessage{request->urlPath()}};
    manager.sendResponse(request, *response);
  });

  // Preparation to handle the receipt of the response
  QObject::connect(&manager, &NetworkManager::responseReceived,
                   [&responseCount, &syncResponseCount, &mutex](QSharedPointer<ResponseMessage> response) {
    qDebug() << "response Recieved emitted";
    QCOMPARE(response->statusCode(), StatusCode::NO_CONTENT);
    QCOMPARE(response->urlPath(), "/simpleAsynch");

    mutex.lock();
    ++responseCount;
    // End early if we are done
    if (responseCount >= 2 and syncResponseCount >= 2)
      QCoreApplication::instance()->quit();
    mutex.unlock();
  });

  for (int i{0}; i < 2; ++i) {

    // Async
    QTimer::singleShot(1, [&manager]() {
      manager.sendRequest("self", RequestMessage{"/simpleAsynch"}); // really simple example
    } );

    // Synch
    QTimer::singleShot(1, [&manager, &responseCount, &syncResponseCount, &mutex]() {
      QSharedPointer<ResponseMessage> response{};
      response = manager.sendRequestWait("self", RequestMessage{"/synch"});
      QVERIFY2(response != nullptr, "Response is nullptr");
      QCOMPARE(response->statusCode(), StatusCode::NO_CONTENT);
      QCOMPARE(response->urlPath(), "/synch");
      mutex.lock();
      ++syncResponseCount;

      // End early if we are done
      if (responseCount >= 2 and syncResponseCount >= 2)
        QCoreApplication::instance()->quit();
      mutex.unlock();
    } );
  }

  // This just ensures the test will finish if there is an error with request/response
  QTimer::singleShot(2000, [&manager]() {
    qDebug() << "Terminating due to time out";
    manager.stop();
    QCoreApplication::instance()->quit();
  } );
  QCoreApplication::instance()->exec();

  QCOMPARE(requestCount, 4);
  QCOMPARE(responseCount, 2);
  QCOMPARE(syncResponseCount, 2);
}

void TestNetworkManager::test_multipleServers()
{
  QtHttpNetworkManager manager1{};
  manager1.start(QUrl{"http://localhost/"}, {8101, 8102});
  QVERIFY2(manager1.isRunning(), "Could not even start the first one");

  QtHttpNetworkManager manager2{};
  manager2.start(QUrl{"http://localhost/"}, {8101, 8102});
  QVERIFY2(manager2.isRunning(), "Could not even start the second");

  QtHttpNetworkManager manager3{};
  manager3.start(QUrl{"http://localhost/"}, {8101, 8102});
  QVERIFY2(not manager3.isRunning(), "The third server should not have started.");

  manager1.stop();
  QVERIFY2(not manager1.isRunning(), "First one should have stopped");

  manager3.start(QUrl{"http://localhost/"}, {8101, 8102});
  QVERIFY2(manager3.isRunning(), "The third server should now have started.");
}

void TestNetworkManager::test_unmatchedRequest()
{
  bool doneResponse{false};

  QtHttpNetworkManager manager{};
  manager.start();

  QSharedPointer<RequestMessage> request{new RequestMessage{"/simpleTest"}};
  QScopedPointer<ResponseMessage> response{new ResponseMessage{request->urlPath()}};

  // This will outright crash if not correct
  // We could test this better if we were to mock out some of the QHttp stuff.
  manager.sendResponse(request, *response);
}

// Test that the handler executes when the manager receives a request over the network.
void TestNetworkManager::test_requestHandler()
{
  bool doneRequest{false};

  QtHttpNetworkManager manager{};
  manager.start();

  manager.addConnection("self", manager.boundAdress());
  manager.registerHandler({"/handlerPath", HttpMethod::PUT}, [](const QUrl& url, const QByteArray& data) {
    qDebug() << "handling: " << url << "  with: " << data;
    return new RequestStub{url, data};
  });

  // prep a simple response when the request is received
  QObject::connect(&manager, &NetworkManager::requestReceived,
                   [&manager, &doneRequest](QSharedPointer<RequestMessage> request) {
    doneRequest = true;
    QCOMPARE(request->httpMethod(), HttpMethod::PUT);
    QCOMPARE(request->urlPath(), "/handlerPath");
    QCOMPARE(request->data(), QByteArray{"handler test"});
    QCOMPARE(request->entity(), QString{"handler test"});

    // Of course, responses don't actually send through the URL, it is for local tracking.
    QScopedPointer<ResponseMessage> response{new ResponseMessage{request->urlPath()}};
    manager.sendResponse(request, *response);
  });

  QSharedPointer<ResponseMessage> response{};
  response = manager.sendRequestWait("self", RequestStub{QUrl{"/handlerPath"}, QString{"handler test"}});
  QCOMPARE(response->statusCode(), StatusCode::NO_CONTENT);
  QCOMPARE(response->urlPath(), "/handlerPath");
}

// Test that the handler executes when the manager received a reponse over the network.
void TestNetworkManager::test_responseHandler()
{
  QtHttpNetworkManager manager{};
  manager.start();

  manager.addConnection("self", manager.boundAdress());

  manager.registerHandler({"/handlerPath", HttpMethod::GET}, [](const QUrl& url, const QByteArray& data) {
    qDebug() << "handling response: " << url << "  with: " << data;
    return new ResponseStub{url, data};
  });

  // prep a simple response when the request is received
  QObject::connect(&manager, &NetworkManager::requestReceived,
                   [&manager](QSharedPointer<RequestMessage> request) {
    QScopedPointer<ResponseMessage> response{new ResponseStub{request->urlPath(), QString{"response handler test"}}};
    manager.sendResponse(request, *response);
  });

  QSharedPointer<ResponseMessage> response{};
  response = manager.sendRequestWait("self", RequestMessage{"/handlerPath"});
  QCOMPARE(response->statusCode(), StatusCode::NOT_IMPLEMENTED);
  QCOMPARE(response->urlPath(), "/handlerPath");
  QCOMPARE(response->data(), QByteArray{"response handler test"});
  QCOMPARE(response->entity(), QString{"response handler test"});
}

void TestNetworkManager::test_catchallRequestHandler()
{
  bool doneRequest{false};

  QtHttpNetworkManager manager{};
  manager.start();

  manager.addConnection("self", manager.boundAdress());
  manager.registerHandler({"*", HttpMethod::GET}, [](const QUrl& url, const QByteArray& data) {
    qDebug() << "handling: " << url << "  with: " << data;
    return new RequestStub{url, data};
  });

  // prep a simple response when the request is received
  QObject::connect(&manager, &NetworkManager::requestReceived,
                   [&manager, &doneRequest](QSharedPointer<RequestMessage> request) {
    doneRequest = true;
    QCOMPARE(request->httpMethod(), HttpMethod::PUT);
    QCOMPARE(request->urlPath(), "/handlerPath");
    QCOMPARE(request->data(), QByteArray{"handler test"});
    QCOMPARE(request->entity(), QString{"handler test"});

    QScopedPointer<ResponseMessage> response{new ResponseMessage{request->urlPath()}};
    manager.sendResponse(request, *response);
  });

  QSharedPointer<ResponseMessage> response{};
  response = manager.sendRequestWait("self", RequestStub{QUrl{"/handlerPath"}, QString{"handler test"}});
  QCOMPARE(response->statusCode(), StatusCode::NO_CONTENT);
  QCOMPARE(response->urlPath(), "/handlerPath");
}

void TestNetworkManager::test_catchallResponseHandler()
{
  QtHttpNetworkManager manager{};
  manager.start();

  manager.addConnection("self", manager.boundAdress());

  manager.registerHandler({"*", HttpMethod::GET}, [](const QUrl& url, const QByteArray& data) {
    qDebug() << "handling response: " << url << "  with: " << data;
    return new ResponseStub{url, data};
  });

  // prep a simple response when the request is received
  QObject::connect(&manager, &NetworkManager::requestReceived,
                   [&manager](QSharedPointer<RequestMessage> request) {
    QScopedPointer<ResponseMessage> response{new ResponseStub{request->urlPath(), QString{"response handler test"}}};
    manager.sendResponse(request, *response);
  });

  QSharedPointer<ResponseMessage> response{};
  response = manager.sendRequestWait("self", RequestMessage{"/handlerPath", HttpMethod::PUT});
  QCOMPARE(response->statusCode(), StatusCode::NOT_IMPLEMENTED);
  QCOMPARE(response->urlPath(), "/handlerPath");
  QCOMPARE(response->data(), QByteArray{"response handler test"});
  QCOMPARE(response->entity(), QString{"response handler test"});
}

void TestNetworkManager::test_queryParameters()
{
  bool doneRequest{false};

  QtHttpNetworkManager manager{};
  manager.start();

  manager.addConnection("self", manager.boundAdress());
  manager.registerHandler({"/handlerPath", HttpMethod::GET}, [](const QUrl& url, const QByteArray& data) {
    qDebug() << "handling: " << url << "  with: " << data;
    return new RequestStub{url, data};
  });

  // prep a simple response when the request is received
  QObject::connect(&manager, &NetworkManager::requestReceived,
                   [&manager, &doneRequest](QSharedPointer<RequestMessage> request) {
    doneRequest = true;
    QCOMPARE(request->httpMethod(), HttpMethod::PUT);
    QCOMPARE(request->urlPath(), "/handlerPath");
    QList<QPair<QString, QString>> expected{{"example-query", "with value"}};
    QCOMPARE(request->queryParameters(), expected);

    QScopedPointer<ResponseMessage> response{new ResponseMessage{request->urlPath()}};
    manager.sendResponse(request, *response);
  });

  QSharedPointer<ResponseMessage> response{};
  RequestStub request{QUrl{"/handlerPath"}, QString{"handler test"}};
  request.addQueryParameter("example-query", "with value");
  response = manager.sendRequestWait("self", request);
  QCOMPARE(response->statusCode(), StatusCode::NO_CONTENT);
  QCOMPARE(response->urlPath(), "/handlerPath");
}

void TestNetworkManager::test_handlersWithMessageFactory()
{
  bool doneRequest{false};

  FakeMessageFactory factory{};
  QtHttpNetworkManager manager{};
  manager.start();

  manager.addConnection("self", manager.boundAdress());

  manager.registerHandler({"/state/on", HttpMethod::PUT}, [&factory](const QUrl& url, const QByteArray& data) {
    qDebug() << "handling: " << url << "  with: " << data;
    return factory.createPutStateRequest(url, data);
  });

  manager.registerHandler({"/state/on", HttpMethod::PUT}, [&factory](const QUrl& url, const QByteArray& data) {
    qDebug() << "handling response: " << url << "  with: " << data;
    return factory.createPutStateResponse(data, url);
  });

  // prep a simple response when the request is received
  QObject::connect(&manager, &NetworkManager::requestReceived,
                   [&manager, &factory, &doneRequest](QSharedPointer<RequestMessage> request) {
    doneRequest = true;
    QCOMPARE(request->httpMethod(), HttpMethod::PUT);
    QCOMPARE(request->urlPath(), "/state/on");
    QCOMPARE(request->data(), QByteArray{"example"});
    QCOMPARE(request->entity(), QString{"example"});

    QScopedPointer<ResponseMessage> response{factory.createPutStateResponse(QStringLiteral("not real"))};
    manager.sendResponse(request, *response);
  });

  QSharedPointer<ResponseMessage> response{};
  QScopedPointer<RequestMessage> request{factory.createPutStateRequest("on", {{"data", "example"}})};
  response = manager.sendRequestWait("self", *request);
  QCOMPARE(response->statusCode(), StatusCode::NOT_IMPLEMENTED);
  QCOMPARE(response->urlPath(), "/state/on");
}

QTEST_MAIN(TestNetworkManager)

#include "tst_testnetworkmanager.moc"
