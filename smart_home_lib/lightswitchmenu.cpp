#include "lightswitchmenu.h"

#include <QTextStream>
#include <QUrl>
#include <QCoreApplication>

LightSwitchMenu::LightSwitchMenu(QTextStream &display, QTextStream &input, QObject *parent)
  : QObject{parent}, _display{display}, _input{input}
{
}

void LightSwitchMenu::run(LightSwitchProxy* lightSwitchProxy){
    _lightSwitchProxy = lightSwitchProxy;
    while (true) {
        _display << "You are controlling "+ _lightSwitchProxy->getID() +" (light switch)" << endl
             << "What would you like to do?" << endl
             << "1. Turn On" << endl
             << "2. Turn Off" << endl
             << "3. Reduce the brightness level (dim)" << endl
             << "4. Increase the brightness level" << endl
             << "Type (b) to back" << endl;

        QString stringInput;
        stringInput = _input.readLine();
        if(stringInput == "1"){
            _lightSwitchProxy->turnOn();
            break;

        }
        else if (stringInput == "2") {
            _lightSwitchProxy->turnOff();
            break;

        }
        else if (stringInput == "3") {
            _lightSwitchProxy->dim();
            break;
        }
        else if (stringInput == "4") {
            _lightSwitchProxy->brighten();
            break;

        }
        else if (stringInput == "q") {
            break;
        }
        else {
            _display << "Invalid option, please choose other" <<endl;
        }
    }
}

void LightSwitchMenu::showRegisterDevice(LightSwitchProxy *lightSwitchProxy)
{
    lightSwitchProxy->getDeviceInfo();
}
