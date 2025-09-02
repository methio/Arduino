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
