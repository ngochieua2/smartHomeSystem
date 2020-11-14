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

    QString getID();

    void turnOn() override;

    void turnOff() override;

    void schedule(QDateTime delay, int duration) override;

    void passRealSprinklerSystem(RealSprinklerSystem* realSprinklerSystem);

    void getDeviceInfo() override;

private:
    RealSprinklerSystem* _realSprinklerSystem{nullptr};
};

#endif // SPRINKLERSYSTEMPROXY_H
