#include "sprinklersystemmenu.h"

#include <QTextStream>
#include <QUrl>
#include <QCoreApplication>


SprinklerSystemMenu::SprinklerSystemMenu(QTextStream &display, QTextStream &input, QObject *parent)
  : QObject{parent}, _display{display}, _input{input}
{
    timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()),this, SLOT(update()));
        timer->start(5000);
}


void SprinklerSystemMenu::run(SprinklerSystemProxy* sprinklerProxy)
{
    _sprinklerProxy = sprinklerProxy;
    while (true) {
        _display << "You are controlling"<< _sprinklerProxy->getID() <<"(sprinkler system)" << endl
             << "What would you like to do?" << endl
             << "1. Turn On" << endl
             << "2. Turn Off" << endl
             << "3. Schedule" << endl
             << "4. Current Sate" << endl
             << "5. Water Usage" << endl
             << "Type (b) to back" << endl;

        QString stringInput;
        stringInput = _input.readLine();
        if(stringInput == "1"){
            _sprinklerProxy->turnOn();
            break;
        }
        else if (stringInput == "2") {
            _sprinklerProxy->turnOff();
            break;
        }
        else if (stringInput == "3") {
            bool isNumber = false;
            int delay{};
           while (true) {
               _display << "Enter delay time" << endl;
               QString optionInput;
               optionInput = _input.readLine();
               optionInput.toInt(&isNumber);
               if (isNumber) {
                   delay = optionInput.toInt();                
                   break;
               } else {
                 _display << "Please enter a number" << endl;
               }
           }
           int duration{};
           while (true) {
               _display << "Enter duration: " << endl;
               QString optionInput;
               optionInput = _input.readLine();
               optionInput.toInt(&isNumber);
               if (isNumber) {
                   duration = optionInput.toInt();                
                   break;
               } else {
                 _display << "Please enter a number" << endl;
               }
           }
           
            _sprinklerProxy->schedule(delay, duration);    
        }
        else if (stringInput == "4") {
            _sprinklerProxy->getMeasurement();
            break;
        }
        else if (stringInput == "5") {
            _sprinklerProxy->getWaterUsage();
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

void SprinklerSystemMenu::update()
{
    if(_sprinklerProxy != nullptr){
        _sprinklerProxy->updateTime();
    }
}
