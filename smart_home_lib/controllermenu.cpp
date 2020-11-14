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
                //emit showRegisterLightSwitch(_controller->getLightSwitchProxyList().at(i));
                _lightSwitchMenu->showRegisterDevice(_controller->getLightSwitchProxyList().at(i));
            }

            for(int i = 0; i < _controller->getThermostatProxyList().size(); ++i){
                //emit showRegisterThermostat(_controller->getThermostatProxyList().at(i));
                _thermostatMenu->showRegisterDevice(_controller->getThermostatProxyList().at(i));
            }
            for(int i = 0; i < _controller->getSprinklerSystemProxyList().size(); ++i){
                //emit showRegisterThermostat(_controller->getThermostatProxyList().at(i));
                _sprinklerSystemMenu->showRegisterDevice(_controller->getSprinklerSystemProxyList().at(i));
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
                //emit showRegisterLightSwitch(_controller->getLightSwitchProxyList().at(i));
                _lightSwitchMenu->showRegisterDevice(_controller->getLightSwitchProxyList().at(i));
            }

            for(int i = 0; i < _controller->getThermostatProxyList().size(); ++i){
                //emit showRegisterThermostat(_controller->getThermostatProxyList().at(i));
                _thermostatMenu->showRegisterDevice(_controller->getThermostatProxyList().at(i));
            }
            for(int i = 0; i < _controller->getSprinklerSystemProxyList().size(); ++i){
                //emit showRegisterThermostat(_controller->getThermostatProxyList().at(i));
                _sprinklerSystemMenu->showRegisterDevice(_controller->getSprinklerSystemProxyList().at(i));
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
                        _display << "That device has been deleted successfully.\n" <<endl;
                        break;
                    }
                    else{
                        _display << "Wrong number, choose again" <<endl;
                    }
                }
            }
            else {
                _display << "\nThere is no device to remove\n" <<endl;
            }
        }
        else if (stringInput == "3") {
            while (true) {
                _display << "\nWhich device you want to see?" << endl
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
                    _display << _controller->currentState("", "All");

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

                }
                else if (optionInput == "b") {
                    break;
                }
                else {
                    _display << "Wrong option, please choose again" << endl;
                }
            }
        }
        else if (stringInput == "4") {
            int count = _controller->getLightSwitchProxyList().size()
                      + _controller->getThermostatProxyList().size()
                      + _controller->getSprinklerSystemProxyList().size();
            if (count > 0){

                while (true) {
                    _display << _controller->currentState("", "All");
                    _display << "Which device you want to controll: (1 to " << count << ")"  << endl;
                    _display << "Choose b to back"  << endl;
                    QString optionInput;
                    optionInput = _input.readLine();
                    if(optionInput.toInt() >= 1 && optionInput.toInt() <= count){

                        int index = optionInput.toInt() - 1;

                        if(optionInput.toInt() <= _controller->getLightSwitchProxyList().size()){
                            _lightSwitchProxy = _controller->getLightSwitchProxyList().at(index);
                        }
                        else if (optionInput.toInt() <= _controller->getLightSwitchProxyList().size()
                                                      + _controller->getThermostatProxyList().size()){
//                            name = _controller->getThermostatProxyList().at(index
//                                                                            -_controller->getLightSwitchProxyList().size())->getID();
                        }
                        else {
//                            name = _controller->getSprinklerSystemProxyList().at(index
//                                                                                 -_controller->getLightSwitchProxyList().size()
//                                                                                 -_controller->getThermostatProxyList().size())->getID();
                        }

                        //Access menu device
                        while (true) {
                            _lightSwitchMenu->run(_lightSwitchProxy);
                            _display << "Current state" << endl;
                            _display << _controller->getUpdateMeasurement();
                            _display << "Do you want to continue controll this device? (y or n)" << endl
                                     <<  "1. Yes            2. No"<< endl;

                            QString option;
                            option = _input.readLine();
                            if (option  == "n"){
                                break;
                            }
                            else if (option  == "y") {
                                // do nothing
                            }
                            else {
                                _display << "Wrong option, please choose again" << endl;
                            }
                        }
                    }
                    else if (optionInput == "b") {
                        break;
                    }
                    else{
                        _display << "Wrong number, choose again" <<endl;
                    }
                }
            }
            else {
                _display << "There is no device to controll" << endl;
            }
        }
        else if (stringInput == "b") {
            break;
        }
        else {
            _display << "Invalid option, please choose other" <<endl;
        }
    }



}
