#include "thermostatmenu.h"

#include <QTextStream>
#include <QUrl>
#include <QCoreApplication>


ThermostatMenu::ThermostatMenu(QTextStream &display, QTextStream &input, QObject *parent)
  : QObject{parent}, _display{display}, _input{input}
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),this, SLOT(update()));
    timer->start(3000);
}

void ThermostatMenu::run(ThermostatProxy* thermostatProxy){
    _thermostatProxy = thermostatProxy;
    while (true) {
        _display << "You are controlling: " + _thermostatProxy->getID() + " (Thermostat)" << endl
             << "What would you like to do?" << endl
             << "1. Show last temperature" << endl
             << "2. Show last 5 temperature" << endl
             << "3. Set  desired temperature" << endl
             << "4. Check current state" << endl
             << "5. Make warmer" << endl
             << "6. Make cooler" << endl
             << "Type (b) to back" << endl;

        QString stringInput;
        stringInput = _input.readLine();
        if(stringInput == "1"){
            _thermostatProxy->getLastMeasurement();
            break;
        }
        else if (stringInput == "2") {
            _thermostatProxy->getLast5Measurement();
            break;
        }
        else if (stringInput == "3") {
            bool isNumber = false;
            while (true) {
                _display << "What value you want to set desired temperature??" << endl;
                QString optionInput;
                optionInput = _input.readLine();
                optionInput.toDouble(&isNumber);
                if (isNumber) {
                    double v = optionInput.toDouble();
                    _thermostatProxy->SetPoint(v);
                    break;
                } else {
                  _display << "Please enter a number" << endl;
                }
            }
            break;
        }
        else if (stringInput == "4") {
            _thermostatProxy->getMeasurement();
        }
        else if (stringInput == "5") {
            bool isNumber = false;
            while (true) {
                _display << "How much do you want to warm up??" << endl;
                QString optionInput;
                optionInput = _input.readLine();
                optionInput.toDouble(&isNumber);
                if (isNumber) {
                    double v = optionInput.toDouble();
                    _thermostatProxy->warmer(v);
                    break;
                } else {
                  _display << "Please enter a number" << endl;
                }
            }
            break;
        }
        else if (stringInput == "6") {
            bool isNumber = false;
            while (true) {
                _display << "How much do you want to cool down??" << endl;
                QString optionInput;
                optionInput = _input.readLine();
                optionInput.toDouble(&isNumber);
                if (isNumber) {
                    double v = optionInput.toDouble();
                    _thermostatProxy->cooler(v);
                    break;
                } else {
                  _display << "Please enter a number" << endl;
                }
            }
            break;
        }
        else if (stringInput == "b") {
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

void ThermostatMenu::update()
{
    if(_thermostatProxy != nullptr){
        _thermostatProxy->Update();
    }
}
