#include "controllermenu.h"
#include <QTextStream>
#include <QUrl>
#include <QCoreApplication>

ControllerMenu::ControllerMenu(QTextStream &display, QTextStream &input, QObject *parent)
  : QObject{parent}, _display{display}, _input{input}
{
    //_lightSwitchMenu = new  LightSwitchMenu(display, input);
}

void ControllerMenu::run(RealController* controller){
    _controller = controller;
    while (true) {
        _display << "Welcome to controller menu" << endl
                 << "Name controller: " << _controller->getID() << endl
                 << "What would you like to do" << endl
                 << "1.Show all register devices" << endl
                 << "2.Unregister device" << endl
                 << "3.Controll device" << endl
                 << "4." << endl
                 << "Type (b) to back" << endl;

        QString stringInput;
        stringInput = _input.readLine();
        if(stringInput == "1"){
            // get info
            for(int i = 0; i < _controller->getLightSwitchProxyList().size(); ++i){
                emit showRegisterDevice(_controller->getLightSwitchProxyList().at(i));
                //_lightSwitchMenu->showRegisterDevice(_controller->getLightSwitchProxyList().at(i));
            }
            //Show data
            _display << endl;
            _display << _controller->registerDevice();
            _display << endl;

        }
        else if (stringInput == "2") {
            _display << "2 event" <<endl;

        }
        else if (stringInput == "3") {
            _display << "3 event" <<endl;
        }
        else if (stringInput == "4") {
            _display << "4 event" <<endl;
        }
        else if (stringInput == "b") {
            break;
        }
        else {
            _display << "Invalid option, please choose other" <<endl;
        }
    }



}
