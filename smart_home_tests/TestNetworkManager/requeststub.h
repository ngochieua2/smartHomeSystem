#ifndef REQUESTSTUB_H
#define REQUESTSTUB_H

#include "network/requestmessage.h"

#include <QByteArray>
#include <QString>
#include <QUrl>
#include <QVariant>

class RequestStub : public network::RequestMessage
{
public:
  RequestStub(const QUrl &url, const QString &entity);
  RequestStub(const QUrl &url, const QByteArray &data);

  // Message interface
public:
  QByteArray data() const override;
  QVariant entity() const override;

private:
  QString _data;

};

#endif // REQUESTSTUB_H
