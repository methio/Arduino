#include <Adafruit_NeoPixel.h>

#define LED_COUNT 12
#define LED_PIN 2

// object declaration
Adafruit_NeoPixel ring(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

uint32_t purple = ring.Color(255, 0, 255);
uint32_t green = ring.Color(0, 255, 0);


void setup() {
  // put your setup code here, to run once:

  ring.begin();
  ring.setBrightness(20);

}

void loop() {
  // put your main code here, to run repeatedly:

  ring.clear(); // switch off all leds

  // set colors to led ring
  ring.fill(purple, 0, 6);
  ring.setPixelColor(9, green);

  ring.show(); 



}










