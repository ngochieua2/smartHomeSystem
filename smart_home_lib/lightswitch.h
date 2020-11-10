#ifndef LIGHTSWITCH_H
#define LIGHTSWITCH_H

#include <smarthomedevices.h>
#include <QString>
#include <QUrl>

class LightSwitch : public SmartHomeDevices
{
public:
    LightSwitch();
    LightSwitch(QString id, QUrl Url);
    ~LightSwitch();

    void turnOn();

    void turnOff();

    void dim();

    void brighten();

    //currentState : 2 measurements();

protected:
    bool OnOffState{};
    int brightnessLevel{};

};

#endif // LIGHTSWITCH_H
