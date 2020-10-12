#include "message.h"

using network::Message;


Message::Message(const QString &urlPath)
  : _urlPath{QUrl{urlPath}.path()}, _headers{}
{
  // Nothing special
}

Message::Message(const QUrl &url)
  : _urlPath{url.path()}, _headers{}
{
  // Nothing special
}

const QString &Message::urlPath() const {
  return _urlPath;
}

const QMap<QString, QString> &Message::headers() const {
  return _headers;
}

QString &Message::operator[](const QString &key) {
  return _headers[key];
}

const QString Message::operator[](const QString &key) const {
  return _headers[key];
}

