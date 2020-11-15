#ifndef REALTHERMOSTAT_H
#define REALTHERMOSTAT_H

//For random
#include <stdlib.h>
#include <time.h>

#include <thermostat.h>
#include <controllerproxy.h>

class ControllerProxy;

class RealThermostat : public Thermostat
{
public:
    RealThermostat();
    RealThermostat(QString id, QUrl URL);
    virtual ~RealThermostat();
    /*!
     * @brief LastMeasurement returns the most recent temperature Measurement from the Thermostat
     * @return QList
     */
    QList <Measurement*> LastMeasurement();
    /*!
     * @brief getLastMeasurement
     */
    void getLastMeasurement() override;
    /*!
     * @brief Last5Measurement returns the 5 most recent temperature Measurements from the Thermostat
     * @return QList
     */
    QList <Measurement*> Last5Measurement();
    /*!
     * @brief getLast5Measurement
     */
    void getLast5Measurement() override;
    /*!
     * @brief setPointMeasurement
     * @return 
     */
    QList <Measurement*> setPointMeasurement();
    /*!
     * @brief getSetPoint
     */
    void getSetPoint() override;
    /*!
     * @brief SetPoint returns a Measurement representing the currently set desired temperature
     * @param setPoint
     */
    void SetPoint(double setPoint) override;
    /*!
     * @brief warmer increases the setpoint to a higher temperature by 'amount', does nothing if the amount is <= 0
     * @param amount
     */
    void warmer(double amount) override;
    /*!
     * @brief cooler decreases the setpoint to a cooler temperature by 'amount', does nothing if the amount is <= 0
     * @param amount
     */
    void cooler(double amount) override;


    void createControllerProxy();

    ControllerProxy* getControllerProxy();

    void getDeviceInfo() override;
    /*!
     * @brief currentState returns whether the temperature is currently 'STABLE' (within a certain 
     * range of the setpoint), 'HEATING' (the temperature is increasing to reach the setpoint), or 
     * 'COOLING' (the temperature is decreasing to reach the setpoint): 'STABLE' is represented by 
     * zero, 'HEATING' is represented by a positive value, 'COOLING' is represented by a negative 
     * value
     * @return QList
     */
    QList <Measurement*> currentState();

    void getMeasurement() override;

    void UpdateState();

    void UpdateTemperature();

    bool isSameValue();

    void Update() override;


private:
    ControllerProxy* _controllerProxy{};
    DeviceInfo* _deviceInfo{nullptr};

    double _setPoint{};
    double _temperature{};
    int _state{};

    Measurement* _measurement{nullptr};
    QList <Measurement*> _mesurementList{};

    QList <Measurement*> _measurementRecord{};
};

#endif // REALTHERMOSTAT_H
