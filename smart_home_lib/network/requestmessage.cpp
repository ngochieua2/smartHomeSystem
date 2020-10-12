#include "requestmessage.h"

using network::RequestMessage;

RequestMessage::RequestMessage(const QString &urlPath, network::HttpMethod httpMethod)
  : Message{urlPath}, _queryParameters{QUrl{urlPath}}, _method{httpMethod}
{}

RequestMessage::RequestMessage(const QUrl &url, network::HttpMethod httpMethod)
  : Message{url}, _queryParameters{url}, _method{httpMethod}
{}

network::HttpMethod RequestMessage::httpMethod() const
{
  return _method;
}

QByteArray RequestMessage::data() const
{
  // Simple GET messages contain no data
  return QByteArray{};
}

QVariant RequestMessage::entity() const
{
  return QVariant{};
}

QList<QPair<QString, QString>> RequestMessage::queryParameters() const
{
  return _queryParameters.queryItems();
}

void RequestMessage::applyQueryParameters(QUrl &url) const
{
  url.setQuery(_queryParameters);
}

void RequestMessage::addQueryParameter(const QString &name, const QString &value)
{
  _queryParameters.addQueryItem(name, value);
}
