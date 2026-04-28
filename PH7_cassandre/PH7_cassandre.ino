//*****************************************
//     VARIABLES DELAIS ANIMATIONS
int affichageLogoAllumage = 3000;
int miseEnVeille = 10000;
int affichageResultat = 15000;
//*****************************************

// screen libraries
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>
// create screen 
#define TFT_CS         14
#define TFT_RST        15
#define TFT_DC         32
Adafruit_ST7789 screen(TFT_CS, TFT_DC, TFT_RST);            // screen documentation-> https://learn.adafruit.com/2-0-inch-320-x-240-color-ips-tft-display/pinouts

// logo stored in "image_logo_bits"
#include "logo.h"
// wave stored in "image_vague_bits"
#include "wave.h"
// custom functions for display
#include "screenFunctions.h"

// soil sensor
#include "Adafruit_seesaw.h"
Adafruit_seesaw ss;
uint16_t capacitveValue = 0;
int capacitveThreshold = 450; // Valeur calibrée le 11/02 


// button
#define BUT 12 // touchpin 5
int buttonValue = 0;
int buttonThreshold = 1480; // Valeur calibrée le 11/02 

// scenarios handling
int scenario = 0; // 0 = potable, 1 = non potable
int screenToDisplay = 0;
bool isThereWater = false;
bool isThereClick = false;
bool launchScenario = true; // should launch a new scenario
unsigned long timeStart = 0;
bool isWaiting = false;

void setup() {
  // start Serial communication
  Serial.begin(115200);

  //check if seesaw is connected at adress 0x36 and working
  if (!ss.begin(0x36)) {
    Serial.println("ERROR! seesaw not found");
    while(1) delay(1);
  } else {
    Serial.print("seesaw started! version: ");
    Serial.println(ss.getVersion(), HEX);
  }

  // set up screen
  screen.init(240, 320);  // screen size
  screen.setRotation(1);  // 0 vertical - 1 horizontal
  clear_screen();         // start with black screen
  delay(10);
  welcome_screen();       // and display welcome message
  delay(affichageLogoAllumage);
}

void loop() {
  // listen to sensors: button and water
  capacitveValue = ss.touchRead(0);
  //read button
  buttonValue = touchRead(BUT);
  // debug
  // Serial.print("capacitive ");Serial.print(capacitveValue);Serial.print(" -- ");Serial.print("button ");Serial.println(buttonValue);

  // update state listeners
  isThereClick = buttonValue < buttonThreshold ? true : false;
  isThereWater = capacitveValue > capacitveThreshold ? true : false;
  // debug
  // Serial.print("isThereClick ");Serial.print(isThereClick);Serial.print(" -- ");Serial.print("isThereWater ");Serial.println(isThereWater);

  // check if we need to display stuffs on the screen
  if(isThereClick && isThereWater && launchScenario){
    // evite de relancer l'animation
    launchScenario = false;
    // affiche l'écran de chargement
    screenToDisplay = 2;    
  }else{
    // délai pour savoir si on retourne à l'écean noir
    if (isWaiting && millis() - timeStart >= miseEnVeille) {
      screenToDisplay = 0;
      isWaiting = false;
    }
  }
  

  // scenario steps management
  switch(screenToDisplay){
    case 0: 
      // iddle state
      clear_screen();
      break;
    case 1: 
      // welcome page
      welcome_screen();
      if(isWaiting == false){
        timeStart = millis();  
        isWaiting = true;
      }
      break;
    case 2: 
      clear_screen();
      // detection page
      for(int i = 0; i >= -160; i-=25){
        drawloading(i);
        delay(10);
      }
      screenToDisplay = 3;
      break;
    case 3: 
      Serial.print("scenario ");Serial.println(scenario);
      clear_screen();
      // result page
      if(scenario == 0){
        drawresult_ok();
        scenario = 1;     
      }else{
        drawresult_fail();
        scenario = 0;
      }
      delay(affichageResultat);
      screenToDisplay = 1;
      launchScenario = true;
      clear_screen();
      break;
  }
  delay(200);
}