#include "thermostatfactory.h"

SmartHomeDevice *ThermostatFactory::CreateDevice(QString id, QUrl url)
{
    return new RealThermostat(id, url);
}
