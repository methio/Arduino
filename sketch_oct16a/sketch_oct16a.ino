// setting up the TMP36
#include <TMP36.h>
#define TMPPIN A0
TMP36 mytmp36(TMPPIN, 5);
int temperature = 20;

//setting up the RGB LED
#define REDPIN 3
#define BLUPIN 6
#define GREPIN 5

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // tell the arduino these pins are OUTPUTS
  pinMode(REDPIN, OUTPUT);
  pinMode(BLUPIN, OUTPUT);
  pinMode(GREPIN, OUTPUT);
}

void RGBColors(int redval=0, int bluval=255, int greval=0){
  analogWrite(REDPIN, redval);
  analogWrite(BLUPIN, bluval);
  analogWrite(GREPIN, greval);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(mytmp36.getTempC());
  temperature = mytmp36.getTempC(); 
/*
  RGBColors(198, 217, 217); //should be light green
  delay(200);
  RGBColors(255, 0, 0); 
  delay(200);
  RGBColors();
  delay(200);
*/

if(temperature < 25)
{
  RGBColors(0, 255, 0);
}else if(temperature >= 25 && temperature < 27)
{
  RGBColors(0, 0, 255);
}else 
{
  RGBColors(255, 0, 0);
}



}













