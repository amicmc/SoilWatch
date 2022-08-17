/**SensorAnalog.h**/
#ifndef SENSOR_ANALOG_H
#define SENSOR_ANALOG_H
#include "Sensor.h"

// Atenuación de entrada, por defecto ADC_11db, rango ADC_0db, ADC_2_5db,
// ADC_6db, ADC_11db
#define B_ATTENUATION ADC_11db

// Divisor para el reloj.Rango de 1 a 255. Por defecto es 1.
#define B_CLOCKDIV 255
/**
 * @class SensorAnalog
 * @brief Representa una clase de sensor analógico derivada de Sensor
 *
 */

class SensorAnalog : public Sensor
{
protected:
    /**
     * @brief Procesa la lectura del sensor
     *
     */
    uint16_t readLevel();
    /**
     * @brief Inicialización de las lecturas analógicas
     *
     */
    virtual void init();

private:
    /**
     * @brief Obtiene la media y la desviación standard de un vector
     * @param vec Vector de valores a tratar
     * @param mean Media de los valores del vector
     * @param sd Desviación típica muestral de los valores del vector
     */
    void stat(vector<uint16_t> vec, float &mean, float &sd);
    /**
     * @brief Elimina los valores que se consideren outliers en un vector
     * @param vec Vector de valores a tratar
     * @param om Multiplicador de desviación estándar para definir outliers
     * @return Vector sin outliers si los tenía
     */
    vector<uint16_t> filterVector(vector<uint16_t> vec, uint8_t om);
    /**
     * @brief Devuelve la media de los valores del vector sin outliers
     * @param vec Vector de valores para obtener la media
     * @param om Multiplicador de desviación estándar para definir outliers
     * @return Media de los valores del vector sin outliers
     */
    uint16_t filteredMean(vector<uint16_t> vec, uint8_t om);

public:
    /**
     * @brief Constructor por defecto
     */
    SensorAnalog(){};
    /**
     * Destructor por defecto
     */
    ~SensorAnalog(){};
    /** getRaw
     * Devuelve la lectura del sensor den formato digital.
     *
     */
    virtual uint16_t getRaw();
};

#endif