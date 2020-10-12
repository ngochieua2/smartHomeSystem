#ifndef MAINMENU_H
#define MAINMENU_H

#include <QString>
#include <QStringList>
#include <QTextStream>

// DELETE THESE INCLUDES WHEN YOU ARE NO LONGER USING THE NETWORK MANAGER EXAMPLE
#include "network/requestmessage.h"
#include "network/responsemessage.h"
#include "network/qthttpnetworkmanager.h"
#include "network/defaultmessagefactory.h"
#include <QSharedPointer>

class MainMenu : public QObject
{
  Q_OBJECT
public:
  explicit MainMenu(QTextStream &display, QTextStream &input, QObject *parent = nullptr);
  virtual ~MainMenu() = default;

  /**
   * @brief displayWelcome display an intial welcome message including the
   * student's name and game title.
   * @param author the name of the student
   * @param title the name of the game
   */
  void displayWelcome(const QString &title, const QString &group, const QStringList &members) const;

public slots:
  /**
   * @brief run Begin executing the main menu.
   *
   * This is a slot so that it can be called on thread start. Refer to the main function to see how this works.
   */
  void run();

private:
  QTextStream &_display;
  QTextStream &_input;

  // Delete the below once you are done using it as an example of how to set up and use
  // the NetworkManager. The Unit Tests also show similar, but this is less cluttered.
private:
  void exampleNetworkManagerUsage();
  network::DefaultMessageFactory _factory{};
  network::QtHttpNetworkManager* _manager{};

private slots:
  void handleRequest(QSharedPointer<network::RequestMessage> request);
  void handleResponse(QSharedPointer<network::ResponseMessage> response);
};

#endif // MAINMENU_H
