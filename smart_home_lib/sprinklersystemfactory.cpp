#include "sprinklersystemfactory.h"

SmartHomeDevice *SprinklerSystemFactory::CreateDevice(QString id, QUrl url)
{
    return new RealSprinklerSystem(id, url);
}
