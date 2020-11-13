#include "lightswitchmenu.h"

#include <QTextStream>
#include <QUrl>
#include <QCoreApplication>

LightSwitchMenu::LightSwitchMenu(QTextStream &display, QTextStream &input, QObject *parent)
  : QObject{parent}, _display{display}, _input{input}
{
}

void LightSwitchMenu::run(){
    while (true) {
        _display << "You are controlling {name}(light switch)" << endl
             << "What would you like to do?" << endl
             << "1. Turn On" << endl
             << "2. Turn Off" << endl
             << "3. Reduce the brightness level (dim)" << endl
             << "4. Increase the brightness level" << endl
             << "5. Check current status" << endl
             << "Type (b) to back" << endl;

        QString stringInput;
        stringInput = _input.readLine();
        if(stringInput == "1"){
            _display << "Test" << endl;

        }
        else if (stringInput == "2") {

        }
        else if (stringInput == "3") {

        }
        else if (stringInput == "4") {

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
