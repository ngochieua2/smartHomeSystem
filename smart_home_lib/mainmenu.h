#ifndef MAINMENU_H
#define MAINMENU_H

#include <QString>
#include <QStringList>
#include <QTextStream>

#include <smarthomecontroller.h>
#include <deviceproxy.h>


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

  //Specific menu
  void configMenu(QString type);
  void controllerMenuInterface();
  void lightSwitchMenuInterface();
  void spinklerMenuInterface();
  void thermostatMenuInterface();

private:
  QTextStream &_display;
  QTextStream &_input;

  QString _id{};
  QString _Url{};
  SmartHomeController* _controller{nullptr};
  QList<deviceProxy*> _DeviceProxyList{};

};

#endif // MAINMENU_H
