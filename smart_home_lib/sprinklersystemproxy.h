#ifndef SPRINKLERSYSTEMPROXY_H
#define SPRINKLERSYSTEMPROXY_H
#include "sprinklersystem.h"
#include "realsprinklersysem.h"
#include "sprinklersystemfactory.h"

class SprinklerSystemProxy : public SprinklerSystem
{
public:
    SprinklerSystemProxy(RealSprinklerSysem* realSprinkler);
    ~SprinklerSystemProxy();
    void turnOn() override;
    void turnOff() override;
    void schedule(int delay, int duration) override;
private:
    RealSprinklerSysem* _realSprinkler{};
};

#endif // SPRINKLERSYSTEMPROXY_H
