/**SensorAnalog.cpp**/

#include "SensorAnalog.h"

void SensorAnalog::init()
{
    analogReadResolution(12);
    analogSetClockDiv(B_CLOCKDIV);
    analogSetPinAttenuation(_sensorPin, B_ATTENUATION);
    adcAttachPin(_sensorPin);
}

uint16_t SensorAnalog::readLevel()
{
    vector<uint16_t> lecturas;
    log_d("SensorAnalog::readLevel(), pin: %d", _sensorPin);
    for (int i = 0; i < SEN_REP; i++)
    {
        uint16_t lectura = analogRead(_sensorPin);
        log_d("Lectura bruta: %d", lectura);
        // Evito divisiones por 0
        if (lectura == 0)
            lectura = 1;
        lecturas.push_back(lectura);
        delay(100);
    }
    return filteredMean(lecturas, SEN_OUT);
}

void SensorAnalog::stat(vector<uint16_t> vec, float &mean, float &sd)
{
    log_d("SensorAnalog::stat()");
    uint16_t accum = 0;
    uint16_t vecLen = vec.size();
    for (int i = 0; i < vecLen; i++)
    {
        accum += vec.at(i);
    }
    mean = (float)accum / (float)vecLen;
    float varAccum = 0.0;
    for (int i = 0; i < vecLen; i++)
    {
        varAccum = varAccum + pow((vec.at(i) - mean), 2);
    }

    if (varAccum == 0)
        varAccum = 1;
    sd = sqrt(varAccum / (float)(vecLen - 1));
}

vector<uint16_t> SensorAnalog::filterVector(vector<uint16_t> vec,
                                            uint8_t outmul)
{
    log_d("SensorAnalog::filterVector()");
    uint16_t vecLen = vec.size();
    outmul = outmul < 1 ? 1 : outmul;
    float mean = 0.0;
    float sd = 0.0;
    stat(vec, mean, sd);
    vector<uint16_t> filterec;
    for (int i = 0; i < vecLen; i++)
    {
        uint16_t current = vec.at(i);
        if (current > mean - outmul * sd && current < mean + outmul * sd)
            filterec.push_back(current);
    }
    return filterec;
}

uint16_t SensorAnalog::filteredMean(vector<uint16_t> vec, uint8_t outmul)
{
    log_d("SensorAnalog::filteredMean()");
    outmul = outmul < 1 ? 1 : outmul;
    float mean = 0.0;
    float sd = 0.0;
    stat(filterVector(vec, outmul), mean, sd);
    return mean;
}

uint16_t SensorAnalog::getRaw()
{
    log_d("SensorAnalog::getRaw()");
    return readLevel();
}
