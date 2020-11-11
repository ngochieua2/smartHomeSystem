#include "sprinklersystem.h"

SprinklerSystem::SprinklerSystem()
{
}

SprinklerSystem::~SprinklerSystem()
{
}


void SprinklerSystem::turnOn()
{
    OnOffStatus = true;
}

void SprinklerSystem::turnOff()
{
    OnOffStatus = false;
}

void SprinklerSystem::schedule(int delay, int duration)
{

}
