#include <DHT.h>
#include "config.h"
#define PINLIGHT A3
#define DHTSENSOR 21 // Digital 21
#define DHTTYPE DHT11
DHT dht(DHTSENSOR, DHTTYPE); //dht
int lightValue = 0; // photosensor
// button state
int current = 1;
int last = 0;
// set up the 'digital' feed
AdafruitIO_Feed *humidityfeed = io.feed("humidity");
void setup() {
  /// put your setup code here, to run once:
  pinMode(PINLIGHT, INPUT);
  Serial.begin(115200);
  dht.begin();
  // wait for serial monitor to open
  while(! Serial);
  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();
  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  // we are connected
  Serial.println();
  Serial.println(io.statusText());
}
void loop() {
  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();
  lightValue = readLight();
  int temperature = dht.readTemperature();
  int humidity = dht.readHumidity();
  current = humidity;
  Serial.print("La lumière fût: " );
  Serial.println(lightValue);
  Serial.print("La température est: " );
  Serial.println(temperature );
  Serial.print("L'humidité est: " );
  Serial.println(humidity);
  // return if the value hasn't changed
  if(current == last)
    return;
  // save the current state to the 'digital' feed on adafruit io
  Serial.print("sending temperature -> ");
  Serial.println(current);
  humidityfeed->save(current);
  // store last button state
  last = current;
  delay(3000);
}
int readLight() {
  int current = constrain(analogRead(PINLIGHT), 0, 1023);
  int currentConvertValue = map(current, 0, 1023, 100, 0);
  return currentConvertValue;
}