#ifndef LIGHTSWITCHMENU_H
#define LIGHTSWITCHMENU_H

#include <QString>
#include <QStringList>
#include <QTextStream>
#include <lightswitchproxy.h>

class LightSwitchMenu : public QObject
{
    Q_OBJECT
public:
    explicit LightSwitchMenu(QTextStream &display, QTextStream &input, QObject *parent = nullptr);
    virtual ~LightSwitchMenu() = default;

    void run();

signals:

public slots:
    void showRegisterDevice(LightSwitchProxy* lightSwitchProxy);

private:
  QTextStream &_display;
  QTextStream &_input;
};

#endif // LIGHTSWITCHMENU_H
