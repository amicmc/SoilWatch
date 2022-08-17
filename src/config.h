/* config.h */
#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include "esp32-hal-log.h"


/* Sensores de humedad de suelo */
#define HSOIL1_PIN 36
#define HSOIL2_PIN 38
#define HSOIL3_PIN 39


/* Multiplicador para la eliminación de outliers en las lecturas de sensores */
#define SEN_OUT 1
/* Número de repeticiones en las lecturas de los sensores analógicos*/
#define SEN_REP 10
/********************************************************************/

#endif
