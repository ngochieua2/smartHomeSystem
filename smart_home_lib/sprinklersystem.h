#ifndef SPRINKLERSYSTEM_H
#define SPRINKLERSYSTEM_H



class SprinklerSystem
{
public:
    SprinklerSystem();
    ~SprinklerSystem();


    void turnOn();

    void turnOff();

    void schedule(int delay, int duration);

    // currentState : measurement

    //waterUsage : measurement

protected:
    bool OnOffStatus{};
    int updatedFrequency{5};
    double waterConsumption{};

};

#endif // SPRINKLERSYSTEM_H
