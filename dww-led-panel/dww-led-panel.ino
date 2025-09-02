#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#include <fade.h>

// doc : https://adafruit.github.io/Adafruit_NeoMatrix/html/class_adafruit___neo_matrix.html

#define WIDTH 32
#define HEIGHT 8
#define LEDPIN 21

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(WIDTH, HEIGHT, LEDPIN,
                                               NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG,
                                               NEO_GRB + NEO_KHZ800);

// uint16_t red = matrix.Color(255, 0, 0);
// uint32_t dww = matrix.ColorHSV(180, 67, 76);
// uint16_t off = matrix.Color(0, 0, 0);


void setup() {
  matrix.begin();
  matrix.setBrightness(40);

  Serial.begin(115200);

  // from fade.h
  generateFadeHue();

  //matrix.drawRect(0, 0, 8, 8, red);
  // matrix.drawLine(0,0,WIDTH,0, red);
  // matrix.show();
}

void loop() {
  //from fade.h -> possible to execute rest of code while fading
  FadeOnce(matrix, 300);
}


// block code execution to fade
void full_fade() {
  /*
    HSV : hue, saturation, brightness
      hue	An unsigned 16-bit value, 0 to 65535, representing one full loop of the color wheel, which allows 16-bit hues to "roll over" while still doing the expected thing (and allowing more precision than the wheel() function that was common to prior NeoPixel examples).
      sat	Saturation, 8-bit value, 0 (min or pure grayscale) to 255 (max or pure hue). Default of 255 if unspecified.
      val	Value (brightness), 8-bit value, 0 (min / black / off) to 255 (max or full brightness). Default of 255 if unspecified.
  
  */ 
  // uint16_t currentHue = 0; //random(200, 60000);
  uint32_t currentColor = matrix.ColorHSV(0, 100, 100);
  uint step = 100;
  uint speed = 50;

  for(uint16_t currentHue = 0; currentHue <= 65535; currentHue += step){
    matrix.fillScreen(currentColor);
    matrix.show();
    delay(speed);
    // update color to display
    currentColor = matrix.gamma32(matrix.ColorHSV(currentHue, 100, 100));
    Serial.print("hue : ");
    Serial.println(currentHue);

  }
}