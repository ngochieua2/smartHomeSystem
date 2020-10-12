#include "responsestub.h"

ResponseStub::ResponseStub(const QUrl &url, const QString &entity)
  : ResponseMessage{url, network::StatusCode::NOT_IMPLEMENTED}, _data{entity}
{}

ResponseStub::ResponseStub(const QUrl &url, const QByteArray &data)
  : ResponseMessage{url, network::StatusCode::NOT_IMPLEMENTED}, _data{data}
{}


QByteArray ResponseStub::data() const
{
  QByteArray byteData{};
  byteData.append(_data);
  return byteData;
}

QVariant ResponseStub::entity() const
{
  return _data;
}
