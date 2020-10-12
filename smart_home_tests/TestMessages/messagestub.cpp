#include "messagestub.h"

MessageStub::MessageStub(const QString &path) : network::Message{path} {}

MessageStub::MessageStub(const QUrl &url) : network::Message{url} {}

QByteArray MessageStub::data() const {
  /* do nothing */
  return QByteArray{};
}

QVariant MessageStub::entity() const
{
  return QVariant{};
}
