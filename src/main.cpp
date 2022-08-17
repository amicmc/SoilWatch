#include <Arduino.h>
#include <heltec.h>
#include "cicytex_logo.h"
#include "MonospacedPlain.h"
#include "SmSensor/SmSensor.h"
#include "WiFi.h"

#define logoX 0
#define logoY 0


bool is1V1Output = false; // version 1.1V: true; 3V: false
float refVoltage = 3.3;   // voltaje de referencia en la placa
int rawValue, mappedValue;
float voltage, vwcValue;
int minADC = 0;
int maxADC = 3568;

void logo()
{
  Heltec.display->clear();
  Heltec.display->drawXbm(logoX, logoY, CICYTEX_width, CICYTEX_height, (const unsigned char *)CICYTEX_bits);
  Heltec.display->display();
  // Opciones ArialMT_Plain_10 ArialMT_Plain_16 ArialMT_Plain_24
  // Monospaced_plain_9 Monospaced_plain_10 Monospaced_plain_12 Monospaced_plain_16
  Heltec.display->setFont(Monospaced_plain_9);
}

void dispHumidity(SmSensor sms, uint8_t displayY)
{
  // S S 128x64
  uint8_t cursorX = 0;
  uint16_t rawValue = sms.getHumidity();
  voltage = rawValue * refVoltage / maxADC;
  voltage = voltage > 3.3 ? 3.3 : voltage;
  voltage = voltage < 0.0 ? 0 : voltage;
  vwcValue = (2.8432f * voltage * voltage * voltage) - (9.1993f * voltage * voltage) + (20.2553f * voltage) - 4.1882f;
  vwcValue = vwcValue > 100.0 ? 100.0 : vwcValue;
  vwcValue = vwcValue < 0.0 ? 0 : vwcValue;
  mappedValue = map(rawValue, minADC, maxADC, 0, 100);
  mappedValue = mappedValue > 100.0 ? 100.0 : mappedValue;
  mappedValue = mappedValue < 0.0 ? 0 : mappedValue;

  char cAP[25];
  snprintf(cAP, 25, "%2d %4d %.3f  %4.1f %3d", sms.getSensorPin(), rawValue, voltage, vwcValue, mappedValue);

  String sScreen = String(cAP);

  log_i("mapped: %d\n", mappedValue);
  log_i("vwcValue: %1f\n", vwcValue);
  log_i("voltage: %3f\n", voltage);
  log_i("raw: %d\n", rawValue);
  log_i("pin: %d\n", sms.getSensorPin());
  log_i("=======================\n");

  Heltec.display->drawString(cursorX, displayY, sScreen);
  Heltec.display->display();

  delay(500);
}

void setup()
{
  Heltec.begin(true /*DisplayEnable Enable*/, true /*LoRa Enable*/, false /*Serial Enable*/, true /*LoRa use PABOOST*/, 868E6 /*LoRa RF working band*/);

  log_i("===========ooooo=======\n");
  SmSensor sms1(HSOIL1_PIN);
  SmSensor sms2(HSOIL2_PIN);
  SmSensor sms3(HSOIL3_PIN);

  uint64_t chipid = ESP.getEfuseMac();                                      
  log_i("ESP32ChipID=%04X%08X\n", (uint16_t)(chipid >> 32), (uint32_t)chipid); 
  delay(100);

  delay(100);

  Heltec.display->clear();
  logo();
  delay(1000);
  Heltec.display->display();
  Heltec.display->clear();
  Heltec.display->drawString(0, 0, "id  Raw  Volt VCont Map");
  Heltec.display->drawString(0, 1, "_______________________");
  /*
    for (size_t i = 0; i < 130; i++)
    {
      Heltec.display -> drawString(i*10, 10, "|");

    }
  */
  Heltec.display->display();
  dispHumidity(sms1, 12);
  delay(300);
  dispHumidity(sms2, 22);
  delay(300);
  dispHumidity(sms3, 32);
  delay(500);
  Heltec.display->drawString(0, 40, "_______________________");
  Heltec.display->drawString(0, 52, "Pulsa RST nueva lectura");
  Heltec.display->display();
}

void loop()
{
  // put your main code here, to run repeatedly:
}