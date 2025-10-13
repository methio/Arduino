#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#include <fade.h>
#include "config.h"

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

// set up the feed, where to get data 
AdafruitIO_Feed *digital = io.feed("color25");

void setup() {
  matrix.begin();
  matrix.setBrightness(40);

  Serial.begin(115200);

  // wait for serial monitor to open
  while(! Serial);

  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  // set up a message handler for the 'digital' feed.
  // the handleMessage function (defined below)
  // will be called whenever a message is
  // received from adafruit io.
  digital->onMessage(handleMessage);

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());
  digital->get();


  // from fade.h
  generateFadeHue();

  //matrix.drawRect(0, 0, 8, 8, red);
  // matrix.drawLine(0,0,WIDTH,0, red);
  // matrix.show();
}

void loop() {
  //from fade.h -> possible to execute rest of code while fading
  // FadeOnce(matrix, 300);

  // keeps client (huzzah32) connected to io.adafruit.com
  io.run();
}

// this function is called whenever an 'color' feed message
// is received from Adafruit IO. it was attached to
// the 'color' feed in the setup() function above.
void handleMessage(AdafruitIO_Data *data) {

  // methods for AdafruitIO_Data: https://adafruit.github.io/Adafruit_IO_Arduino/html/class_adafruit_i_o___data.html#af2ae58fda00ca0d775dd1baf5ff39716

  Serial.print("received <- ");
  Serial.println(data->toString());

  matrix.clear();
  matrix.fill(data->toNeoPixel());
  matrix.show();
}



