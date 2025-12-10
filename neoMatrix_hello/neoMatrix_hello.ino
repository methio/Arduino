#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include <gamma.h>

// Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, 6,
//   NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
//   NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
//   NEO_GRBW            + NEO_KHZ800);

Adafruit_NeoPixel matrix = Adafruit_NeoPixel(64, 6, NEO_RGBW + NEO_KHZ800);

uint16_t red = matrix.Color(50, 255, 255, 0); // (white value, Red value, Blue value, Green value)

void setup() {
  matrix.begin();
  matrix.setBrightness(10);
}

void loop() {

  for(int i = 0; i <= 64; i++){

    matrix.clear();
    // matrix.fill(red);
    matrix.setPixelColor(i, red);
    matrix.show();


    delay(200);
  }

  // matrix.drawPixel(0,0,red);
  // matrix.show();
  // delay(200);
  

}
