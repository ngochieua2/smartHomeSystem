#ifndef MESSAGESTUB_H
#define MESSAGESTUB_H

#include "network/message.h"
#include <QByteArray>
#include <QVariant>

/**
 * @brief The MessageStub class is a simple stub to test the
 * core aspects of network::Message that are implemented directly
 * at the level of the abstract class.
 */
class MessageStub : public network::Message {
public:
  MessageStub(const QString& path);
  MessageStub(const QUrl& url);
  virtual ~MessageStub() override = default;

  virtual QByteArray data() const override;

  virtual QVariant entity() const override;
};

#endif // MESSAGESTUB_H
