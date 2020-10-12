#ifndef EXAMPLEREQUESTMESSAGE_H
#define EXAMPLEREQUESTMESSAGE_H

#include <QByteArray>
#include <QString>
#include <QVariant>
#include "network/requestmessage.h"
#include "network/responsemessage.h"

using namespace network;

// The following is an example request message class used by the example.
// The idea is to push the data processing into the message as much as
// possible, to hide the HTTP specific aspects.

class ExampleRequestMessage : public RequestMessage {
public:
  /// Simple constructor, GET request with no content. (GET's cannot have content)
  ExampleRequestMessage(const QString &urlPath = QStringLiteral("/"));

  /// Request containing the "name". Since this sends data it is a POST request type.
  /// The "name" string is the application object for the message.
  ExampleRequestMessage(const QString &name,
                        const QString &urlPath);

  /// Request built from the data itself. If the data is empty assume a simple GET,
  /// otherwise it must have been a POST request.
  ExampleRequestMessage(const QByteArray &data,
                        const QString &urlPath = QStringLiteral("/"));

  ~ExampleRequestMessage() override = default;

  /// Retrieve the application object, convenience function
  QString name() const;

  /// Retrieve the underlying data.
  QByteArray data() const override;

  /// Retrieve the application data entity
  QVariant entity() const override;

private:
  QByteArray _data;
  QVariant _entity;
};

#endif // EXAMPLEREQUESTMESSAGE_H
