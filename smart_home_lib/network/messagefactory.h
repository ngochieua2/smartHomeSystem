#ifndef MESSAGEFACTORY_H
#define MESSAGEFACTORY_H

#include <QByteArray>
#include <QList>
#include <QMap>
#include <QString>
#include <QUrl>
#include <QVariant>
#include "requestmessage.h"
#include "responsemessage.h"
#include "measurement.h"
#include "deviceinfo.h"

namespace network {

/**
 * @brief The MessageFactory class - Abstract Factory class declaring the
 * interface for creating request and response messages.
 *
 * There are member functions to create requests and responses for the
 * different URL Paths and HTTP Methods (for requests) and HTTP Statuses
 * (for responses) at both the sending application and receiver application.
 * For the sender, typically application entities (e.g., Measurements) are
 * passed in, which needs to be serialised into the data content.
 * This may be done by your factory implementation or by subtypes of
 * RequestMessage and ResponseMessage that you define.
 *
 * While, at the receiver, the byte data content of the HTTP message is
 * passed in and it must be deserialised to produce the application entity,
 * such as a list of Measurements.
 *
 * These pairs of functions need to be implemented together to realise the
 * communication between the controller and device. However, just because
 * the factory provides separate functions it does not mean their
 * implementations cannot reuse classes, functions, etc., that are common
 * to both functions of the pair.
 *
 * When creating a concrete implementation you will need to provide a type
 * (e.g., an enum, string, etc.) for the 'known states' that can be used
 * for PUT /state/... messages and the setpoint 'change types' that can be
 * used for PUT /setpoint/... messages.
 *
 * @sa createPutStateRequest
 * @sa createPutSetpointRequest
 *
 * If it fits the rest of your application, you may make this derived from
 * QObject, e.g., to utilise the object hierarchy-based memory management.
 * But note that Signals & Slots do not work properly for template classes.
 */
template <typename T, typename U>
class MessageFactory
{
public:
  typedef T AllowedStates; ///< gives it nicer name and makes it referenceable externally
  typedef U SetpointChange; ///< gives it nicer name and makes it referenceable externally

  MessageFactory() = default;
  virtual ~MessageFactory() = default;

  /**
   * @brief createGetStateRequest Returns a RequestMessage configured
   * for the '/state' URL path and the 'GET' HTTP Method.
   *
   * This request does not include any data or parameters and can be used
   * at sender and receiver.
   *
   * @return request message for GET /state
   */
  virtual RequestMessage* createGetStateRequest() = 0;

  /**
   * @brief createGetStateResponse Returns a ResponseMessage containing
   * the Measurements representing the device state.
   *
   * All devices have at least one "state" Measurement, an empty list
   * indicates an internal error of the server, so the response status
   * MUST be SERVER_ERROR; otherwise status will be OK. An optional
   * error message may be included in the response.
   *
   * @param state list of device state Measurements
   * @param errorMessage (optional) error message to be included in the response
   * @return response for GET /state
   */
  virtual ResponseMessage* createGetStateResponse(const QList<Measurement*> &state,
                                                  const QString &errorMessage = "") = 0;

  /**
   * @brief createGetStateResponse Returns a ResponseMessage containing
   * the Measurements representing the device state that is built at the
   * receiving application.
   *
   * All devices have at least one "state" Measurement: therefore, empty
   * data indicates an internal error of the server, so the response status
   * MUST be SERVER_ERROR.
   *
   * If data is provided but does not conform to the expected Measurement
   * format, it should be considered an error message and the response
   * status WILL be SERVER_ERROR and the application entity will be the
   * error message.
   *
   * Otherwise status will be OK and the application
   * entity will contain a list of deserialised Measurements.
   *
   * @param data the data from the underlying HTTP response
   * @param url (optional) the request url if desired
   * @return response for GET /state built at the receiver
   */
  virtual ResponseMessage* createGetStateResponse(const QByteArray &data, const QUrl &url = {"/state"}) = 0;


  /**
   * @brief createPutStateRequest Returns a RequestMessage configured
   * for a specified '/state/<state>' URL path and the 'PUT' HTTP Method.
   * This interface typically changes the state of a device and may specify
   * additional parameters.
   *
   * The implementation will need to map from the allowed states
   * to the correct URL path, e.g., /state/on, and map the parameters
   * appropriately (some could be data, others URL query parameters).
   *
   * The @a state may also map to sub-paths, e.g.: /state/brightness-level/dim
   *
   * Consider that the Smart Home System tries to maintain a consistent
   * REST API across its devices, so this generalisation can be made.
   * Also, consider that some concrete implementations of the MessageFactory
   * may be specific to certain devices (or sets of devices).
   *
   * @param state the specific state to be set
   * @param parameters (optional) additional parameters for the request, e.g., 'delay' and 'duration'
   * @return request for PUT /state/... given a specified state and (optional) parameters
   */
  virtual RequestMessage* createPutStateRequest(const AllowedStates &state,
                                                const QMap<QString, QVariant> &parameters = QMap<QString, QVariant>{}) = 0;

  /**
   * @brief createPutStateRequest Returns a RequestMessage built at the
   * receiving application when a PUT /state/<state> request is received.
   *
   * The implementation will need to map from the URL path to the allowed
   * states, e.g., /state/on, and map the parameters appropriately such
   * that the application entity is a QMap<QString, QVariant> object..
   *
   * The @a state may also map to sub-paths, e.g.: /state/brightness-level/dim
   *
   * @param path the URL Path for which the request was received
   * @param data the data from the underlying HTTP response, most likely empty
   * @return request for PUT /state/<state>[?<param>] built at the receiver
   */
  virtual RequestMessage* createPutStateRequest(const QUrl &path, const QByteArray &data) = 0;

  /**
   * @brief createPutStateResponse Returns a ResponseMessage for the
   * PUT /state/... group of URL Paths.
   *
   * A successful PUT will result in a No Content response.
   * A failed PUT will result in Bad Request response (the provided
   * parameters could not be understood, or were not provided, etc.).
   * Occurrence of a failure is indicated by a non-empty @a errorMessage.
   *
   * (The error message is useful when testing from a browser)
   *
   * @param errorMessage indicating the cause of the failure
   * @return response for PUT /state/...
   */
  virtual ResponseMessage* createPutStateResponse(const QString &errorMessage = "") = 0;

  /**
   * @brief createPutStateResponse Returns a ResponseMessage for the
   * PUT /state/... group of URL Paths that is built at the receiving application.
   *
   * Empty data indicates a successful No Content response.
   * If data is present, it will be intepreted as an error message (plain text)
   * for a Bad Request response.
   *
   * (The error message may be logged)
   *
   * @param data empty data for success, error message on failure
   * @param url (optional) the request url if desired
   * @return response for PUT /state/... built at the receiver
   */
  virtual ResponseMessage* createPutStateResponse(const QByteArray &data, const QUrl &url = {"/state"}) = 0;


  /**
   * @brief createGetMeasurementsRequest Returns a RequestMessage configured
   * for '/measurements[/last][?name={name},type={type}]' URL path and the
   * 'GET' HTTP Method.
   *
   * (The square bracketed sections indicate it is optional depending on the
   * specified parameters.)
   *
   * If the optional parameters are provided but not supported, they can be
   * ignored by the receiver.
   *
   * @param mostRecentOnly @c true if only the 1 most recent Measurement is to be retrieved
   * @param filters (optional) parameters indicating filters to be applied to the Measurements
   * @return request for GET /measurements or /measurements/last
   */
  virtual RequestMessage* createGetMeasurementsRequest(bool mostRecentOnly,
                                                       const QMap<QString, QVariant> &filters = QMap<QString, QVariant>{}) = 0;

  /**
   * @brief createGetMeasurementsRequest Returns a RequestMessage built at the
   * receiving application when a GET /measurements[/last][?name={name},type={type}]
   * request is received.
   *
   * (The square bracketed sections indicate it is optional depending on the
   * specified parameters.)
   *
   * The implementation will need to map from the URL path to the correct action,
   * e.g., /measurements/last, and map the parameters appropriately such
   * that the application entity is a QMap<QString, QVariant> object.
   *
   * @param path the URL Path for which the request was received
   * @param data the data from the underlying HTTP response, most likely empty
   * @return request for GET /measurements[/last][?name={name},type={type}] built at the receiver
   */
  virtual RequestMessage* createGetMeasurementsRequest(const QUrl &path, const QByteArray &data) = 0;

  /**
   * @brief createGetMeasurementsResponse Returns a ResponseMessage containing
   * the device's most recent measurement(s).
   *
   * Response status will always be OK. Empty lists are allowed.
   *
   * @param measurements list of device sensor Measurements
   * @return response for GET /measurements[/last][?name={name},type={type}]
   */
  virtual ResponseMessage* createGetMeasurementsResponse(const QList<Measurement*> &measurements) = 0;

  /**
   * @brief createGetMeasurementsResponse Returns a ResponseMessage containing
   * the Measurements representing the device measurements that is built at the
   * receiving application.
   *
   * The application entity will contain a (possibly empty) list of deserialised
   * Measurements.
   *
   * @param data the data from the underlying HTTP response
   * @param url (optional) the request url if desired
   * @return response for GET /measurements[/last][?name={name},type={type}] built at the receiver
   */
  virtual ResponseMessage* createGetMeasurementsResponse(const QByteArray &data, const QUrl &url = {"/measurements"}) = 0;


  /**
   * @brief createPostMeasurementsRequest Returns a RequestMessage configured
   * for '/measurements' URL path and the 'POST' HTTP Method.
   *
   * Contains a list of Measurements, which is the measurement data to be
   * reported to the Controller.
   *
   * @param measurements the Measurements to report
   * @return request for POST /measurements
   */
  virtual RequestMessage* createPostMeasurementsRequest(const QList<Measurement*> &measurements) = 0;

  /**
   * @brief createPostMeasurementsRequest Returns a RequestMessage built at the
   * receiving application when a POST /measurements request is received.
   *
   * The data is expected to be serialised Measurement data, so the applicatation
   * entity will be a (possibly empty) list of Measurements.
   *
   * @param data the data from the underlying HTTP request, containing Measurement data
   * @param url (optional) the request url if desired
   * @return request for POST /measurements built at the receiver
   */
  virtual RequestMessage* createPostMeasurementsRequest(const QByteArray &data, const QUrl &url = {"/measurements"}) = 0;

  /**
   * @brief createPostMeasurementsResponse Returns a ResponseMessage for
   * POST /measurements and indicating the success or failure of the report.
   *
   * A successful POST will result in a No Content status.
   *
   * If no Measurements were provided in the request, it will result in a
   * Bad Request status. (The receiver excepts at least one Measurement)
   *
   * Occurrence of a failure is indicated by a non-empty @a errorMessage.
   *
   * @return response for POST /measurements
   */
  virtual ResponseMessage* createPostMeasurementsResponse(const QString &errorMessage = "") = 0;

  /**
   * @brief createPostMeasurementsResponse Returns a ResponseMessage for
   * POST /measurements that is built at the receiving application.
   *
   * Empty data indicates a successful No Content response.
   * If data is present, it will be intepreted as an error message (plain text)
   * for a Bad Request response.
   *
   * (The error message may be logged)
   *
   * @param data empty data for success, error message on failure
   * @param url (optional) the request url if desired
   * @return response for POST /measurements built at the receiver
   */
  virtual ResponseMessage* createPostMeasurementsResponse(const QByteArray &data, const QUrl &url = {"/measurements"}) = 0;


  /**
   * @brief createGetSetpointRequest Returns a RequestMessage configured
   * for the '/setpoint' URL path and the 'GET' HTTP Method.
   *
   * This request does not include any data and can be used at both sender
   * and receiver.
   *
   * @return request message for GET /setpoint
   */
  virtual RequestMessage* createGetSetpointRequest() = 0;

  /**
   * @brief createGetSetpointResponse Returns a ResponseMessage containing
   * the Measurement representing the device setpoint.
   *
   * All devices with a setpoint must have a measurement for it, a nullptr
   * value indicates an internal error of the server, so the response status
   * MUST be SERVER_ERROR; otherwise status will be OK.
   *
   * (Note that a device without a setpoint would return Not Found,
   * independently of this message type.)
   *
   * @param setpoint the Measurement representing the setpoint, or nullptr for error
   * @return response for GET /setpoint
   */
  virtual ResponseMessage* createGetSetpointResponse(const Measurement* setpoint) = 0;

  /**
   * @brief createGetSetpointResponse Returns a ResponseMessage containing
   * the Measurement representing the device setpoint that is built at the
   * receiving application.
   *
   * All devices with a setpoint must have a measurement for it: therefore,
   * empty data indicates an internal error of the server, so the response
   * status MUST be SERVER_ERROR.
   *
   * If data is provided but does not conform to the expected Measurement
   * format, it should be considered an error message and the response
   * status WILL be SERVER_ERROR and the application entity will be the
   * error message.
   *
   * Otherwise status will be OK and the application entity will contain a
   * deserialised Measurement.
   *
   * @param data the data from the underlying HTTP response
   * @param url (optional) the request url if desired
   * @return response for GET /setpoint built at the receiver
   */
  virtual ResponseMessage* createGetSetpointResponse(const QByteArray &data, const QUrl &url = {"/setpoint"}) = 0;

  /**
   * @brief createPutSetpointRequest Returns a RequestMessage configured
   * for a specified '/setpoint/{changeType}' URL path and the 'PUT' HTTP Method.
   * This interface typically causes a change to the setpoint of a device
   * and may specify additional parameters.
   *
   * The implementation will need to map from the setpoint change types
   * to the correct URL path, e.g., /setpoint/warmer, and map the parameters
   * appropriately (some could be data, others URL query parameters).
   *
   * Consider that the Smart Home System tries to maintain a consistent
   * REST API across its devices, so this generalisation can be made.
   * Also, consider that some concrete implementations of the MessageFactory
   * may be specific to certain devices (or sets of devices).
   *
   * @param changeType the type of change to be made to the setpoint
   * @param parameters (optional) additional parameters for the request, e.g., 'amount'
   * @return request for PUT /setpoint/... given a specified state and (optional) parameters
   */
  virtual RequestMessage* createPutSetpointRequest(const SetpointChange &changeType,
                                                   const QMap<QString, QVariant> &parameters = QMap<QString, QVariant>{}) = 0;

  /**
   * @brief createPutSetpointRequest Returns a RequestMessage built at the
   * receiving application when a PUT /setpoint/{changeType} request is received.
   *
   * The implementation will need to map from the URL path to the setpoint change
   * types, e.g., /setpoint/warmer, and map the parameters appropriately such
   * that the application entity is a QMap<QString, QVariant> object.
   *
   * @param path the URL Path for which the request was received
   * @param data the data from the underlying HTTP response, most likely empty
   * @return request for PUT /setpoint/... built at the receiver
   */
  virtual RequestMessage* createPutSetpointRequest(const QUrl &path, const QByteArray &data) = 0;

  /**
   * @brief createPutSetpointResponse Returns a ResponseMessage for the
   * PUT /setpoint/... group of URL Paths.
   *
   * A successful PUT will result in a No Content response.
   * A failed PUT will result in Bad Request response (the provided
   * parameters could not be understood, or were not provided, etc.).
   * Occurrence of a failure is indicated by a non-empty @a errorMessage.
   *
   * (The error message is useful when testing from a browser)
   *
   * @param errorMessage indicating the cause of the failure
   * @return response for PUT /setpoint/...
   */
  virtual ResponseMessage* createPutSetpointResponse(const QString &errorMessage = "") = 0;

  /**
   * @brief createPutSetpointResponse Returns a ResponseMessage for the
   * PUT /setpoint/... group of URL Paths that is built at the receiving application.
   *
   * Empty data indicates a successful No Content response.
   * If data is present, it will be intepreted as an error message (plain text)
   * for a Bad Request response.
   *
   * (The error message may be logged)
   *
   * @param data empty data for success, error message on failure
   * @param url (optional) the request url if desired
   * @return response for PUT /setpoint/... built at the receiver
   */
  virtual ResponseMessage* createPutSetpointResponse(const QByteArray &data, const QUrl &url = {"/setpoint"}) = 0;


  /**
   * @brief createGetUsageRequest Returns a RequestMessage configured
   * for '/usage' URL path and the 'GET' HTTP Method.
   *
   * (This request contains no data and can be used at both sender and receiver)
   *
   * @return request for GET /usage
   */
  virtual RequestMessage* createGetUsageRequest() = 0;

  /**
   * @brief createGetUsageResponse Returns a ResponseMessage containing
   * the device's 'usage' related measurement(s).
   *
   * All devices with a 'usage' will have at least one Measurement, an empty
   * list indicates an internal error of the server, so the response status
   * MUST be SERVER_ERROR; otherwise status will be OK.
   *
   * @param usage list of device usage Measurements
   * @return response for GET /usage
   */
  virtual ResponseMessage* createGetUsageResponse(const QList<Measurement*> &usage) = 0;

  /**
   * @brief createGetUsageResponse Returns a ResponseMessage containing
   * the device's 'usage' related measurement(s) that is built at the
   * receiving application.
   *
   * The application entity will contain a (possibly empty) list of deserialised
   * Measurements. If it is empty, the response status MUST be SERVER_ERROR,
   * otherwise it will be OK.
   *
   * @param data the data from the underlying HTTP response
   * @param url (optional) the request url if desired
   * @return response for GET /usage built at the receiver
   */
  virtual ResponseMessage* createGetUsageResponse(const QByteArray &data, const QUrl &url = {"/usage"}) = 0;


  /**
   * @brief createGetDevicesRequest Returns a RequestMessage configured
   * for '/devices' URL path and the 'GET' HTTP Method.
   *
   * (This request contains no data and can be used at both sender and receiver)
   *
   * @return request for GET /devices
   */
  virtual RequestMessage* createGetDevicesRequest() = 0;

  /**
   * @brief createGetDevicesResponse Returns a ResponseMessage containing
   * the information about devices registered at the controller.
   *
   * Response status will always be OK. Empty lists are allowed.
   *
   * @param devices list of device info objects
   * @return response for GET /devices
   */
  virtual ResponseMessage* createGetDevicesResponse(const QList<DeviceInfo*> &devices) = 0;

  /**
   * @brief createGetDevicesResponse Returns a ResponseMessage containing
   * the information about devices registered at the controller that is built at the
   * receiving application.
   *
   * The application entity will contain a (possibly empty) list of deserialised
   * DeviceInfo objects.
   *
   * @param data the data from the underlying HTTP response
   * @param url (optional) the request url if desired
   * @return response for GET /devices built at the receiver
   */
  virtual ResponseMessage* createGetDevicesResponse(const QByteArray &data, const QUrl &url = {"/devices"}) = 0;


  /**
   * @brief createPostDeviceRequest Return a RequestMessage configured
   * for '/devices' URL Path and the 'POST' HTTP Method.
   *
   * @param deviceInfo the name, type, and URL of the device to be registered
   * @return request for POST /devices
   */
  virtual RequestMessage* createPostDeviceRequest(const DeviceInfo* deviceInfo) = 0;

  /**
   * @brief createPostDeviceRequest Returns a RequestMessage built at the
   * receiving application when a POST /devices request is received.
   *
   * The data is expected to be serialised DeviceInfo data, so the applicatation
   * entity will be a single DeviceInfo object.
   * If the data is not a valid serialised DeviceInfo, the application entity will
   * be null/empty.
   *
   * @param data the data from the underlying HTTP response, containing DeviceInfo data
   * @param url (optional) the request url if desired
   * @return request for POST /devices built at the receiver
   */
  virtual RequestMessage* createPostDeviceRequest(const QByteArray &data, const QUrl &url = {"/devices"}) = 0;

  /**
   * @brief createPostDeviceResponse Return a ResponseMessage containing
   * the information about the registered device.
   *
   * Response status will be 'Created', if registration is successful, in
   * which case the orginally provided device information is to be echoed
   * back to the requestor (according to HTTP spec), including the
   * 'last seen' information.
   *
   * No device info indicates the device is already registered and will have
   * a 'No Content' status.
   *
   * Invalid device (e.g., empty 'name', unknown 'type', invalid URL format, etc.)
   * info will return a 'Bad Request' status, with the provided error message or
   * an internally generated one.
   *
   * @param deviceInfo the name, type, URL, and lastSeen details of the registered device
   * @param errorMessage (optional) error message for a Bad Request response
   * @return response for POST /devices
   */
  virtual ResponseMessage* createPostDeviceResponse(const DeviceInfo* deviceInfo,
                                                    const QString &errorMessage = "") = 0;

  /**
   * @brief createPostDeviceResponse Returns a ResponseMessage containing
   * the information about the registered device that is built at the
   * receiving application.
   *
   * Empty data indicates a successful 'No Content' response, meaning that the
   * device is already registered.
   *
   * A valid serialised DeviceInfo object is an OK status and the application
   * entity will be the deserialised DeviceInfo object.
   *
   * An invalid serialised DeviceInfo object is expected to be the error message
   * string of a Bad Request response and the application entity will contain the
   * error message.
   *
   * (The error message may be logged)
   *
   * @param data the data from the underlying HTTP response
   * @param url (optional) the request url if desired
   * @return response for POST /devices built at the receiver
   */
  virtual ResponseMessage* createPostDeviceResponse(const QByteArray &data, const QUrl &url = {"/devices"}) = 0;

  /**
   * @brief createDeleteDeviceRequest Return a RequestMessage configured
   * for '/devices/{name}' URL Path and the 'DELETE' HTTP Method.
   *
   * @param deviceName the name of the device to be unregistered from the controller
   * @return request for DELETE /devices/{name}
   */
  virtual RequestMessage* createDeleteDeviceRequest(const QString &deviceName) = 0;

  /**
   * @brief createDeleteDeviceRequest Returns a RequestMessage built at the
   * receiving application when a DELETE /devices/{name} request is received.
   *
   * The implementation will need to extract the device name/id from the URL
   * path: the application entity will be the extracted name.
   *
   * @param path the URL Path for which the request was received
   * @return request for DELETE /devices/{name} built at the receiver
   */
  virtual RequestMessage* createDeleteDeviceRequest(const QUrl &path) = 0;

  /**
   * @brief createDeleteDeviceResponse Return a ResponseMessage indicating
   * completion of the DELETE /devices/{name} request.
   *
   * Will always have status 'No Content'. Can be used at sender and receiver.
   *
   * @param url (optional) the request url if desired
   * @return response for DELETE /devices/{name}
   */
  virtual ResponseMessage* createDeleteDeviceResponse(const QUrl &url = {"/devices/"}) = 0;


  /**
   * @brief createGenericNotFound Returns a ResponseMessage indicating
   * that the URL could not be found on the server with a human readable
   * message.
   *
   * (This will be useful if testing from your browser as you will at
   * least see some response. For debugging purposes you may pass in
   * a more detailed message string).
   *
   * This should be used whenever the server does not have a mapping for
   * a particular path and is independent of any particular API.
   *
   * @return a generic HTTP 'Not Found' response
   */
  virtual ResponseMessage* createGenericNotFound(const QUrl &url, const QString &message = "Not Found") = 0;
};

} // namespace network

#endif // MESSAGEFACTORY_H
