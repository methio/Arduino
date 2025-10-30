// module to detect temperature, humidity, barometric pressure, and VOC gas.
// learn more in the product page: https://learn.adafruit.com/adafruit-bme680-humidity-temperature-barometic-pressure-voc-gas/arduino-wiring-test


/*  To use the BME Component, you will need to install
    the following library: Adafruit_BME680 library
*/
// libraries
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"
#include "config.h"

// Setup for BME688 module
#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME680 bme;

/* we create array with 5 entries

  index     data type    eg value   unit
 data[0] | temperature  | 24.20   | °C
 data[1] | pression     | 9994.77 | hPa
 data[2] | humidity     | 46.84   | %
 data[3] | gas          | 9.38    | KOhms
 data[4] | altitude     | 154.67  | m


This is what we send to adafruitIO feed. 
 data = [23.87,994.52,45.09,39.53,157.12];
            |     |      |    |     └── altitude
            |     |      |    └── gas 
            |     |      └── humidity 
            |     └── pression
            └── temperature
*/
String data = "[";

// setup the adafruit IO feed: replace "your_feed_name"
AdafruitIO_Feed *your_feed_name = io.feed("your_feed_name");

void setup() {
  // start serial communication
  Serial.begin(9600);

  // make sure BME device is working
  if (!bme.begin()) {
    Serial.println("Could not find a valid BME680 sensor, check wiring!");
    while (1);
  }
  // Set up oversampling and filter initialization
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // 320*C for 150 ms

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
  // keep connection to adafruit services alive
  io.run();

  // make sure BME module works
  if (! bme.performReading()) {
    Serial.println("Failed to perform reading :(");
    return;
  }
  // get temperature
  // Serial.print("Temperature = ");
  // Serial.print(bme.temperature);
  // Serial.println(" *C");
  float temp = bme.temperature; // add latest temperature to array

  // get pressure
  // Serial.print("Pressure = ");
  // Serial.print(bme.pressure / 100.0);
  // Serial.println(" hPa");
  float press = bme.pressure / 100.0; // add latest pressure to array

  // get humidity
  // Serial.print("Humidity = ");
  // Serial.print(bme.humidity);
  // Serial.println(" %");
  float humi = bme.humidity;       // add latest humidity to array

  // get gas
  // Serial.print("Gas = ");
  // Serial.print(bme.gas_resistance / 1000.0);
  // Serial.println(" KOhms");
  float gas = bme.gas_resistance / 1000.0;  // add latest gas to array

  // get altitude
  // Serial.print("Approx. Altitude = ");
  // Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  // Serial.println(" m");
  float alti = bme.readAltitude(SEALEVELPRESSURE_HPA); // add latest altitude to array

  // concatenate the data
  data = data + temp + "," + press + "," + humi + "," + gas + "," + alti + "]";
  Serial.println(data);

  // save data to adafruit feed
  your_feed_name->save(data);

  // wait 2 seconds before next reading
  Serial.println();
  delay(2000);

  // clear the array
  data = "[";

}
