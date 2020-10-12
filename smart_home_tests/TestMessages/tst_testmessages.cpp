#include <QtTest>

#include "network/message.h"
#include "network/requestmessage.h"
#include "network/responsemessage.h"

#include "messagestub.h"

#include <QList>
#include <QPair>
#include <QString>

using namespace network;

// Some simple tests of the Message class hierarchy.
// Particularly the URL processing in object creation.

class TestMessages : public QObject
{
  Q_OBJECT

public:
  TestMessages();
  ~TestMessages();

private slots:
  void test_messageBase();
  void test_requestMessage();
  void test_requestQueryParameters();
  void test_responseMessage();
};

TestMessages::TestMessages()
{

}

TestMessages::~TestMessages()
{

}

void TestMessages::test_messageBase()
{
  MessageStub simplePath{"somePath"};
  QCOMPARE(simplePath.urlPath(), QStringLiteral("somePath"));

  MessageStub longerPath{"somePath/more"};
  QCOMPARE(longerPath.urlPath(), QStringLiteral("somePath/more"));

  MessageStub precedingSlashPath{"/somePath/more"};
  QCOMPARE(precedingSlashPath.urlPath(), QStringLiteral("/somePath/more"));

  MessageStub urlPath{QUrl{"http://example.com/somePath/more"}};
  QCOMPARE(urlPath.urlPath(), QStringLiteral("/somePath/more"));

  MessageStub urlPathString{"http://example.com/somePath/more"};
  QCOMPARE(urlPathString.urlPath(), QStringLiteral("/somePath/more"));

  MessageStub urlIpPath{QUrl{"http://127.0.0.1/somePath/more"}};
  QCOMPARE(urlIpPath.urlPath(), QStringLiteral("/somePath/more"));

  MessageStub headers{""};
  headers["test-header"] = "test-value";
  QCOMPARE(headers["test-header"], QStringLiteral("test-value"));
  QCOMPARE(headers.headers()["test-header"], QStringLiteral("test-value"));

  QCOMPARE(headers["test-not-present"], QStringLiteral(""));
  QCOMPARE(headers.headers().contains("test-not-present"), true);
}

void TestMessages::test_requestMessage()
{
  RequestMessage getRoot{};
  QCOMPARE(getRoot.httpMethod(), HttpMethod::GET);

  RequestMessage getSimplePath{"/somePath", HttpMethod::GET};
  QCOMPARE(getSimplePath.httpMethod(), HttpMethod::GET);
  QCOMPARE(getSimplePath.data(), QByteArray{});

  RequestMessage put{"/", HttpMethod::PUT};
  QCOMPARE(put.httpMethod(), HttpMethod::PUT);

  RequestMessage post{"/", HttpMethod::POST};
  QCOMPARE(post.httpMethod(), HttpMethod::POST);

  RequestMessage deleteReq{"/", HttpMethod::DELETE};
  QCOMPARE(deleteReq.httpMethod(), HttpMethod::DELETE);
}

void TestMessages::test_requestQueryParameters()
{
  QList<QPair<QString, QString>> expectedParameters{{"example", "value"},
                                                    {"second", "1"}};

  RequestMessage getQueryString{"/somePath?example=value&second=1", HttpMethod::GET};
  QCOMPARE(getQueryString.httpMethod(), HttpMethod::GET);
  QCOMPARE(getQueryString.queryParameters(), expectedParameters);

  RequestMessage getQueryUrl{QUrl{"/somePath?example=value&second=1"}, HttpMethod::GET};
  QCOMPARE(getQueryUrl.httpMethod(), HttpMethod::GET);
  QCOMPARE(getQueryUrl.queryParameters(), expectedParameters);
}

void TestMessages::test_responseMessage()
{
  ResponseMessage getRoot{};
  QCOMPARE(getRoot.statusCode(), StatusCode::NO_CONTENT);

  ResponseMessage getSimplePath{"/somePath", StatusCode::OK};
  QCOMPARE(getSimplePath.statusCode(), StatusCode::OK);
  QCOMPARE(getSimplePath.data(), QByteArray{});

  ResponseMessage  getNotFound{"/somePath", StatusCode::NOT_FOUND};
  QCOMPARE(getNotFound.statusCode(), StatusCode::NOT_FOUND);
}

QTEST_APPLESS_MAIN(TestMessages)

#include "tst_testmessages.moc"
