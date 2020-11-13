#include "thermostatmenu.h"

#include <QTextStream>
#include <QUrl>
#include <QCoreApplication>


ThermostatMenu::ThermostatMenu(QTextStream &display, QTextStream &input, QObject *parent)
  : QObject{parent}, _display{display}, _input{input}
{
}

void ThermostatMenu::run(){
    while (true) {
        _display << "You are controlling {name}(light switch)" << endl
             << "What would you like to do?" << endl
             << "1. " << endl
             << "2. " << endl
             << "3. " << endl
             << "4. " << endl
             << "5. " << endl
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

void ThermostatMenu::showRegisterDevice(ThermostatProxy* thermostatProxy)
{
    thermostatProxy->getDeviceInfo();
}
