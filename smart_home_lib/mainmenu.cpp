#include "mainmenu.h"

#include <QTextStream>
#include <QUrl>
#include <QCoreApplication>

MainMenu::MainMenu(QTextStream &display, QTextStream &input, QObject *parent)
  : QObject{parent}, _display{display}, _input{input}
{
    _controllerMenu = new ControllerMenu(display, input);
    _lightSwitchMenu = new  LightSwitchMenu(display, input);

    QObject::connect(_controllerMenu,&ControllerMenu::showRegisterDevice,
                     _lightSwitchMenu,&LightSwitchMenu::showRegisterDevice);
}

void MainMenu::displayWelcome(const QString &title, const QString &group, const QStringList &members) const
{
  QString welcomeText{"Welcome to " + title};
  QString groupText{"Developed by " + group + ":"};

  _display << welcomeText << endl
           << groupText << endl;

  for (auto name: members) {
    _display << "- " << name << endl;
  }

  _display << "COMP 3023 Software Development with C++" << endl << endl;

}

void MainMenu::configMenu(QString type)
{
    QString id;
    QUrl Url;
    while (true) {
        _display << "What would you like to call this *"+ type+"*" << endl;
        id = _input.readLine();
        if(id.isEmpty()){
            _display << "Name cannot be empty";
        }
        else {
            break;
        }
    }
    while (true) {
        _display << "What is the URL for " + id + "(" + type + ")" << endl;
        Url = _input.readLine();
        if(Url.isEmpty()){
            _display << "Url cannot be empty";
        }
        else {
            break;
        }
    }
    _display << "Initialising " + type + " *" + id + "* on *"+Url.toString()+"* ..." << endl;

    //if type is controller, create a new one
    if (type == "Smart Home Controller"){
        _controller = new RealController(id,Url);
    }
    // if type is device, save it into QPair temporary variable
    // it will be register when accessing controller
    else if (type == "Light Switch"){
        tempLightSwitch.append(qMakePair(QString(id),QUrl(Url)));
    }
}


void MainMenu::run()
{
    while (true) {
        _display << "Preparing to initialise you Smart Home System." << endl
                 << "What type of device are do you want to configure?" << endl
                 << "1. Smart Home Controller" << endl
                 << "2. Light Switch" << endl
                 << "3. Thermostat" << endl
                 << "4. Sprinkler System" << endl
                 << "Type (q) to quit" << endl;
        QString stringInput;
        stringInput = _input.readLine();
        if(stringInput == "1"){

            if(_controller == nullptr){
                configMenu("Smart Home Controller");
                _display << "Success\n" << endl;
            }

            //Register device and set up
            if (!tempLightSwitch.isEmpty()){
                for(int i = 0; i < tempLightSwitch.size(); ++i){
                    _controller->registerDevice(tempLightSwitch.at(i).first, "lightSwitch", tempLightSwitch.at(i).second);
                    //Factory
                    _device = new RealLightSwitch(tempLightSwitch.at(i).first,tempLightSwitch.at(i).second);

                    _realLightSwitch = static_cast<RealLightSwitch*>(_device);
                    _controller->getLightSwitchProxy()->passRealLightSwitch(_realLightSwitch);
                    _realLightSwitch->createControllerProxy();
                    _realLightSwitch->getControllerProxy()->passController(_controller);
                }
                tempLightSwitch.clear();

            }
            _controllerMenu->run(_controller);

        }
        else if (stringInput == "2") {
            _display << "Light Switch event" <<endl;
            configMenu("Light Switch");
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

    // Need to exit the event loop to end the application
    QCoreApplication::instance()->quit();
}



