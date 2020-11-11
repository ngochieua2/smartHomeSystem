#ifndef REALSPRINKLERSYSEM_H
#define REALSPRINKLERSYSEM_H
#include "sprinklersystem.h"

class RealSprinklerSysem : public SprinklerSystem
{
public:
    RealSprinklerSysem(QString id, QUrl url);
    virtual ~RealSprinklerSysem();
    void turnOn() override;
    void turnOff() override;
    void schedule(int delay, int duration) override;
};

#endif // REALSPRINKLERSYSEM_H
