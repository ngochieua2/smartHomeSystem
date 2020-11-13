#ifndef CONTROLLERMENU_H
#define CONTROLLERMENU_H

#include <QString>
#include <QStringList>
#include <QTextStream>
#include <realcontroller.h>
#include <lightswitchmenu.h>


class ControllerMenu : public QObject
{
    Q_OBJECT
public:
    explicit ControllerMenu(QTextStream &display, QTextStream &input, QObject *parent = nullptr);
    virtual ~ControllerMenu() = default;

    void run(RealController* controller);

signals:
    void showRegisterDevice(LightSwitchProxy*);

private:
  QTextStream &_display;
  QTextStream &_input;

  RealController* _controller{nullptr};

  LightSwitchMenu* _lightSwitchMenu{nullptr};

};

#endif // CONTROLLERMENU_H
