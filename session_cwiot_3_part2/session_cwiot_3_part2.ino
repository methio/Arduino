#include <Adafruit_NeoMatrix.h>
#include <gamma.h>

#include "config.h"

/************************ Example Starts Here *******************************/

// Setup the led ring
#include <Adafruit_NeoPixel.h>
#define LED_COUNT 12
#define LED_PIN 21
// object declaration
Adafruit_NeoPixel ring(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
uint32_t purple = ring.Color(255, 0, 255);
uint32_t green = ring.Color(0, 255, 0);

// Setup the light sensor
#define LIGHT_PIN A2
int lightValue = 0;

// set up the 'digital' feed
AdafruitIO_Feed *digital = io.feed("color");
AdafruitIO_Feed *light = io.feed("light");


void setup() {

  pinMode(LIGHT_PIN, INPUT);
  
  ring.begin();
  ring.setBrightness(20);
  
  // start the serial connection
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

}

void loop() {

  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();


  // we want to read the light value
  lightValue = analogRead(LIGHT_PIN);
  // debug purpose
  Serial.print("the current light value is:");
  Serial.println(lightValue);
  // we send the light value to the feed
  light->save(lightValue);
  // we wait 3seconds to avoid flooding the feed
  delay(3000);


}

// this function is called whenever an 'digital' feed message
// is received from Adafruit IO. it was attached to
// the 'digital' feed in the setup() function above.
void handleMessage(AdafruitIO_Data *data) {

  Serial.print("received <- ");
  Serial.println(data->toString());

  ring.clear(); // switch off all leds

  // set colors to led ring
  // ->toNeoPixel() is a method to translate data into a RGB color for the ring
  ring.fill(data->toNeoPixel());

  ring.show(); 

  
}

















