#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>
#include <QList>
#include <QPair>
#include <QUrl>
#include <QSharedPointer>
#include "requestmessage.h"
#include "responsemessage.h"

namespace network {

/**
 * @brief The NetworkManager class provides an interface for a facade that
 * encapsulates both server and client components necessary to send and
 * receive messages over the network.
 */
class NetworkManager : public QObject
{
  Q_OBJECT
public:
  explicit NetworkManager(QObject *parent = nullptr);

  /// @brief Starts the server listening on the specified bind address and port,
  /// only one of the ports will be bound to the rest are alternatives.
  ///
  /// If the server cannot be started on a port, the next port of the
  /// @a portRange is tried.
  ///
  /// After this function completed, whether the server was successfully
  /// started can be determined by called @sa isRunning().
  ///
  /// The address and port at which the server is listening can be retrieved from
  /// @sa boundAddress()
  ///
  /// If the server is running and a request is received, the requestReceived(...)
  /// signal will be emitted.
  ///
  /// @param bindAddress the address (and possibly port) to listen on; the protocol is ignored
  /// @param portRange a list of ports to try to bind to
  virtual void start(const QUrl &bindAddress = QUrl{"http://localhost"},
                     const QList<quint16> &portRange = {80, 8101, 8102, 8103} ) = 0;


  /// @brief Stops the server from listening for requests.
  ///
  /// Has no effect if the server is not currently listening for requests.
  virtual void stop() = 0;


  /// @brief Access the address and port to which the server is bound.
  ///
  /// If the server is not currently running, an invalid QUrl is returned.
  virtual const QUrl &boundAdress() const = 0;


  /// @brief Returns @c true if the server is listening for requests, false otherwise.
  ///
  /// After call start(), this function should be called and if it returns @c false,
  /// a warning should be provided to the user and the application should quit.
  virtual bool isRunning() const = 0;


  /// @brief Adds a named Connection to the manager with the specified id and address
  ///
  /// If a connection with the id already exists, returns false; otherwise returns true.
  ///
  /// While requests can be received from unknown sources, messages can only be sent to
  /// known connections.
  virtual bool addConnection(const QString &id, const QUrl &targetAddress) = 0;


  /// @brief Removes the named Connection from the manager.
  ///
  /// If the connection does not currently exist, does nothing.
  virtual void removeConnection(const QString &id) = 0;


  /// @brief Send a request to the target named connection
  ///
  /// When a response to this request is a received the responseReceived(...)
  /// signal will be emitted.
  virtual void sendRequest(const QString &id, const RequestMessage &request) = 0;


  /// @brief Send a request to the target named connection and wait for the response
  ///
  /// No signal will be emitted when the response is received; instead this
  /// function will block until the response is received and returns it.
  ///
  /// This will be required when using Proxies as they must return the
  /// appropriate value to appear like the real thing.
  /// Otherwise you can use the above function and hook the signals up
  /// to utilise the information or output it wherever it needs to go.
  virtual QSharedPointer<ResponseMessage> sendRequestWait(const QString &id, const RequestMessage &request) = 0;


  /// @brief Send a response to the specified request
  ///
  /// The request must be a request that came from the NetworkManager in the first
  /// place, via the requestReceived signal; otherwise nothing will happen.
  ///
  /// This will end a request response cycle from the perspective of server-side.
  /// The original requestor will emit its responseReceived(...) signal once it
  /// receives the response.
  virtual void sendResponse(QSharedPointer<const RequestMessage> request, const ResponseMessage &response) = 0;

  using RequestGenerator = std::function<RequestMessage* (const QUrl&, const QByteArray&)>;
  using ResponseGenerator = std::function<ResponseMessage* (const QUrl&, const QByteArray&)>;

  /**
   * @brief registerHandler Register url path and HTTP method pair with
   * a handler that will be used to create a RequestMessage or ResponseMessage
   * when the NetworkManager recieves data from the network that matches.
   * The generated message is what will be the argument to the requestReceived
   * or responseReceived signal emitted from the NetworkManager.
   *
   * If the pair is already registered, the previous handler will replaced by
   * provided handler.
   *
   * The handler expects the 2 parameters: const QUrl& url, const QByteArray& data
   * Note: the url will include any query parameters, so they can be processed
   *
   * A path with special string "*" is treated as a 'catch-all' or default handler.
   * The HTTP method is ignored in this case. You may want to register a handler that
   * can capture the data if desired; otherwise a default message will be generated that
   * captures only the URL and HTTP method or response Status.
   *
   * @param path a pair of string (e.g., '/simple') and method (e.g., GET) to register a handler
   * @param requestHandler the function, functor, or lambda, that will be used to create a request message
   * @param responseHandler the function, functor, or lambda, that will be used to create a response message
   */
  virtual void registerHandler(const QPair<QString, HttpMethod> &path, const RequestGenerator &requestHandler) = 0;
  virtual void registerHandler(const QPair<QString, HttpMethod> &path, const ResponseGenerator &responseHandler) = 0;

  /**
   * @brief removePath Deregisters a URL path/HTTP method pair from the
   * NetworkManager; the handler for which will be removed and no longer called.
   *
   * If the pair is not registered, nothing will happen.
   *
   * @param path a pair of string (e.g., '/simple') and method (e.g., GET) to deregister
   */
  virtual void removePath(const QPair<QString, HttpMethod> &path) = 0;

signals:
  void requestReceived(QSharedPointer<RequestMessage> request);
  void responseReceived(QSharedPointer<ResponseMessage> response);

};

} // namespace network


#endif // NETWORKMANAGER_H
