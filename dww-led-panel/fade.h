const int fadeLength = 15;
int currentFadeStep = 0;
uint16_t currentHues[fadeLength];
uint16_t hueA = 30001; // hue: 0 -> 65535
uint16_t hueB = 45003;

/* 
  DWW hues
  25000 <- light blue-green
  35000 <- light blue
  HUE wheel : https://learn.adafruit.com/adafruit-neopixel-uberguide/arduino-library-use
*/


uint16_t lerpHue(uint16_t hueA, uint16_t hueB, float t){
  return  hueA * (1 - t) + hueB * t;
}
float mapf(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
uint16_t getRandomHue(uint16_t min = 25000, uint16_t max = 35000){
  return random(min, max);
}
void generateFadeHue(){
  hueA = getRandomHue();
  hueB = getRandomHue(abs(hueA - 100), abs(hueA + 100));
  for(int i = 0; i <= fadeLength; i++){
    float currentStep = mapf(i, 0, fadeLength, 0, 1);
    uint16_t hue = lerpHue(hueA, hueB, currentStep);
    currentHues[i] = hue;
  }
}
// we do one step of fade
void FadeOnce(Adafruit_NeoPixel & r, int speed = 200){
  if(currentFadeStep >= fadeLength){
    currentFadeStep = 0;
    generateFadeHue();
  }
  r.fill(r.ColorHSV(currentHues[currentFadeStep], 255, 255));
  r.show();
  delay(speed);
  currentFadeStep ++;
}



// // block code execution to fade
// void full_fade() {
//   /*
//     HSV : hue, saturation, brightness
//       hue	An unsigned 16-bit value, 0 to 65535, representing one full loop of the color wheel, which allows 16-bit hues to "roll over" while still doing the expected thing (and allowing more precision than the wheel() function that was common to prior NeoPixel examples).
//       sat	Saturation, 8-bit value, 0 (min or pure grayscale) to 255 (max or pure hue). Default of 255 if unspecified.
//       val	Value (brightness), 8-bit value, 0 (min / black / off) to 255 (max or full brightness). Default of 255 if unspecified.
  
//   */ 
//   // uint16_t currentHue = 0; //random(200, 60000);
//   uint32_t currentColor = matrix.ColorHSV(0, 100, 100);
//   uint step = 100;
//   uint speed = 50;

//   for(uint16_t currentHue = 0; currentHue <= 65535; currentHue += step){
//     matrix.fillScreen(currentColor);
//     matrix.show();
//     delay(speed);
//     // update color to display
//     currentColor = matrix.gamma32(matrix.ColorHSV(currentHue, 100, 100));
//     Serial.print("hue : ");
//     Serial.println(currentHue);

//   }
// }
