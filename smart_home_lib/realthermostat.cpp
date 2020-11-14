#include "realthermostat.h"

RealThermostat::RealThermostat()
{
}

RealThermostat::RealThermostat(QString id, QUrl URL)
{
    _device_id = id;
    _devideType = "Thermostat";
    _deviceUrl = URL;
    _deviceInfo = new DeviceInfo(_device_id, _devideType, _deviceUrl);

    //set default value
    _setPoint = 18.00;
    _temperature = 25.00;
    _state = -1;

    // Save to _measurementRecord
    _measurement = new Measurement(_device_id, Measurement::measurementType::temperatureSetpoint, _setPoint);
    _measurementRecord.append(_measurement);
    _measurement = new Measurement(_device_id, Measurement::measurementType::temperature, _temperature);
    _measurementRecord.append(_measurement);
    _measurement = new Measurement(_device_id, Measurement::measurementType::thermostatState, _state);
    _measurementRecord.append(_measurement);

    //Update to have some default value
    Update();
    Update();
    Update();
}

RealThermostat::~RealThermostat()
{
    delete _deviceInfo;
    delete _controllerProxy;
    delete _measurement;
    for(int i = 0; i < _mesurementList.size(); i++){
        delete _mesurementList.at(i);
    }
    for(int i = 0; i < _measurementRecord.size(); i++){
        delete _measurementRecord.at(i);
    }
}

QList<Measurement *> RealThermostat::LastMeasurement()
{
    _mesurementList.clear();
    for (int i = _measurementRecord.size()-1; i >= 0; i--){
        if(_measurementRecord.at(i)->getType() == Measurement::measurementType::temperature){
            _measurement = new Measurement(_device_id,Measurement::measurementType::temperature,_measurementRecord.at(i)->value());
            _mesurementList.append(_measurement);
            break;
        }
    }
    return _mesurementList;
}

void RealThermostat::getLastMeasurement()
{
    _controllerProxy->report(LastMeasurement());
}

QList<Measurement *> RealThermostat::Last5Measurement()
{
    _mesurementList.clear();
    int count = 0;
    for (int i = _measurementRecord.size()-1; i >= 0; i--){
        if(_measurementRecord.at(i)->getType() == Measurement::measurementType::temperature){
            _measurement = new Measurement(_device_id,Measurement::measurementType::temperature,_measurementRecord.at(i)->value());
            _mesurementList.append(_measurement);
            count++;
        }
        if (count == 5){
            break;
        }
    }
    if(count < 5){
        for(int i = 0; i < 5-count; i++){
            _measurement = new Measurement(_device_id,Measurement::measurementType::temperature, "NULL");
            _mesurementList.append(_measurement);
        }
    }
    return _mesurementList;
}

void RealThermostat::getLast5Measurement()
{
    _controllerProxy->report(Last5Measurement());
}

QList<Measurement *> RealThermostat::setPointMeasurement()
{
    _mesurementList.clear();
    _measurement = new Measurement(_device_id,Measurement::measurementType::temperatureSetpoint, _setPoint);
    _mesurementList.append(_measurement);

    return _mesurementList;
}

void RealThermostat::getSetPoint()
{
    _controllerProxy->report(setPointMeasurement());
}

void RealThermostat::SetPoint(double setPoint)
{
    _setPoint = setPoint;
    _mesurementList.clear();
    _measurement = new Measurement(_device_id, Measurement::measurementType::temperatureSetpoint, _setPoint);
    _measurementRecord.append(_measurement);
    if(!isSameValue()){
        _measurement = new Measurement(_device_id,Measurement::measurementType::temperatureSetpoint, _setPoint);
        _mesurementList.append(_measurement);
        _controllerProxy->report(_mesurementList);
    }
}

void RealThermostat::warmer(double amount)
{
    _setPoint += amount;
    _mesurementList.clear();
    _measurement = new Measurement(_device_id, Measurement::measurementType::temperatureSetpoint, _setPoint);
    _measurementRecord.append(_measurement);
    if(!isSameValue()){
        _measurement = new Measurement(_device_id,Measurement::measurementType::temperatureSetpoint, _setPoint);
        _mesurementList.append(_measurement);
        _controllerProxy->report(_mesurementList);
    }
}

void RealThermostat::cooler(double amount)
{
    _setPoint -= amount;
    _mesurementList.clear();
    _measurement = new Measurement(_device_id, Measurement::measurementType::temperatureSetpoint, _setPoint);
    _measurementRecord.append(_measurement);
    if(!isSameValue()){
        _measurement = new Measurement(_device_id,Measurement::measurementType::temperatureSetpoint, _setPoint);
        _mesurementList.append(_measurement);
        _controllerProxy->report(_mesurementList);
    }
}

void RealThermostat::createControllerProxy()
{
    _controllerProxy = new ControllerProxy();
}

ControllerProxy *RealThermostat::getControllerProxy()
{
    return _controllerProxy;
}

void RealThermostat::getDeviceInfo()
{
    _controllerProxy->receiveDeviceInfo(_deviceInfo);
    _deviceInfo = new DeviceInfo(_device_id,_devideType,_deviceUrl);
    _deviceInfo->updateTime();
}

QList<Measurement *> RealThermostat::currentState()
{
    _mesurementList.clear();
    _measurement = new Measurement(_device_id, Measurement::measurementType::thermostatState, _state);
    _mesurementList.append(_measurement);
    return _mesurementList;
}

void RealThermostat::getMeasurement()
{
    _controllerProxy->report(currentState());
}

void RealThermostat::UpdateState()
{
    if ((_setPoint - 0.5) > _temperature) //Heating // Positive value
    {
        _state = 1;
    }
    else if (_setPoint + 0.5 < _temperature) //Cooling // Negative value
    {
        _state = -1;
    }
    else {
        _state = 0;
    }
    //record
    _measurement = new Measurement(_device_id, Measurement::measurementType::thermostatState, _state);
    _measurementRecord.append(_measurement);
    _mesurementList.clear();
    if(!isSameValue()){
        _measurement = new Measurement(_device_id,Measurement::measurementType::thermostatState, _state);
        _mesurementList.append(_measurement);
        _controllerProxy->report(_mesurementList);
    }
}

void RealThermostat::UpdateTemperature()
{
    srand (time(NULL));
    int random = rand() % 2 + 1;
    if(_state == 0){
        if(random == 1){
            _temperature += 0.5;
        }
        else {
            _temperature -= 0.5;
        }
    }
    else if (_state == 1) //Heat
    {
        double v = (_temperature - _setPoint)/10;
        if(v <= 0.5){
            _temperature += 0.5;
        }
        else {
             _temperature += v;
        }
    }
    else // cool
    {
        double v = (_setPoint-_temperature)/10;
        if(v <= 0.5){
            _temperature -= 0.5;
        }
        else {
            _temperature -= v;
        }
    }

    //Record
    _measurement = new Measurement(_device_id, Measurement::measurementType::temperature, _temperature);
    _measurementRecord.append(_measurement);
}

bool RealThermostat::isSameValue()
{
    for (int i = _measurementRecord.size() - 2; i >= 0; i--){
        if(_measurementRecord.last()->getType() == _measurementRecord.at(i)->getType()){
            if(_measurementRecord.last()->value() == _measurementRecord.at(i)->value()){
                return true;
            }
            else {
                return false;
            }
        }
    }
    return false;
}

void RealThermostat::Update()
{
    UpdateTemperature();
    UpdateState();
}
