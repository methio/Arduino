// libraries
#include <Wire.h>
// seesaw adress: 0x36
// lcd adress:    0x27
#include <Adafruit_seesaw.h>
#include <LiquidCrystal_I2C.h>

// light sensor
#define lightSensorPin A2   // the light sensor pin
int lightValue = 0;         // the light sensor value will be stored in this variable

// seeSaw 
Adafruit_seesaw soilSensor; // create the object soilSensor out of the Adafruit_seesaw class
uint16_t soilValue = 0;     // soilValue as a percentage
float tempValue = 0;        // temperature as °C float value

// lcd
LiquidCrystal_I2C screen(0x27, 16, 2); // create the object screen out of the LiquidCrystal_I2C class

void setup() {
  // intialize serial communication
  Serial.begin(115200);

  // make sure Seesaw is working
  if (!soilSensor.begin(0x36)) {
    Serial.println("ERROR! seesaw not found");
    while(1) delay(1);
  } else {
    Serial.print("seesaw started! version: ");
    Serial.println(soilSensor.getVersion(), HEX);
  }

  // make sure the screen is working   
	screen.init();                     // initialize the LCD	
	screen.backlight();                // turn on backligh
	screen.print("Floopies °-°");     // display a welcome message
}
 
void loop() {

  // get light value
  lightValue = analogRead(lightSensorPin);

  // get soil and temp values
  tempValue = soilSensor.getTemp();
  soilValue = soilSensor.touchRead(0);
  int percentSoil = ((float)soilValue /  1023.00) * 100.0;    

  // debug values in the serial monitor
  Serial.print("Temperature: "); Serial.print(tempValue); Serial.println("°C");
  Serial.print("soil moisture: "); Serial.print(percentSoil); Serial.println("%");

  // print values on the screen 
  screen.clear();               // clean screen
  screen.setCursor(0, 0);       // move cursor to origin
  screen.print("temp:");   
  screen.setCursor(5, 0);  
  screen.print(tempValue);
  screen.setCursor(10, 0); 
  screen.print((char) 223);   
  screen.setCursor(11, 0); 
  screen.print("C"); 
  screen.setCursor(0, 1);
  screen.print("soil:");   
  screen.setCursor(5, 1);  
  screen.print(percentSoil);
  screen.setCursor(8, 1); 
  screen.print("%");  
  screen.setCursor(11, 1);
  screen.print("l:");   
  screen.setCursor(13, 1);  
  screen.print(lightValue);


delay(1000);
}