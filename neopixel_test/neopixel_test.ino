#include <Adafruit_NeoPixel.h>

#define LEDPIN 3
#define LEDCOUNT 31

Adafruit_NeoPixel strip(LEDCOUNT, LEDPIN, NEO_GRB + NEO_KHZ800);
uint16_t red = strip.Color(30, 30, 50);

void setup() {
  strip.begin();
  strip.setBrightness(30); 
}

void loop() {
  strip.clear();

  strip.fill(red);

  strip.show();
  delay(500);
}
