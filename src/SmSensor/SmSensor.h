/** SmSensor.h
 * Clase especializada en la lectura de la humedad de suelo con un sensor
 *        de humedad de suelo PinoTech SoilWatch 10.
 * Datasheet: https://pino-tech.eu/wp-content/uploads/2017/08/SoilWatch10.pdf
 * Conexiones:
 *    Brown – VCC (+)
 *    Green – VDD (-)
 *    White – Output
 * Dos versiones:
 *    1V1: Salida de 0 - 1.1V
 *    3V0: Salida de 0 - 3.0V
 */

#ifndef SMSENSOR_H
#define SMSENSOR_H

#include "config.h"
#include "../Sensor/SensorAnalog.h"

/**
 * @brief Enumera los tres modos de lectura posible
 */
enum ReadMode
{
    accurate,
    theoretical,
    exact
};

/**
 * @brief Clase especializada en la lectura de la humedad de suelo con un sensor
 *        de humedad de suelo PinoTech SoilWatch 10.
 *
 */
class SmSensor : public SensorAnalog
{
private:
    ReadMode _rmode;
    float _slope = 0.0f;
    float _intercept = 0.0f;
    // Multiplicador para el modo teórico
    const double tmul = 3.046;
    // Pendiente de la recta ajustada en modo accurate
    const double pSlope = 2.671839;
    // Interceptación Y de la recta ajustada en modo accurate
    const double pIntercept = 463.210238;
    // Tensión máxima de salida: version 1.1V: true; 3V: false
    bool is1V1Output = false;
    // Tensión de referencia en la placa
    float refVoltage = 3.3;

public:

    /**
     * @brief constructor parametrizado de SmSensor en modo teorethical
     * 
     * @param smPin Pin asociado al pin de lectura del sensor
     * 
     */
    SmSensor(const uint8_t smPin);

    /**
     * @brief constructor parametrizado de SmSensor
     * 
     * @param smPin Pin asociado al pin de lectura del sensor
     * @param ReadMode Modo de lectura del sensor
     */
    SmSensor(const uint8_t smPin, const ReadMode mode);

    /**
    * @brief constructor parametrizado de SmSensor.
    * Su uso implica, de forma implícita, el uso de ReadMode exact.
    * 
    * @param smPin Pin asociado al pin de lectura del sensor
    * @param slope Pendiente de la recta de calibración
    * @param intercept Intersección de la recta
    */
    SmSensor(const uint8_t smPin, const float slope,
             const float intercept);

    /**
    * @brief Obtiene el valor de la humedad en puntos digitales.
    *
    * @return Valor de la humedad como entero positivo entre 0 y 4096
    */
    uint16_t getSmRaw();
    
    /**
    * @brief Obtiene el valor de la humedad como contenido volumétrico.
    *
    * @return Valor de la humedad como % de humedad en volumen entre 0 y 9999 (0.01 - 100 % )
    */
    uint16_t getVWC();


    /**
    * @brief Obtiene el valor de la humedad en %.
    *
    * @return Valor de la humedad como entero positivo entre 0 y 100
    */
    uint16_t getHumidity();
};
#endif