#ifndef MESSAGE_H
#define MESSAGE_H

#include <QByteArray>
#include <QString>
#include <QMap>
#include <QUrl>
#include <QVariant>
#include "qhttpabstracts.hpp"

namespace network {

/**
 * @brief The Message class represents requests and responses to be
 * sent via the network manager. It provides a common-ish interface
 * over the QHttp server and the standard Qt Client networking code.
 *
 * You will usually use the subclasses RequestMessage and
 * ResponseMessage (or further derived classes).
 *
 * The idea is that a Message is a container around all of the
 * information required to send/receive a message of a particular
 * REST API call.
 * Moreover, the specific message types may how to convert the
 * supplied objects to the data to be sent over the network and vice
 * versa. For example, a message type may take a Measurement and
 * produce the byte data (accessible through the data() function)
 * by serialising the object into CSV and convert the CSV into bytes.
 * Conversely, the message type will be able to read the byte data
 * to create a Measurement object by deserialising from CSV.
 *
 * (The alternative is to handle the conversion in the factory and
 * keep the messages lean.)
 *
 * With the message configuration and content stored in a Message
 * object, the NetworkManager will then send the request or response.
 *
 * Note: that the Message only stores the @bold path portion of the
 * URL as the same message could be sent to @bold different endpoints, i.e.,
 * devices or controllers.
 */
class Message
{
public:
  Message(const QString &urlPath = "/");
  Message(const QUrl &url);
  virtual ~Message() = default;

  /**
   * @brief urlPath Returns the path portion of the URL that is/was requested.
   * Will be combined with endpoint or IP address to complete the URL.
   * @return
   */
  virtual const QString& urlPath() const;

  /**
   * @brief data Returns the data associated with this message.
   * @return
   */
  virtual QByteArray data() const = 0;

  /**
   * @brief entity Returns the application entity/data for the message:
   * the 'entity' is possibly a list of things.
   *
   * This is in contrast to the @c data() function, which returns the
   * data that is to be sent/recevied over the wire.
   *
   * @return
   */
  virtual QVariant entity() const = 0;

  /**
   * @brief headers Returns the headers to be used for this request/response.
   * @return
   */
  virtual const QMap<QString, QString>& headers() const;

  /// For convenience to access and modify the headers
  QString& operator[] (const QString &key);
  const QString operator[] (const QString &key) const;

protected:
  QString _urlPath;
  QMap<QString, QString> _headers;
};

/**
 * @brief The HttpMethod enum is the subset of HTTP methods that we need
 * to support in this application.
 */
enum HttpMethod {
  GET = qhttp::THttpMethod::EHTTP_GET, ///< GET - for retrieving resources/entities (collections or individuals)
  PUT = qhttp::THttpMethod::EHTTP_PUT, ///< PUT - for update or replace a resource/entity
  POST = qhttp::THttpMethod::EHTTP_POST, ///< POST - add a new entity to a collection
  DELETE = qhttp::THttpMethod::EHTTP_DELETE ///< DELETE - delete a collection or resource
};

/**
 * @brief The StatusCode enum is the subset of HTTP Status Codes that we
 * will make use of this in application. We have a small selection that
 * allow us to report success as well as several error types.
 */
enum StatusCode {
  OK = qhttp::TStatusCode::ESTATUS_OK,           ///< OK - successful response
  CREATED = qhttp::TStatusCode::ESTATUS_CREATED, ///< Created - entity created
  NO_CONTENT = qhttp::TStatusCode::ESTATUS_NO_CONTENT, ///< No Content - successful response with no body in the response
  BAD_REQUEST = qhttp::TStatusCode::ESTATUS_BAD_REQUEST, ///< Bad Request - unable to interpret request message
  NOT_FOUND = qhttp::TStatusCode::ESTATUS_NOT_FOUND,     ///< Not Found - unable to find specified entity
  CONFLICT = qhttp::TStatusCode::ESTATUS_CONFLICT,       ///< Conflict - attempted to update an entity that is newer
  SERVER_ERROR = qhttp::TStatusCode::ESTATUS_INTERNAL_SERVER_ERROR, ///< Server Error - the server crapped itself
  NOT_IMPLEMENTED = qhttp::TStatusCode::ESTATUS_NOT_IMPLEMENTED     ///< Not Implemented - the message type is not (yet) implemented
};

} // namespace network

Q_DECLARE_METATYPE(network::HttpMethod)
Q_DECLARE_METATYPE(network::StatusCode)

#endif // MESSAGE_H
