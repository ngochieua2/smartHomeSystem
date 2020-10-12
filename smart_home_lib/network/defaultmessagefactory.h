#ifndef DEFAULTMESSAGEFACTORY_H
#define DEFAULTMESSAGEFACTORY_H

#include "messagefactory.h"
#include "requestmessage.h"
#include "responsemessage.h"

namespace network {

/**
 * @brief The DefaultMessageFactory class implements the entire interface
 * to return "empty" Requests and Responses.
 *
 * Responses actually produce "Not Implemented" statuses.
 *
 * The template parameters are simply QStrings for direct mapping, but you
 * can change this to suit if you would like to inherit from this class so
 * that you only have to implement a few factory methods at a time.
 */
class DefaultMessageFactory : public MessageFactory<QString, QString>
{
public:
  DefaultMessageFactory() = default;
  ~DefaultMessageFactory() override = default;

  // MessageFactory interface
public:
  RequestMessage *createGetStateRequest() override;
  ResponseMessage *createGetStateResponse(const QList<Measurement *> &state, const QString &errorMessage = "") override;
  ResponseMessage *createGetStateResponse(const QByteArray &data, const QUrl &url = {"/state"}) override;
  RequestMessage *createPutStateRequest(const AllowedStates &state, const QMap<QString, QVariant> &parameters) override;
  RequestMessage *createPutStateRequest(const QUrl &path, const QByteArray &data) override;
  ResponseMessage *createPutStateResponse(const QString &errorMessage = "") override;
  ResponseMessage *createPutStateResponse(const QByteArray &data, const QUrl &url = {"/state"}) override;
  RequestMessage *createGetMeasurementsRequest(bool mostRecentOnly, const QMap<QString, QVariant> &filters) override;
  RequestMessage *createGetMeasurementsRequest(const QUrl &path, const QByteArray &data) override;
  ResponseMessage *createGetMeasurementsResponse(const QList<Measurement *> &measurements) override;
  ResponseMessage *createGetMeasurementsResponse(const QByteArray &data, const QUrl &url = {"/measurements"}) override;
  RequestMessage *createPostMeasurementsRequest(const QList<Measurement *> &measurements) override;
  RequestMessage *createPostMeasurementsRequest(const QByteArray &data, const QUrl &url = {"/measurements"}) override;
  ResponseMessage *createPostMeasurementsResponse(const QString &errorMessage = "") override;
  ResponseMessage *createPostMeasurementsResponse(const QByteArray &data, const QUrl &url = {"/measurements"}) override;
  RequestMessage *createGetSetpointRequest() override;
  ResponseMessage *createGetSetpointResponse(const Measurement *setpoint) override;
  ResponseMessage *createGetSetpointResponse(const QByteArray &data, const QUrl &url = {"/setpoint"}) override;
  RequestMessage *createPutSetpointRequest(const SetpointChange &changeType, const QMap<QString, QVariant> &parameters) override;
  RequestMessage *createPutSetpointRequest(const QUrl &path, const QByteArray &data) override;
  ResponseMessage *createPutSetpointResponse(const QString &errorMessage = "") override;
  ResponseMessage *createPutSetpointResponse(const QByteArray &data, const QUrl &url = {"/setpoint"}) override;
  RequestMessage *createGetUsageRequest() override;
  ResponseMessage *createGetUsageResponse(const QList<Measurement *> &usage) override;
  ResponseMessage *createGetUsageResponse(const QByteArray &data, const QUrl &url = {"/usage"}) override;
  RequestMessage *createGetDevicesRequest() override;
  ResponseMessage *createGetDevicesResponse(const QList<DeviceInfo *> &devices) override;
  ResponseMessage *createGetDevicesResponse(const QByteArray &data, const QUrl &url = {"/usage"}) override;
  RequestMessage *createPostDeviceRequest(const DeviceInfo *deviceInfo) override;
  RequestMessage *createPostDeviceRequest(const QByteArray &data, const QUrl &url = {"/devices"}) override;
  ResponseMessage *createPostDeviceResponse(const DeviceInfo *deviceInfo, const QString &errorMessage = "") override;
  ResponseMessage *createPostDeviceResponse(const QByteArray &data, const QUrl &url = {"/devices"}) override;
  RequestMessage *createDeleteDeviceRequest(const QString &deviceName) override;
  RequestMessage *createDeleteDeviceRequest(const QUrl &path) override;
  ResponseMessage *createDeleteDeviceResponse(const QUrl &url = {"/devices"}) override;
  ResponseMessage *createGenericNotFound(const QUrl &url, const QString &message = "Not Found") override;
};

} // namespace network

#endif // DEFAULTMESSAGEFACTORY_H
