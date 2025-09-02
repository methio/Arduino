#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel ring(12, 21, NEO_GRB + NEO_KHZ800);
// variables
int fadeLength = 15;
int currentFadeStep = 0;
uint16_t currentHues[15];
uint16_t hueA = 30001; // hue: 0 -> 65535
uint16_t hueB = 45003;
uint16_t lerpHue(uint16_t hueA, uint16_t hueB, float t){
  return  hueA * (1 - t) + hueB * t;
}
float mapf(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
uint16_t getRandomHue(){
  return random(0, 65535);
}
void generateFadeHue(){
  hueA = getRandomHue();
  hueB = getRandomHue();
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
  ring.fill(r.ColorHSV(currentHues[currentFadeStep], 255, 255));
  ring.show();
  delay(speed);
  currentFadeStep ++;
}
void setup() {
  Serial.begin(115200);
  generateFadeHue();
}
void loop() {
  FadeOnce(ring, 300);
}