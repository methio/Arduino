#include <Adafruit_NeoPixel.h>

#define NUMPIXELS 64
#define LEDPIN 3
Adafruit_NeoPixel pixels(NUMPIXELS, LEDPIN, NEO_GRB + NEO_KHZ800);

uint32_t red = pixels.Color(150, 0, 0);
uint32_t yellow = pixels.Color(150, 150, 0);

int right[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 29, 30, 31, 32, 44, 45, 46, 47, 59, 60, 61, 62, 74, 75, 76, 77};
int left[] = {64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47};



void setup() {

  pixels.begin();
  pixels.setBrightness(30);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=0; i<sizeof(right); i++) {
      pixels.setPixelColor(left[i], yellow);

      delay(200);
      pixels.show();

  }
    
}
