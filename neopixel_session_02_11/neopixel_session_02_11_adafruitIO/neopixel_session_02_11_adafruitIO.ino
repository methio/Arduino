// file where we setup the wifi connection
#include "config.h"
#include <Adafruit_NeoPixel.h>

// variable for neopixel
#define RINGPIN 21
#define LEDCOUNT 12
// NeoPixel luminosity, 0 (min) to 255 (max)
int brightness = 20;
// create neopixel object 
Adafruit_NeoPixel ring(LEDCOUNT, RINGPIN, NEO_GRB + NEO_KHZ800);


// create a rgb color
uint32_t red = ring.Color(255, 0, 0);
uint32_t green = ring.Color(0, 255, 0);

// set up the 'your_feed_name' feed
AdafruitIO_Feed *your_feed_name = io.feed("your_feed_name");

void setup() {  
  // INITIALIZE NeoPixel ring object (REQUIRED)
  ring.begin();   
  
  // Set BRIGHTNESS 
  ring.setBrightness(brightness); 

  // start the serial connection
  Serial.begin(115200);

  // wait for serial monitor to open
  while(! Serial);

  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  // on message (new value) use the callback function handleMessage()
  your_feed_name->onMessage(handleMessage);

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());
  your_feed_name->get(); // get latest value on feed
}

void loop() {

  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();

}

// this function is called whenever an 'digital' feed message
// is received from Adafruit IO. it was attached to
// the 'digital' feed in the setup() function above.
void handleMessage(AdafruitIO_Data *data) {

  // Set all pixel colors to 'off'
  ring.clear();

  // Set color to fill the ring 
  // data is the "value" from the feed. 
  // The method ->toNeoPixel() translate data into a valid rgb color
  ring.fill(data->toNeoPixel());
  
  // Now we display color
  ring.show();
}
