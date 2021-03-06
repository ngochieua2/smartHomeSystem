#ifndef MAINMENU_H
#define MAINMENU_H

#include <QString>
#include <QStringList>
#include <QTextStream>

#include <controllermenu.h>
#include <lightswitchmenu.h>
#include <thermostatmenu.h>
#include <sprinklersystemmenu.h>

#include <realcontroller.h>
#include <reallightswitch.h>
#include <realthermostat.h>
#include <realsprinklersystem.h>

#include <lightswitchfactory.h>
#include <thermostatfactory.h>
#include <sprinklersystemfactory.h>


class MainMenu : public QObject
{
  Q_OBJECT
public:
  explicit MainMenu(QTextStream &display, QTextStream &input, QObject *parent = nullptr);
  virtual ~MainMenu() = default;

  /*!
   * @brief displayWelcome display an intial welcome message including the
   * student's name and game title.
   * @param author the name of the student
   * @param title the name of the game
   */
  void displayWelcome(const QString &title, const QString &group, const QStringList &members) const;
  /*!
   * @brief configMenu call menu to config devices and controller
   * @param type
   */
  void configMenu(QString type);
  /*!
   * @brief isExist return true if new name or id is same with other name
   * it is usd to make sure id or name must be unique
   * @param id
   * @return boolean
   */
  bool isExist(QString id);

public slots:
  /*!
   * @brief run Begin executing the main menu.
   *
   * This is a slot so that it can be called on thread start. Refer to the main function to see how this works.
   */
  void run();


private:
  QTextStream &_display;
  QTextStream &_input;

  ControllerMenu* _controllerMenu{nullptr};
  LightSwitchMenu* _lightSwitchMenu{nullptr};
  ThermostatMenu* _thermostatMenu{nullptr};
  SprinklerSystemMenu* _spinklerSystemMenu{nullptr};

  RealController* _controller{nullptr};
  SmartHomeDevice* _device{nullptr};
  RealLightSwitch* _realLightSwitch{nullptr};
  RealThermostat* _realThermostat{nullptr};
  RealSprinklerSystem* _realSprinkerSystem{nullptr};

  QList <QPair<QString, QUrl>> tempLightSwitch{};
  QList <QPair<QString, QUrl>> tempThermostat{};
  QList <QPair<QString, QUrl>> tempSprinklerSystem{};

  DeviceFactory* _factory{nullptr};

};

#endif // MAINMENU_H
