#include "requeststub.h"


RequestStub::RequestStub(const QUrl &url, const QString &entity)
  : RequestMessage{url, network::HttpMethod::PUT}, _data{entity}
{
  _headers["Content-Type"] = "text/plain";
}

RequestStub::RequestStub(const QUrl &url, const QByteArray &data)
  : RequestMessage{url, network::HttpMethod::PUT}, _data{data}
{
  _headers["Content-Type"] = "text/plain";
}

QByteArray RequestStub::data() const
{
  QByteArray byteData{};
  byteData.append(_data);
  return byteData;
}

QVariant RequestStub::entity() const
{
  return _data;
}
