#include "fakemessagefactory.h"

#include "requeststub.h"
#include "responsestub.h"

network::RequestMessage *FakeMessageFactory::createPutStateRequest(const AllowedStates &state, const QMap<QString, QVariant> &parameters)
{
  // Better to use QUrl, but this is a quick and dirty test
  QString path{"/state"};
  if (not state.isEmpty()) path.append('/').append(state);
  return new RequestStub{path, parameters["data"].toString()};
}

network::RequestMessage *FakeMessageFactory::createPutStateRequest(const QUrl &path, const QByteArray &data)
{
  return new RequestStub{path, data};
}

network::ResponseMessage *FakeMessageFactory::createPutStateResponse(const QString &errorMessage)
{
  return new ResponseStub{QUrl{"/state"}, errorMessage};
}

network::ResponseMessage *FakeMessageFactory::createPutStateResponse(const QByteArray &data, const QUrl &url)
{
  return new ResponseStub{url, data};
}
