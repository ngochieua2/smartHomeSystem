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
     * @brief getLastMeasurement is used to send last measurement to controller
     */
    void getLastMeasurement() override;
    /*!
     * @brief Last5Measurement returns the 5 most recent temperature Measurements from the Thermostat
     * @return QList
     */
    QList <Measurement*> Last5Measurement();
    /*!
     * @brief getLast5Measurement is used to send last 5 measurement to controller
     */
    void getLast5Measurement() override;
    /*!
     * @brief setPointMeasurement return setPoint measurement
     * @return Qlist
     */
    QList <Measurement*> setPointMeasurement();
    /*!
     * @brief getSetPoint is used to send setPoint measurement to controller
     */
    void getSetPoint() override;
    /*!
     * @brief SetPoint returns a Measurement representing the currently set desired temperature
     * if state change, it will report back to controller
     * @param setPoint
     */
    void SetPoint(double setPoint) override;
    /*!
     * @brief warmer increases the setpoint to a higher temperature by 'amount', does nothing if the amount is <= 0
     * if state change, it will report back to controller
     * @param amount
     */
    void warmer(double amount) override;
    /*!
     * @brief cooler decreases the setpoint to a cooler temperature by 'amount', does nothing if the amount is <= 0
     * if state change, it will report back to controller
     * @param amount
     */
    void cooler(double amount) override;
    /*!
     * @brief createControllerProxy create controller proxy in the thermostat
     */
    void createControllerProxy();

    /*!
     * @brief getControllerProxy return controller proxy in the thermostat
     * @return ControllerProxy
     */
    ControllerProxy* getControllerProxy();
    /*!
     * @brief getDeviceInfo is usd to send its info to controller
     */
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
    /*!
     * @brief getMeasurement send device measurement to controller
     * it can be empty if nothing change
     *
     */
    void getMeasurement() override;
    /*!
     * @brief UpdateState combine with Qtimer and after 3 second, it will
     * be create new state
     */
    void UpdateState();
    /*!
     * @brief UpdateTemperature combine with Qtimer and after 3 second, it will
     * be create new temperature depend on current state
     */
    void UpdateTemperature();
    /*!
     * @brief isSameValue is used to check is that current have been changed or not
     * after command
     * @return bool
     */
    bool isSameValue();
    /*!
     * @brief Update is order of UpdateTemperature() and UpdateState()
     */
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
