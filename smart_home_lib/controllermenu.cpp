#include "controllermenu.h"
#include <QTextStream>
#include <QUrl>
#include <QCoreApplication>

ControllerMenu::ControllerMenu(QTextStream &display, QTextStream &input, QObject *parent)
  : QObject{parent}, _display{display}, _input{input}
{
    _lightSwitchMenu = new  LightSwitchMenu(display, input);
    _thermostatMenu = new ThermostatMenu(display,input);
    _sprinklerSystemMenu = new SprinklerSystemMenu(display, input);
}

void ControllerMenu::run(RealController* controller){
    _controller = controller;
    while (true) {
        _display << "Welcome to controller menu" << endl
                 << "Name controller: " << _controller->getID() << endl
                 << "What would you like to do" << endl
                 << "1.Show all register devices" << endl
                 << "2.Unregister device" << endl
                 << "3.Current State of all devices" << endl
                 << "4.Controll device" << endl
                 << "Type (b) to back" << endl;

        QString stringInput;
        stringInput = _input.readLine();

        if(stringInput == "1") // Show all registed device
        {
            _display << "\nDevice list:";
            // get info from devices
            for(int i = 0; i < _controller->getLightSwitchProxyList().size(); ++i){
                _controller->getLightSwitchProxyList().at(i)->getDeviceInfo();
            }

            for(int i = 0; i < _controller->getThermostatProxyList().size(); ++i){
                _controller->getThermostatProxyList().at(i)->getDeviceInfo();
            }
            for(int i = 0; i < _controller->getSprinklerSystemProxyList().size(); ++i){
                _controller->getSprinklerSystemProxyList().at(i)->getDeviceInfo();
            }

            //Show data
            _display << endl;
            _display << _controller->registerDevice();
        }
        else if (stringInput == "2") // Unregister device
        {
            //Show all registered devices
            // get info from devices
            for(int i = 0; i < _controller->getLightSwitchProxyList().size(); ++i){
                _controller->getLightSwitchProxyList().at(i)->getDeviceInfo();
            }
            for(int i = 0; i < _controller->getThermostatProxyList().size(); ++i){
                _controller->getThermostatProxyList().at(i)->getDeviceInfo();
            }
            for(int i = 0; i < _controller->getSprinklerSystemProxyList().size(); ++i){
                _controller->getSprinklerSystemProxyList().at(i)->getDeviceInfo();
            }

            //Count number of registered device
            int count = _controller->getLightSwitchProxyList().size()
                      + _controller->getThermostatProxyList().size()
                      + _controller->getSprinklerSystemProxyList().size();
            if (count > 0){
                //Show data
                _display << "\nDevice list:";
                _display << endl;
                _display << _controller->registerDevice();
                while (true) {
                    _display << "Which device you want to unregister: (1 to " << count << ")"  << endl;
                    QString optionInput;
                    optionInput = _input.readLine();
                    if(optionInput.toInt() >= 1 && optionInput.toInt() <= count){
                        QString name;
                        int index = optionInput.toInt() - 1;
                        if(optionInput.toInt() <= _controller->getLightSwitchProxyList().size()){
                            name = _controller->getLightSwitchProxyList().at(index)->getID();
                        }
                        else if (optionInput.toInt() <= _controller->getLightSwitchProxyList().size()
                                                      + _controller->getThermostatProxyList().size()){
                            name = _controller->getThermostatProxyList().at(index
                                                                            -_controller->getLightSwitchProxyList().size())->getID();
                        }
                        else {
                            name = _controller->getSprinklerSystemProxyList().at(index
                                                                                 -_controller->getLightSwitchProxyList().size()
                                                                                 -_controller->getThermostatProxyList().size())->getID();
                        }
                        _controller->unregisterDevice(name);
                        _display << "\nThat device has been deleted successfully.\n" <<endl;
                        break;
                    }
                    else{
                        _display << "\nWrong number, choose again\n" <<endl;
                    }
                }
            }
            else {
                _display << "\nThere is no device to remove\n" <<endl;
            }
        }
        else if (stringInput == "3") {
            while (true) {
                _display << "Which device you want to see?" << endl
                         << "1. All devices " << endl
                         << "2. Light Switch " << endl
                         << "3. Thermostat" << endl
                         << "4. Sprinker system" << endl
                         << "5. Searching" << endl
                         << "type (b) to back " << endl;
                QString optionInput;
                optionInput = _input.readLine();
                if(optionInput == "1"){
                    //All device
                    _display << _controller->currentState("", "");
                }
                else if (optionInput == "2") {
                    _display << _controller->currentState("", "lightSwitch");
                }
                else if (optionInput == "3") {
                    _display << _controller->currentState("", "thermostat");
                }
                else if (optionInput == "4") {

                    _display << _controller->currentState("", "sprinklerSystem");
                }
                else if (optionInput == "5") {
                    _display << "Enter the device name you want to search: " << endl;
                    QString aname{};
                    while (true) {
                        QString getName = _input.readLine();
                        if(getName.isEmpty()){
                            _display << "Name cannot be empty" << endl;
                        }
                        else {
                            aname = getName;
                            break;
                        }
                    }
                    while (true) {
                        _display << "\nWhich device you want to search?" << endl
                                 << "1. All devices " << endl
                                 << "2. Light Switch " << endl
                                 << "3. Thermostat" << endl
                                 << "4. Sprinker system" << endl
                                 << "type (b) to back " << endl;
                        QString option;
                        option = _input.readLine();
                        if(option == "1"){
                            _display << _controller->currentState(aname, "");
                            break;
                        }
                        else if (option == "2") {
                            _display << _controller->currentState(aname, "lightSwitch");
                            break;
                        }
                        else if (option == "3") {
                            _display << _controller->currentState(aname, "thermostat");
                            break;
                        }
                        else if (option == "4") {
                            _display << _controller->currentState(aname, "sprinklerSystem");
                            break;
                        }
                        else if (option == "b" ) {
                            break;
                        }
                        else {
                            _display << "\nWrong option, please choose again\n" << endl;
                        }
                    }
                }
                else if (optionInput == "b") {
                    break;
                }
                else {
                    _display << "\nWrong option, please choose again\n" << endl;
                }
            }
        }
        else if (stringInput == "4") {

            int count = _controller->getLightSwitchProxyList().size()
                      + _controller->getThermostatProxyList().size()
                      + _controller->getSprinklerSystemProxyList().size();
            if (count > 0){

                while (true) {
                    _display << _controller->currentState("", "");
                    _display << "Which device you want to controll: (1 to " << count << ")"  << endl;
                    _display << "Choose b to back"  << endl;
                    QString optionInput;
                    optionInput = _input.readLine();
                    if(optionInput.toInt() >= 1 && optionInput.toInt() <= count){

                        int index = optionInput.toInt() - 1;

                        if(optionInput.toInt() <= _controller->getLightSwitchProxyList().size()){
                            _lightSwitchProxy = _controller->getLightSwitchProxyList().at(index);
                            _thermostatProxy = nullptr;
                            _sprinkerSystemProxy = nullptr;
                        }
                        else if (optionInput.toInt() <= _controller->getLightSwitchProxyList().size()
                                                      + _controller->getThermostatProxyList().size()){
                            _thermostatProxy = _controller->getThermostatProxyList().at(index -_controller->getLightSwitchProxyList().size());
                            _lightSwitchProxy = nullptr;
                            _sprinkerSystemProxy = nullptr;
                        }
                        else {
                            _sprinkerSystemProxy = _controller->getSprinklerSystemProxyList().at(index
                                                                                 -_controller->getLightSwitchProxyList().size()
                                                                                 -_controller->getThermostatProxyList().size());
                            _lightSwitchProxy = nullptr;
                            _thermostatProxy = nullptr;
                        }
                        //Access menu device
                        bool run = true;
                        while (run) {
                            if(_lightSwitchProxy != nullptr){
                                _lightSwitchMenu->run(_lightSwitchProxy);
                            }
                            else if (_thermostatProxy != nullptr) {
                                _thermostatMenu->run(_thermostatProxy);
                            }
                            else if (_sprinkerSystemProxy != nullptr) {
                                _sprinklerSystemMenu->run(_sprinkerSystemProxy);
                            }
                            _display << "Current state: " << endl;
                            _display << _controller->getUpdateMeasurement();
                            _display << "Do you want to continue controll this device? (y) or (n)" << endl
                                     <<  "1. Yes            2. No"<< endl;
                            while (true) {
                                QString option;
                                option = _input.readLine();
                                if (option  == "n"){
                                    run = false;
                                    break;
                                }
                                else if (option  == "y") {
                                    break;
                                }
                                else {
                                    _display << "\nWrong option, please choose again\n" << endl;
                                }
                            }
                        }
                    }
                    else if (optionInput == "b") {
                        break;
                    }
                    else{
                        _display << "\nWrong number, choose again\n" <<endl;
                    }
                }
            }
            else {
                _display << "\nThere is no device to controll\n" << endl;
            }
        }
        else if (stringInput == "b") {
            break;
        }
        else {
            _display << "\nInvalid option, please choose other\n" <<endl;
        }
    }
}
