#include "Adafruit_Si7021.h"
#include <Wire.h>
//lcd library
#include <LiquidCrystal_I2C.h>
//sensor library
#include "i2c_SI7021.h"
//Adressage Capteur

SI7021 si7021;
//Adressage LCD
LiquidCrystal_I2C lcd(0x27,20,4);

//Constants
const String title = "Meteo";
const int splashScreenDur = 5000;

//degree sign
byte degree[8]={
  B00110,
  B01001,
  B01001,
  B00110,
  B00000,
  B00000,
  B00000,
  B00000
};
//additionnal init var
//float temp;
//float hum;
Adafruit_Si7021 temp = Adafruit_Si7021();
Adafruit_Si7021 hum = Adafruit_Si7021();
//logs var
