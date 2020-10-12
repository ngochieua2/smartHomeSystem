#ifndef EXAMPLERESPONSEMESSAGE_H
#define EXAMPLERESPONSEMESSAGE_H

#include <QByteArray>
#include <QString>
#include <QVariant>
#include "network/requestmessage.h"
#include "network/responsemessage.h"

using namespace network;

// The following is an example response message class used by the example.

class ExampleResponseMessage : public ResponseMessage {
public:
  /// Simple constructor, OK with generic response (if no name provided) otherwise
  /// a customised response message.
  ExampleResponseMessage(const QString &urlPath = QStringLiteral("/"),
                         StatusCode status = OK, const QString &name = QStringLiteral(""));

  /// Request built from the data itself. If the data is empty assume a simple GET,
  /// otherwise it must have been a POST request.
  ExampleResponseMessage(const QByteArray &data,
                         const QString &urlPath = QStringLiteral("/"),
                         StatusCode status = OK);

  ~ExampleResponseMessage() override = default;

  /// Retrieve the application object.
  QString name() const;

  /// Retrieve the data for the message exchange.
  QByteArray data() const override;

  /// Retrieve the application data entity
  QVariant entity() const override;

private:
  QString _name;
};

#endif // EXAMPLERESPONSEMESSAGE_H
