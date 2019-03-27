#include <Wire.h>
#include "i2c.h"
#include <LiquidCrystal_I2C.h>
#include "i2c_SI7021.h"

SI7021 si7021;
LiquidCrystal_I2C lcd(0x27,20,4);

byte newChar1[8]={
  B00000,
  B00000,
  B00000,
  B00001,
  B00001,
  B00101,
  B00101,
  B10101
};
byte newChar2[8]={
  B00000,
  B00000,
  B01110,
  B10001,
  B00100,
  B01010,
  B00000,
  B00100
};

void setup()
{
    Serial.begin(115200);

    Serial.print("Probe SI7021: ");
    if (si7021.initialize()) Serial.println("Sensor found!");
    else
    {
        Serial.println("Sensor missing");
        while(1) {};
    }
}

void loop()
{
    static float humi, temp;

    si7021.getHumidity(humi);
    si7021.getTemperature(temp);
    si7021.triggerMeasurement();

    Serial.print("TEMP: ");
    Serial.print(temp);
    Serial.print(" HUMI: ");
    Serial.print(humi);
    Serial.println("");

  lcd.init();                // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("TEMP:");
  lcd.setCursor(6,0);
  lcd.print(temp);
  lcd.setCursor(0,1);
  lcd.print("HUMI:");
  lcd.setCursor(6,1);
  lcd.print(humi);

  //Wire.begin();
  //lcd.init();
  lcd.createChar(0,newChar1);
  lcd.setCursor(14,0);
// need to re-position after createChar
  lcd.write(0);
  
  lcd.createChar(1,newChar2);
  lcd.setCursor(14,1);
// need to re-position after createChar
  lcd.write(1);
}

/**<

Program size:
A1.0.5: 6896b
A1.5.7: 6590b
A1.6.3: 6484b / 499b
 */
