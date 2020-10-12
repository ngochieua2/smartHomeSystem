#ifndef REQUESTMESSAGE_H
#define REQUESTMESSAGE_H
#include "message.h"
#include <QByteArray>
#include <QList>
#include <QPair>
#include <QString>
#include <QUrl>
#include <QUrlQuery>
#include <QVariant>

#include "qhttpserverrequest.hpp"

namespace network {

/**
 * @brief The RequestMessage class - Base class for request messages,
 * can also be used directly for simple GET requests.
 *
 * You can modify this class as you require, but most of your
 * implementation will be on subclasses of it that you create.
 * Refer to the 'ExampleRequestMessage' class in the TestNetworkExample
 * test project.
 *
 * Note: the data() function will always return empty and must be
 * overridden on derived class if data needs to be included in the
 * request. Most requests do not send any data, so it is a reasonable
 * default.
 */
class RequestMessage : public Message
{
public:
  RequestMessage(const QString &urlPath = QStringLiteral("/"), HttpMethod httpMethod = GET);
  RequestMessage(const QUrl &url, HttpMethod httpMethod = GET);

  /**
   * @brief httpMethod Return the HTTP method (e.g., GET, POST, etc.) this message is to be sent using.
   * @return the HTTP method of this message
   */
  HttpMethod httpMethod() const;

  /**
   * @brief data Returns an empty QByteArray. Override in subclasses that actually provide data.
   * @return nothing
   */
  QByteArray data() const override;

  /**
   * @brief entity Returns an empty/null QVariant. Override in subclasses that actually have data/entities.
   * @return nothing
   */
  QVariant entity() const override;

  /**
   * @brief queryParameters Returns the query parameters to be used for this message.
   *
   * Using a list rather than a map preserves order
   *
   * @return
   */
  virtual QList<QPair<QString, QString>> queryParameters() const;

  /**
   * @brief applyQueryParameters Adds this request's query parameters to the given URL
   *
   * @return
   */
  virtual void applyQueryParameters(QUrl &url) const;

  /**
   * @brief addQueryParameter Adds the specified parameter to the query parameters to
   * be sent with the request.
   *
   * @param name
   * @param value
   */
  virtual void addQueryParameter(const QString &name, const QString &value);

  /**
   * @brief httpMethodFrom Returns the HTTP method of the specified QHttpRequest
   * as a HttpMethod rather than the qhttp::THttpMethod used by the QHttp library.
   *
   * This is a convenience function. There is no need to modify it (or even use it).
   *
   * @param request the request from which to retrieve the HTTP method
   * @return the method code as HttpMethod
   */
  inline static HttpMethod httpMethodFrom(const qhttp::server::QHttpRequest *request) {
    return static_cast<network::HttpMethod>(request->method());
  }

protected:
  QUrlQuery _queryParameters;

private:
  HttpMethod _method;
};

} // namespace network

#endif // REQUESTMESSAGE_H
