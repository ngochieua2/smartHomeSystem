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
    /*!
     * @brief run runs the menu of thermostat
     * @param thermostatProxy
     */
    void run(ThermostatProxy* thermostatProxy);

    QTimer *timer;


public slots:

    void update();

private:
  QTextStream &_display;
  QTextStream &_input;

  ThermostatProxy* _thermostatProxy{nullptr};

};

#endif // THERMOSTATMENU_H
