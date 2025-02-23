/*
  myCO2.h - Library for mqtt client
  lib_deps =
    wifwaf/MH-Z19
*/
#ifndef MYCO2_h
#define MYCO2_h

#include "Arduino.h"
#include <HardwareSerial.h>
// #include <SoftwareSerial.h>
#include <MHZ19.h>
#include "main.h"

#define LOOP_SECONDS_CO2 4
#define SCAN_SECONDS_CO2 30
#define CALIBRATE_SECONDS 40 // timeElapse = 12e5; //  20 minutes in milliseconds

// Nutzung der Schnittstelle UART2
#define RX2 13 //16 is used for OLED_RST !
#define TX2 12

#define MHZ19_BAUDRATE 9600
#define MHZ19_PROTOCOL SERIAL_8N1
#define MHZ19_RANGE 5000 // Obergrenze des Messbereichs des Sensors
#define MHZ19_PWM_PIN 5

class myCO2 // define class
{
public:
  myCO2(void); // constructor, which is used to create an instance of the class
  // void loop(int *iValue, char *cValue);
  void loop(sensor_data_struct *sData);
  void begin(char *cValue);
  void calibrateStart(void);
  void calibrateEnd(void);
  long calibrateTimer(void);
  void status(char *value);
  int value(void);
  int valueTemp(void);
  int version(void);

private:
  MHZ19 mhz19b; // Sensor-Objekt
  unsigned long currentMillisLoop = 0, previousMillis = 0, previousMillisScan = 0;
  unsigned long intervalLoop = LOOP_SECONDS_CO2 * 1000;
  unsigned long intervalScanDevice = SCAN_SECONDS_CO2 * 1000;
  unsigned long calibrateStartTime = 0, calibrateInterval = CALIBRATE_SECONDS * 1000;
  // CO2-Werte bei serieller und PWM-Messung
  int co2_ser, co2_pwm;
  int temp_mh; //Temperatur des MH-Z19B
  char mhz19_version[4];
  char statusChar[100];
  bool sensorFound;
  bool mhz19bCalibration = false;
};

#endif
