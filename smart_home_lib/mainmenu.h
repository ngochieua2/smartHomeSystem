#ifndef MAINMENU_H
#define MAINMENU_H

#include <QString>
#include <QStringList>
#include <QTextStream>

#include <controllermenu.h>
#include <lightswitchmenu.h>
//#include <smarthomecontroller.h>
#include <realcontroller.h>
#include <reallightswitch.h>

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

private:
  QTextStream &_display;
  QTextStream &_input;

  ControllerMenu* _controllerMenu{nullptr};
  LightSwitchMenu* _lightSwitchMenu{nullptr};

  RealController* _controller{nullptr};
  SmartHomeDevice* _device{nullptr};
  RealLightSwitch* _realLightSwitch{nullptr};

  QList <QPair<QString, QUrl>> tempLightSwitch{};


};

#endif // MAINMENU_H
