#ifndef RESPONSESTUB_H
#define RESPONSESTUB_H

#include "network/responsemessage.h"

class ResponseStub : public network::ResponseMessage
{
public:
  ResponseStub(const QUrl &url, const QString &entity);
  ResponseStub(const QUrl &url, const QByteArray &data);

  // Message interface
public:
  QByteArray data() const override;
  QVariant entity() const override;

private:
  QString _data;

};

#endif // RESPONSESTUB_H
