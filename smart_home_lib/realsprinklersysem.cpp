#include "realsprinklersysem.h"

RealSprinklerSysem::RealSprinklerSysem(QString id, QUrl url)
{
    
}

void RealSprinklerSysem::turnOn()
{
    OnOffStatus = true;
}

void RealSprinklerSysem::turnOff()
{
    OnOffStatus = false;
}

void RealSprinklerSysem::schedule(int delay, int duration)
{
    
}


