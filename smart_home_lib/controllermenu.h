#ifndef CONTROLLERMENU_H
#define CONTROLLERMENU_H

#include <QString>
#include <QStringList>
#include <QTextStream>
#include <realcontroller.h>
#include <lightswitchmenu.h>
#include <thermostatmenu.h>
#include <sprinklersystemmenu.h>


class ControllerMenu : public QObject
{
    Q_OBJECT
public:
    explicit ControllerMenu(QTextStream &display, QTextStream &input, QObject *parent = nullptr);
    virtual ~ControllerMenu() = default;

    /*!
     * @brief implement the interface of controller menu
     * @param real controller has been set up with device proxy
     */
    void run(RealController* controller);


private:
  QTextStream &_display;
  QTextStream &_input;

  RealController* _controller{nullptr};

  LightSwitchMenu* _lightSwitchMenu{nullptr};
  ThermostatMenu* _thermostatMenu{nullptr};
  SprinklerSystemMenu* _sprinklerSystemMenu{nullptr};

  LightSwitchProxy* _lightSwitchProxy{nullptr};
  ThermostatProxy* _thermostatProxy{nullptr};
  SprinklerSystemProxy* _sprinkerSystemProxy{nullptr};

};

#endif // CONTROLLERMENU_H
