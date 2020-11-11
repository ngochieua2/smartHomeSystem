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
private:
    RealSprinklerSysem* _realSprinkler{};
    SprinklerSystemFactory* _factory{};
};

#endif // SPRINKLERSYSTEMPROXY_H
