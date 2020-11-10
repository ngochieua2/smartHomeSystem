#include "mainmenu.h"

// If you want, change all of the QTextStream stuff to std:istream and std::ostream
// to stay with what you are familiar. Just keep in mind that it will not understand
// the various Qt objects that you might try to output.
#include <QTextStream>
#include <QUrl>
#include <QCoreApplication>

MainMenu::MainMenu(QTextStream &display, QTextStream &input, QObject *parent)
  : QObject{parent}, _display{display}, _input{input}
{
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


void MainMenu::run()
{
  _display << "Preparing to initialise you Smart Home System." << endl
           << "What type of device are do you want to configure?" << endl
           << "1. Smart Home Controller" << endl
           << "2. Light Switch" << endl
           << "3. Thermostat" << endl
           << "4. Sprinkler System" << endl
           << "Type (q) to quit" << endl;

  for (QString selection{_input.read(1)}; selection.toLower() != "q"; selection = _input.read(1)) {
    if (selection == "1" ){
        _display << "Smart Home Controller event" << endl;

        if (_controller == nullptr){
            configMenu("Smart Home Controller");
            _controller = new SmartHomeController(_id,_Url);
            _display << "Success" << endl;
        }
        controllerMenuInterface();
    }
    else if (selection == "2"){
        _display << "Light Switch event" << endl;
    }
    else if (selection == "3"){
        _display << "Thermostat event" << endl;
    }
    else if (selection == "4") {
        _display << "Sprinkler System event" << endl;
    }
    else if (selection != '\n') {
      _display << "Please choose correct option"<< endl;
      _input.readLine(); // skip the rest of the line
    }
  }

  // Need to exit the event loop to end the application
  QCoreApplication::instance()->quit();
}

void MainMenu::configMenu(QString type)
{
    _display << "What would you like to call this *"+ type+"*";
    _input >> _id;
    _display << "What is the URL for " + _id + "(" + type + ")" << endl;
    _input >> _Url;
    _display << "Initialising " + type + " *" + _id + "* on *"+_Url+"* ..." << endl;

}

void MainMenu::controllerMenuInterface()
{
    _display << "Name:"
             << "What would you like to do" << endl;


}

void MainMenu::lightSwitchMenuInterface()
{
    _display << "You are controlling {name}(light switch)" << endl
             << "What would you like to do?" << endl
             << "1. Turn On" << endl
             << "2. Turn Off" << endl
             << "3. Reduce the brightness level (dim)" << endl
             << "4. Increase the brightness level" << endl
             << "5. Check current status" << endl
             << "Type (b) to back" << endl;

    for (QString dvSelection{_input.read(1)}; dvSelection.toLower() != "b"; dvSelection = _input.read(1)) {
      if (dvSelection == "1" ){

      }
      else if (dvSelection == "2"){

      }
      else if (dvSelection == "3"){

      }
      else if (dvSelection == "4") {

      }
      else if (dvSelection == "5") {

      }
      else if (dvSelection != '\n') {
        _display << "Please choose correct option"<< endl;
        _input.readLine(); // skip the rest of the line
      }
    }
}

void MainMenu::spinklerMenuInterface()
{
    _display << "You are controlling {name}(spinkler)" << endl
             << "What would you like to do?" << endl
             << "1. Turn On" << endl
             << "2. Turn Off" << endl
             << "3. Set schedule" << endl
             << "4. Check current status" << endl
             << "5. Check water usage" << endl
             << "Type (b) to back" << endl;

    for (QString dvSelection{_input.read(1)}; dvSelection.toLower() != "b"; dvSelection = _input.read(1)) {
      if (dvSelection == "1" ){

      }
      else if (dvSelection == "2"){

      }
      else if (dvSelection == "3"){

      }
      else if (dvSelection == "4") {

      }
      else if (dvSelection == "5") {

      }
      else if (dvSelection != '\n') {
        _display << "Please choose correct option"<< endl;
        _input.readLine(); // skip the rest of the line
      }
    }
}

void MainMenu::thermostatMenuInterface()
{
    _display << "You are controlling {name}(therostat)" << endl
             << "What would you like to do?" << endl
             << "1. Check the most recent temperature" << endl
             << "2. Check the 5 most recent temperature" << endl
             << "3. Set temperature point" << endl
             << "4. Check current status" << endl
             << "5. Warmer" << endl
             << "6. Cooler" << endl
             << "Type (b) to back" << endl;

    for (QString dvSelection{_input.read(1)}; dvSelection.toLower() != "b"; dvSelection = _input.read(1)) {
      if (dvSelection == "1" ){

      }
      else if (dvSelection == "2"){

      }
      else if (dvSelection == "3"){

      }
      else if (dvSelection == "4") {

      }
      else if (dvSelection == "5") {

      }
      else if (dvSelection == "6") {

      }
      else if (dvSelection != '\n') {
        _display << "Please choose correct option"<< endl;
        _input.readLine(); // skip the rest of the line
      }
    }
}

