/**Actuator.h**/
#ifndef ACTUATOR_H
#define ACTUATOR_H

#include "Arduino.h"
using namespace std;

/**
 * @class Actuator
 * @brief Representa una clase de actuador digital
 *
 */
class Actuator
{
private :
    bool _hasWatcher = false;
    virtual void _init(int mode);
    virtual void IRAM_ATTR _onAlert();

protected:
    uint8_t _sensorPin;
    uint8_t _watcherPin;

public:
    /**
     * @class Constructor por defecto
     */
    Actuator(){};

    /**
     * @class Constructor parametrizado
     * 
     * @param sensorPin Pin de salida del actuador
     * @param watcherPin Pin del supervisor del actuador
     */
    Actuator(uint8_t sensorPin, uint8_t watcherPin, int mode)
    {
        setSensorPin(sensorPin);
        setWatcherPin(watcherPin, mode);
    }

    /**
     * @class Constructor parametrizado
     * 
     * @param sensorPin Pin de salida del actuador
     */
    Actuator(uint8_t sensorPin)
    {
        setSensorPin(sensorPin);
        _hasWatcher = false;
        _watcherPin = NULL;
    }

    void setSensorPin(uint8_t sensorPin)
    {
        _sensorPin = sensorPin;
        pinMode(_sensorPin, OUTPUT);
    }

    void setWatcherPin(uint8_t watcherPin, int mode)
    {
        _watcherPin = watcherPin;
        pinMode(_watcherPin, INPUT);
        _hasWatcher = true;
        _init(mode);
    }

    bool isSupervised(){
        return _hasWatcher;
    }

    

    /**
     * Destructor por defecto
     */
    ~Actuator(){};

};

#endif