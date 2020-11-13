#ifndef THERMOSTATMENU_H
#define THERMOSTATMENU_H

#include <QString>
#include <QStringList>
#include <QTextStream>
#include <thermostatproxy.h>

class ThermostatMenu : public QObject
{
    Q_OBJECT
public:
    explicit ThermostatMenu(QTextStream &display, QTextStream &input, QObject *parent = nullptr);
    virtual ~ThermostatMenu() = default;

    void run();

signals:

public slots:
    void showRegisterDevice(ThermostatProxy* thermostatProxy);

private:
  QTextStream &_display;
  QTextStream &_input;

};

#endif // THERMOSTATMENU_H
