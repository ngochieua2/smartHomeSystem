#include "sprinklersystemproxy.h"

SprinklerSystemProxy::SprinklerSystemProxy(RealSprinklerSysem *realSprinkler)
{
    _realSprinkler = realSprinkler;
}
SprinklerSystemProxy::~SprinklerSystemProxy(){
    delete _realSprinkler;
    delete  _factory;
}
