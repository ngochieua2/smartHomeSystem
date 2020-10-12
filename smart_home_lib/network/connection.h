#ifndef CONNECTION_H
#define CONNECTION_H

#include <QMetaType>
#include <QHostAddress>
#include <QString>

namespace network {

/**
 * @brief The Connection struct simply holds network details
 * of a named connection and is used by the NetworkManager to
 * track its known communication partners.
 */
struct Connection
{
  QString id;
  QHostAddress address;
  quint16 port;
};


} // namespace network

// Makes the class usable with QVariant
Q_DECLARE_METATYPE(network::Connection)

#endif // CONNECTION_H
