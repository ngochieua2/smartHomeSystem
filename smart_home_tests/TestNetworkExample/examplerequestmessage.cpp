#include "examplerequestmessage.h"


ExampleRequestMessage::ExampleRequestMessage(const QString &urlPath)
  : RequestMessage{urlPath, GET}, _data{}, _entity{}
{
  _headers["Content-Type"] = "text/plain";
  _headers["Accept"] = "text/plain";
}

ExampleRequestMessage::ExampleRequestMessage(const QString &name, const QString &urlPath)
  : RequestMessage{urlPath, (name.isEmpty() ? GET : POST)}, _data{}, _entity{name}
{
  _headers["Content-Type"] = "text/plain";
  // This is just an example of "converting" the message into the data.
  // Note: does not have to be done in the constructor.
  // The original string is available as the 'entity'
  _data.append(name);
}

ExampleRequestMessage::ExampleRequestMessage(const QByteArray &data, const QString &urlPath)
  : RequestMessage{urlPath, (data.isEmpty() ? GET : POST)}, _data{data}, _entity{}
{
  _headers["Content-Type"] = "text/plain";
  // We recover the original 'entity' from the data
  // There is a constructor for creating a String from a QByteArray
  _entity = QString{_data};
}

QString ExampleRequestMessage::name() const {
  return _entity.toString();
}

QByteArray ExampleRequestMessage::data() const {
  return _data;
}

QVariant ExampleRequestMessage::entity() const
{
  return _entity;
}
