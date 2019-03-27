#include "addi_meteo.h"
void setup() {
  // put your setup code here, to run once:
  lcd.init();
  lcd.backlight();
  //Show title splash screen
  while(millis() < splashScreenDur){
    lcd.setCursor(3,0);
    lcd.print(title); 
  }
  while(millis() < 10000){
    //error managing
    if(si7021.initialize()){
      lcd.init();
      lcd.setCursor(1,0);
      lcd.print("My sensor works!");
    }else{
      lcd.init();
      lcd.setCursor(1,0);
      lcd.print("No sensor..:(");
      while(1) {};
    }
  }
  displayText();
}

void displayText(){
  lcd.init();
  lcd.setCursor(0,0);
  lcd.print("temp:");
    //print ° sign
  lcd.createChar(0,degree);
  lcd.setCursor(14,0);
    // need to re-position after createChar
  lcd.write(0);
  lcd.setCursor(15,0);
  lcd.print("C");
  
  lcd.setCursor(0,1);
  lcd.print("humidit:");
  lcd.setCursor(15,1);
  lcd.print("%");
}

void loop() {
  // put your main code here, to run repeatedly:
  //Get values from sensor
  /*si7021.getTemperature(temp);
  si7021.getHumidity(hum);
  si7021.triggerMeasurement();*/

  //print values
  lcd.setCursor(10,0);
  lcd.print(temp.readTemperature(), 1);
  lcd.setCursor(10,1);
  lcd.print(hum.readHumidity(), 1);

  }
