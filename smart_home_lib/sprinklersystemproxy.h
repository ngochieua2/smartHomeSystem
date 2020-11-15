#ifndef SPRINKLERSYSTEMPROXY_H
#define SPRINKLERSYSTEMPROXY_H
#include "sprinklersystem.h"
#include "realsprinklersystem.h"

class RealSprinklerSystem;

class SprinklerSystemProxy : public SprinklerSystem
{
public:
    SprinklerSystemProxy();
    SprinklerSystemProxy(QString id, QUrl url);
    virtual ~SprinklerSystemProxy();
    /*!
     * @brief getID returns device proxy
     * @return id
     */
    QString getID();
    /*!
     * @brief turnOn calls real device to turn on
     */
    void turnOn() override;
    /*!
     * @brief turnOff calls real device to turn off
     */
    void turnOff() override;
    /*!
     * @brief schedule calls real device to implement schedule feature
     * @param delay
     * @param duration
     */
    void schedule(int delay, int duration) override;
    /*!
     * @brief passRealSprinklerSystem pass the real device to the its proxy
     * @param realSprinklerSystem
     */
    void passRealSprinklerSystem(RealSprinklerSystem* realSprinklerSystem);
    /*!
     * @brief getDeviceInfo calls real device to retrieve its information
     */
    void getDeviceInfo() override;
    /*!
     * @brief getMeasurement calls real device to retrieve its measurement
     */
    void getMeasurement() override;
    /*!
     * @brief getWaterUsage calls real device to retrieve its water usage
     */
    void getWaterUsage() override;
    /*!
     * @brief updateTime calls real device to update its starting time
     */
    void updateTime() override;

private:
    RealSprinklerSystem* _realSprinklerSystem{nullptr};
};

#endif // SPRINKLERSYSTEMPROXY_H
