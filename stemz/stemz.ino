#include <Adafruit_NeoPixel.h>
#include "Adafruit_seesaw.h"
#include "AdafruitIO_WiFi.h"

// IO credentials
#define IO_USERNAME "methio"
#define IO_KEY "aio_iZwd53sqnwoUIMJLOM7Xq8mZExnn"

// wifi credentials
#define WIFI_SSID "thomaswifi"
#define WIFI_PASS "thomaswifi"

// wifi object
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

// seesaw setup
Adafruit_seesaw seeSaw;
uint16_t moisture = 0;

// relay setup
#define relay 21

// led Strip
#define LEDPIN 4
#define NUMPIXELS 30  // change with number of pixels
int BRIGHTNESS = 100; // from 0 to 255

Adafruit_NeoPixel strip(NUMPIXELS, LEDPIN, NEO_GRB + NEO_KHZ800);

// color
uint32_t lightYellow = strip.Color(216,194,2);
uint32_t black = strip.Color(0,0,0);

// set up the feeds
AdafruitIO_Feed *pump = io.feed("pump");
AdafruitIO_Feed *leds = io.feed("leds");


void setup() {
  // start the serial connection
  Serial.begin(115200);

  // wait for serial monitor to open
  while(! Serial);

  // setup seesaw
  if (!seeSaw.begin(0x36)) {
    Serial.println("ERROR! seesaw not found");
    while(1) delay(1);
  } else {
    Serial.print("seesaw started! version: ");
    Serial.println(seeSaw.getVersion(), HEX);
  }

  // setup relay
  pinMode(relay, OUTPUT);

  // strip setup
  strip.begin();   
  strip.setBrightness(BRIGHTNESS); 

  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  // when new value on the feed, call function newXXXXMessage()
  pump->onMessage(newPumpMessage);
  leds->onMessage(newLedsMessage);

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());

  // get initial values
  pump->get();
  leds->get();
}

void loop() {
  io.run();

  // get moisture and do nothing with it
  moisture = seeSaw.touchRead(0);
  // Serial.print("Capacitive: "); Serial.println(moisture);

  // small delay to avoid flood
  delay(200);
}

// When new value in the pump feed
void newPumpMessage(AdafruitIO_Data *data) {
  Serial.print("pump received <- ");
  if(data->toPinLevel() == HIGH)
    Serial.println("OFF");
  else
    Serial.println("ON");

  digitalWrite(relay, data->toPinLevel());
}

// When new value in the leds feed
void newLedsMessage(AdafruitIO_Data *data) {
  Serial.print("led received <- ");
  if(data->toPinLevel() == HIGH){
    Serial.println("OFF");
    strip.fill(black);
  }else{
    Serial.println("ON");
    strip.fill(lightYellow);
  }
    strip.show();  
}