#include "sprinklersystemfactory.h"

SmartHomeDevices *SprinklerSystemFactory::CreateDevice(QString id, QUrl url)
{
    return new RealSprinklerSysem(id, url);
}
