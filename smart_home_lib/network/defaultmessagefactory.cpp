#include "defaultmessagefactory.h"

network::RequestMessage *network::DefaultMessageFactory::createGetStateRequest()
{
  return new RequestMessage("/state");
}

network::ResponseMessage *network::DefaultMessageFactory::createGetStateResponse([[maybe_unused]] const QList<Measurement *> &state, [[maybe_unused]] const QString &errorMessage)
{
  return new ResponseMessage("/state", StatusCode::NOT_IMPLEMENTED);
}

network::ResponseMessage *network::DefaultMessageFactory::createGetStateResponse([[maybe_unused]] const QByteArray &data, const QUrl &url)
{
  return new ResponseMessage(url, StatusCode::NOT_IMPLEMENTED);
}

network::RequestMessage *network::DefaultMessageFactory::createPutStateRequest([[maybe_unused]] const AllowedStates &state, [[maybe_unused]] const QMap<QString, QVariant> &parameters)
{
  return new RequestMessage("/state", HttpMethod::PUT);
}

network::RequestMessage *network::DefaultMessageFactory::createPutStateRequest([[maybe_unused]] const QUrl &path, [[maybe_unused]] const QByteArray &data)
{
  return new RequestMessage("/state", HttpMethod::PUT);
}

network::ResponseMessage *network::DefaultMessageFactory::createPutStateResponse([[maybe_unused]] const QString &errorMessage)
{
  return new ResponseMessage("/state", StatusCode::NOT_IMPLEMENTED);
}

network::ResponseMessage *network::DefaultMessageFactory::createPutStateResponse([[maybe_unused]] const QByteArray &data, const QUrl &url)
{
  return new ResponseMessage(url, StatusCode::NOT_IMPLEMENTED);
}

network::RequestMessage *network::DefaultMessageFactory::createGetMeasurementsRequest([[maybe_unused]] bool mostRecentOnly, [[maybe_unused]] const QMap<QString, QVariant> &filters)
{
  return new RequestMessage("/measurements");
}

network::RequestMessage *network::DefaultMessageFactory::createGetMeasurementsRequest([[maybe_unused]] const QUrl &path, [[maybe_unused]] const QByteArray &data)
{
  return new RequestMessage("/measurements");
}

network::ResponseMessage *network::DefaultMessageFactory::createGetMeasurementsResponse([[maybe_unused]] const QList<Measurement *> &measurements)
{
  return new ResponseMessage("/measurements", StatusCode::NOT_IMPLEMENTED);
}

network::ResponseMessage *network::DefaultMessageFactory::createGetMeasurementsResponse([[maybe_unused]] const QByteArray &data, const QUrl &url)
{
  return new ResponseMessage(url, StatusCode::NOT_IMPLEMENTED);
}

network::RequestMessage *network::DefaultMessageFactory::createPostMeasurementsRequest([[maybe_unused]] const QList<Measurement *> &measurements)
{
  return new RequestMessage("/measurements", HttpMethod::POST);
}

network::RequestMessage *network::DefaultMessageFactory::createPostMeasurementsRequest([[maybe_unused]] const QByteArray &data, const QUrl &url)
{
  return new RequestMessage(url, HttpMethod::POST);
}

network::ResponseMessage *network::DefaultMessageFactory::createPostMeasurementsResponse([[maybe_unused]] const QString &errorMessage)
{
  return new ResponseMessage("/measurements", StatusCode::NOT_IMPLEMENTED);
}

network::ResponseMessage *network::DefaultMessageFactory::createPostMeasurementsResponse([[maybe_unused]] const QByteArray &data, const QUrl &url)
{
  return new ResponseMessage(url, StatusCode::NOT_IMPLEMENTED);
}

network::RequestMessage *network::DefaultMessageFactory::createGetSetpointRequest()
{
  return new RequestMessage("/setpoint");
}

network::ResponseMessage *network::DefaultMessageFactory::createGetSetpointResponse([[maybe_unused]] const Measurement *setpoint)
{
  return new ResponseMessage("/setpoint", StatusCode::NOT_IMPLEMENTED);
}

network::ResponseMessage *network::DefaultMessageFactory::createGetSetpointResponse([[maybe_unused]] const QByteArray &data, const QUrl &url)
{
  return new ResponseMessage(url, StatusCode::NOT_IMPLEMENTED);
}

network::RequestMessage *network::DefaultMessageFactory::createPutSetpointRequest([[maybe_unused]] const SetpointChange &changeType, [[maybe_unused]] const QMap<QString, QVariant> &parameters)
{
  return new RequestMessage("/setpoint", HttpMethod::PUT);
}

network::RequestMessage *network::DefaultMessageFactory::createPutSetpointRequest([[maybe_unused]] const QUrl &path, [[maybe_unused]] const QByteArray &data)
{
  return new RequestMessage("/setpoint", HttpMethod::PUT);
}

network::ResponseMessage *network::DefaultMessageFactory::createPutSetpointResponse([[maybe_unused]] const QString &errorMessage)
{
  return new ResponseMessage("/setpoint", StatusCode::NOT_IMPLEMENTED);
}

network::ResponseMessage *network::DefaultMessageFactory::createPutSetpointResponse([[maybe_unused]] const QByteArray &data, const QUrl &url)
{
  return new ResponseMessage(url, StatusCode::NOT_IMPLEMENTED);
}

network::RequestMessage *network::DefaultMessageFactory::createGetUsageRequest()
{
  return new RequestMessage("/usage");
}

network::ResponseMessage *network::DefaultMessageFactory::createGetUsageResponse([[maybe_unused]] const QList<Measurement *> &usage)
{
  return new ResponseMessage("/usage", StatusCode::NOT_IMPLEMENTED);
}

network::ResponseMessage *network::DefaultMessageFactory::createGetUsageResponse([[maybe_unused]] const QByteArray &data, const QUrl &url)
{
  return new ResponseMessage(url, StatusCode::NOT_IMPLEMENTED);
}

network::RequestMessage *network::DefaultMessageFactory::createGetDevicesRequest()
{
  return new RequestMessage("/devices");
}

network::ResponseMessage *network::DefaultMessageFactory::createGetDevicesResponse([[maybe_unused]] const QList<DeviceInfo *> &devices)
{
  return new ResponseMessage("/devices", StatusCode::NOT_IMPLEMENTED);
}

network::ResponseMessage *network::DefaultMessageFactory::createGetDevicesResponse([[maybe_unused]] const QByteArray &data, const QUrl &url)
{
  return new ResponseMessage(url, StatusCode::NOT_IMPLEMENTED);
}

network::RequestMessage *network::DefaultMessageFactory::createPostDeviceRequest([[maybe_unused]] const DeviceInfo *deviceInfo)
{
  return new RequestMessage("/devices", HttpMethod::POST);
}

network::RequestMessage *network::DefaultMessageFactory::createPostDeviceRequest([[maybe_unused]] const QByteArray &data, const QUrl &url)
{
  return new RequestMessage(url, HttpMethod::POST);
}

network::ResponseMessage *network::DefaultMessageFactory::createPostDeviceResponse([[maybe_unused]] const DeviceInfo *deviceInfo, [[maybe_unused]] const QString &errorMessage)
{
  return new ResponseMessage("/devices", StatusCode::NOT_IMPLEMENTED);
}

network::ResponseMessage *network::DefaultMessageFactory::createPostDeviceResponse([[maybe_unused]] const QByteArray &data, const QUrl &url)
{
  return new ResponseMessage(url, StatusCode::NOT_IMPLEMENTED);
}

network::RequestMessage *network::DefaultMessageFactory::createDeleteDeviceRequest([[maybe_unused]] const QString &deviceName)
{
  return new RequestMessage("/devices/", HttpMethod::DELETE);
}

network::RequestMessage *network::DefaultMessageFactory::createDeleteDeviceRequest([[maybe_unused]] const QUrl &path)
{
  return new RequestMessage("/devices/", HttpMethod::DELETE);
}

network::ResponseMessage *network::DefaultMessageFactory::createDeleteDeviceResponse(const QUrl &url)
{
  return new ResponseMessage(url, StatusCode::NOT_IMPLEMENTED);
}

network::ResponseMessage *network::DefaultMessageFactory::createGenericNotFound(const QUrl &url, [[maybe_unused]]  const QString &message)
{
  return new ResponseMessage(url, StatusCode::NOT_FOUND);
}
