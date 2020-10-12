#ifndef FAKEMESSAGEFACTORY_H
#define FAKEMESSAGEFACTORY_H

#include "network/defaultmessagefactory.h"

class FakeMessageFactory : public network::DefaultMessageFactory
{
public:

  // MessageFactory interface
public:
  network::RequestMessage *createPutStateRequest(const AllowedStates &state, const QMap<QString, QVariant> &parameters) override;
  network::RequestMessage *createPutStateRequest(const QUrl &path, const QByteArray &data) override;
  network::ResponseMessage *createPutStateResponse(const QString &errorMessage = "") override;
  network::ResponseMessage *createPutStateResponse(const QByteArray &data, const QUrl &url = {"/state"}) override;
};

#endif // FAKEMESSAGEFACTORY_H
