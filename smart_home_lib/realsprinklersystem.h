#ifndef REALSPRINKLERSYSTEM_H
#define REALSPRINKLERSYSTEM_H
#include "controllerproxy.h"
#include "sprinklersystem.h"

class ControllerProxy;

class RealSprinklerSystem : public SprinklerSystem
{
public:
    RealSprinklerSystem();
    RealSprinklerSystem(QString id, QUrl url);
    virtual ~RealSprinklerSystem();
    /*!
     * @brief turnOn will change the sprinkler system state to 'ON' until it 
     * is turned off or a timer is scheduled; this will cancel any scheduled time 
     */
    void turnOn() override;
    /*!
     * @brief turnOff will change the state of the sprinkler system state to 'OFF' 
     * until it is turned on or a timer is scheduled; this will cancel any scheduled time
     */
    void turnOff() override;
    /*!
     * @brief schedule schedule the sprinkler to turn on after the 'delay' for the specified 
     * 'duration'; scheduling the start will turn the sprinkler system off if it is on, and 
     * set the state to 'SCHEDULED'
     * @param delay
     * @param duration
     */
    void schedule(int delay, int duration) override;
    /*!
     * @brief createControllerProxy create controller proxy of the sprinkler system
     */
    void createControllerProxy();
    /*!
     * @brief getControllerProxy return controller proxy of the sprinkler system
     * @return ControllerProxy
     */
    ControllerProxy* getControllerProxy();

    void getDeviceInfo() override;

    void getMeasurement() override;
    
    void getWaterUsage() override;
    /*!
     * @brief UpdateWaterUsage
     */
    void UpdateWaterUsage();
    /*!
     * @brief currentState returns whether the Sprinkler System is running 'ON', 
     * 'OFF', or 'SCHEDULED' (i.e., off but has a start-time scheduled) as a 
     * Measurement and, if it is in the 'SCHEDULED' state, it will also return 
     * the time at which it will turn on as a second Measurement, and the duration 
     * it will be on for as a third Measurement.
     * @return QList
     */
    QList <Measurement*> currentState();
    /*!
     * @brief waterUsage return two Measurements, the first will be the current usage 
     * tracking water consumption for the current run of the sprinkler system, the 
     * second is the total or 'lifetime' water usage tracking the litres of water 
     * consumed over the lifetime of the sprinkler system across all its runs
     * @return QList
     */
    QList<Measurement*> waterUsage();
    /*!
     * @brief getState return the state of sprinkler
     * @return QString
     */
    QString getState();

    QTimer* getTimer();
    
    bool isValueChanged();
    
    QList<Measurement*> latestWaterConsumption();
    
    QList<Measurement*> totalWaterConsumption();
    
    void updateTime() override;
        
private:
    QString _state{};
    
    QDateTime _start{};
    QDateTime _end{};
    
    int _duration{};
    int _delay{};
    int _updateFrequency{};
    
    double _waterConsumptionpPerInt{};
    double _currentWaterConsumption{};
    double _totalWaterConsumption{};   
    
    QTimer* _timer{};
    ControllerProxy* _controllerProxy{};

    DeviceInfo* _deviceInfo{nullptr};

    Measurement* _measurement{nullptr};
    QList <Measurement*> _measurementList{};
    QList <Measurement*> _measurementRecord{};

};

#endif // REALSPRINKLERSYSTEM_H
