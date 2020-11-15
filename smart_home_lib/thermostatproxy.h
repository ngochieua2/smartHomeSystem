#ifndef THERMOSTATPROXY_H
#define THERMOSTATPROXY_H

#include <thermostat.h>
#include <realthermostat.h>

class RealThermostat;

class ThermostatProxy : public Thermostat
{
public:
    ThermostatProxy();
    ThermostatProxy(QString id, QUrl Url);
    virtual ~ThermostatProxy();
    /*!
     * @brief getID return the device id
     * @return id
     */
    QString getID();
    /*!
     * @brief getLastMeasurement calls real device to get the most recent temperature Measurement from the Thermostat
     */
    void getLastMeasurement() override;
    /*!
     * @brief getLast5Measurement calls real device to get the 5 most recent temperature Measurements from the Thermostat
     */
    void getLast5Measurement() override;
    
    /*!
     * @brief getSetPoint calls real device to get a Measurement representing the currently set desired temperature
     */
    void getSetPoint() override;
    /*!
     * @brief SetPoint calls real device to returns a Measurement representing the currently set desired temperature
     * @param setPoint
     */
    void SetPoint(double setPoint) override;
    /*!
     * @brief warmercalls real device to increases the setpoint to a higher temperature by 'amount', does nothing if the amount is <= 0
     * @param amount
     */
    void warmer(double amount) override;
    /*!
     * @brief cooler calls real device to decreases the setpoint to a cooler temperature by 'amount', does nothing if the amount is <= 0
     * @param amount
     */
    void cooler(double amount) override;
    /*!
     * @brief passRealThermostat pass the real thermostat to its proxy
     * @param realThermostat
     */
    void passRealThermostat(RealThermostat* realThermostat);
    /*!
     * @brief getDeviceInfo calls real device to gets device information
     */
    void getDeviceInfo() override;
    /*!
     * @brief getMeasurement calls real device to gets the measurement of the device
     */
    void getMeasurement() override;
    /*!
     * @brief Update calls real device to update its new measurement
     */
    void Update() override;

private:
    RealThermostat* _realThermostat{nullptr};

};

#endif // THERMOSTATPROXY_H
