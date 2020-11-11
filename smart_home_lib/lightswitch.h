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
    /**
     * @brief turnOn will change the state to 'ON' if it is 'OFF', 
     * otherwise will do nothing
     */
    void turnOn();
    /**
     * @brief turnOff will change the state to 'OFF' if it is 'ON', 
     * otherwise will do nothing
     */
    void turnOff();
    /**
     * @brief dim will reduce the 'brightness level' by 20 points if currently greater than 20, 
     * otherwise will do nothing (cannot be reduced to zero brightness)
     */
    void dim();
    /**
     * @brief brighten will increase the 'brightness level' by 20 points if currently less than 100, 
     * otherwise will do nothing (cannot go above 100 percent)
     */
    void brighten();
    /**
     * @brief currentState will return two Measurements, one indicating the 'ON'/'OFF' status 
     * (boolean true/false, respectively), and one indicating the 'brightness level'
     */
    //currentState : 2 measurements();

protected:
    bool OnOffState{};
    int brightnessLevel{};

};

#endif // LIGHTSWITCH_H