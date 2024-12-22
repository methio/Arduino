
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#define WIDTH 8
#define HEIGHT 8
#define LEDPIN 3
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(WIDTH, HEIGHT, LEDPIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
  NEO_GRB            + NEO_KHZ800);

uint16_t red = matrix.Color(255, 0, 0);
uint16_t off = matrix.Color(0, 0, 0);


// uint16_t posX = 0;
// uint16_t posY = 0;
// uint16_t width = 2;
// uint16_t height = 8;

void setup() {
  matrix.begin();
  matrix.setBrightness(40);
  

}

void loop() {
  // matrix.fillScreen(0);

  blinkLeft(200, red, off);
  // displayLeft(red);

  blinkRight(200, red, off);
  // displayRight(red);
}


void displayRight(uint16_t currentColor){
  uint16_t posX = 0;
  uint16_t posY = 0;
  uint16_t width = 2;
  uint16_t height = 8;
  
  matrix.drawRect(posX, posY, width, height, currentColor);
  matrix.fillRect(posX, posY, width, height, currentColor);
  matrix.drawRect(posX, posY, height, width, currentColor);
  matrix.fillRect(posX, posY, height,  width, currentColor);

  matrix.show();
}

void displayLeft(uint16_t currentColor){
  uint16_t width = 2;
  uint16_t height = 8;
  
  matrix.drawRect(6, 0, width, height, currentColor);
  matrix.fillRect(6, 0, width, height, currentColor);
  matrix.drawRect(0, 6, height, width, currentColor);
  matrix.fillRect(0, 6, height, width, currentColor);

  matrix.show();
}

void blinkLeft(int speed, uint16_t colorA, uint16_t colorB){
  displayLeft(colorA);
  delay(speed);
  displayLeft(colorB);
  delay(speed);
}
void blinkRight(int speed, uint16_t colorA, uint16_t colorB){
  displayRight(colorA);
  delay(speed);
  displayRight(colorB);
  delay(speed);
}
