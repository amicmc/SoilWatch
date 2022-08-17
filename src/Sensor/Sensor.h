/**Sensor.h**/
#ifndef SENSOR_H
#define SENSOR_H

#include "config.h"
using namespace std;
/**
 * @brief Clase de la que se especializan los sensores, ofreciendo una
 * interfaz homogénea
 */
class Sensor
{
protected:
    uint8_t _sensorPin;

public:
    /**
     * @brief Constructor por defecto
     */
    Sensor(){};
    /**
     * @brief Destructor por defecto
     */
    ~Sensor(){};
    /**
    * @brief Establece el pin de lectura del sensor
    * *
    @param sensorPin Pin de lectura del sensor
    */
    void setSensorPin(const uint8_t sensorPin) { _sensorPin = sensorPin; }
    uint8_t getSensorPin() { return _sensorPin; }
    
};

/**
 * @brief Excepcion lanzable en caso de error
 */
class SensorException : public exception
{
    std::string m_msg;

public:
    /**
    * @brief Constructor personalizado
    * *
    @param message Mensaje a emitir con la excepción
    */
    SensorException(const string &message)
        : m_msg(string("Sensor Exception: ") + message) {}
    virtual const char *what() const throw() { return m_msg.c_str(); }
};
#endif