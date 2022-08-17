#include "SmSensor.h"



SmSensor::SmSensor(const uint8_t smPin)
{
    setSensorPin(smPin);
    _rmode = theoretical;
    init();
}

SmSensor::SmSensor(const uint8_t smPin, const ReadMode mode)
{
    setSensorPin(smPin);
    _rmode = mode;
    init();
}

SmSensor::SmSensor(const uint8_t smPin, const float slope, const float intercept)
{
    setSensorPin(smPin);
    init();
    _slope = slope;
    _intercept = intercept;
    _rmode = exact;
}

uint16_t SmSensor::getHumidity()
{
    uint16_t raw = getRaw();
    switch (_rmode)
    {
    case accurate:
        return round(raw * pSlope + pIntercept);
        break;
    case exact:
        if (_slope != 0 && _intercept != 0)
            return (raw * _slope + _intercept);
        else{
            const char message[82] = "No es posible usar el modo exacto sin "
                                  "proporcionar pendiente y ordenada al origen";
            log_e("%s",message);
            throw SensorException(message);
        }
        break;
    default:
        return map(raw, 0, 4095, 0, (int)(refVoltage*100));
        break;
    }
}

uint16_t SmSensor::getSmRaw()
{
    return getRaw();
}


uint16_t SmSensor::getVWC()
{
    return getRaw();
}