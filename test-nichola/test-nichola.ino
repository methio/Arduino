// creating the links
#include <Adafruit_NeoMatrix.h>
#include <gamma.h>
#include "config.h"
// set up the 'color' feed
AdafruitIO_Feed *color = io.feed("data-color");
//defining relevant features
#define PIN 21
//(#grid width, #grid height,  pin number it is connected to on arduino)
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, 2,
  NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800);
// uint32_t red = matrix.Color(255,0,0);

String dataString;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  matrix.begin();
  matrix.setBrightness(5);
  matrix.show();
    // wait for serial monitor to open
  while(! Serial);
  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();
  // set up a message handler for the 'digital' feed.
  // the handleMessage function (defined below)
  // will be called whenever a message is
  // received from adafruit io.
  color->onMessage(handleDataColor);
  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  // now we are connected
  Serial.println();
  Serial.println(io.statusText());
  delay(500);

  color->get();

  dataString.reserve(520);
}
void loop() {
  // put your main code here, to run repeatedly:
  io.run();
}
// allow datacolor array connect with matrix
void handleDataColor(AdafruitIO_Data *data){
  Serial.println("Fetching data color from AdafruitIO");
  dataString = data->toString();
  Serial.println(dataString.length());
  Serial.println(dataString);

  // wipe clean
  //matrix.clear();
/*
  For(int i=0; i <= 64; i++){
    data[i].toNeoPixel();
    matrix.setPixelColor(i,data->toNeoPixel());
  }
*/
  //make it visible in matrix
  //matrix.show();
}