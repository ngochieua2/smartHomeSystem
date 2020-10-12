#include "exampleresponsemessage.h"


ExampleResponseMessage::ExampleResponseMessage(const QString &urlPath, StatusCode status, const QString &name)
  : ResponseMessage{urlPath, status}, _name{name}
{
  _headers["Content-Type"] = "text/plain";
  // We convert to the data when calling the data() function. So no need to do anything here.
  // For illustration purposes we do this the opposite to the ExampleRequestMessage.
}

ExampleResponseMessage::ExampleResponseMessage(const QByteArray &data, const QString &urlPath, StatusCode status)
  : ResponseMessage{urlPath, status}, _name{}
{
  _headers["Content-Type"] = "text/plain";

  // Extract the name from the received data.
  QString allData{data};
  if (allData != QStringLiteral("Hello World!")) {
    int nameStart{allData.indexOf(' ') + 1};
    // Retrieve the text after the first space, excluding the final exclamation mark
    // i.e., "Hello Matt!" => "Matt"
    _name = allData.mid(nameStart, allData.size() - 1 - nameStart);
  }
}

QString ExampleResponseMessage::name() const {
  return _name;
}

QByteArray ExampleResponseMessage::data() const {
  QByteArray data{};
  if (_name.isEmpty()) {
    data.append("Hello World!");
  }
  else {
    data.append("Hello ").append(_name).append('!');
  }
  return data;
}

QVariant ExampleResponseMessage::entity() const
{
  // Or we can do things the other way around. Give a concrete form
  // internally and make it a QVariant when it is retrieved.
  return QVariant{_name};
}
