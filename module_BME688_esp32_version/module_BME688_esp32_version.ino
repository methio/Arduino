// module to detect temperature, humidity, barometric pressure, and VOC gas.
// learn more in the product page: https://learn.adafruit.com/adafruit-bme680-humidity-temperature-barometic-pressure-voc-gas/arduino-wiring-test


/*  To use the BME Component, you will need to install
    the following library: Adafruit_BME680 library
*/
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME680 bme; // I2C

/* we create array with 5 entries

  index     data type    eg value   unit
 data[0] | temperature  | 24.20   | °C
 data[1] | pression     | 9994.77 | hPa
 data[2] | humidity     | 46.84   | %
 data[3] | gas          | 9.38    | KOhms
 data[4] | altitude     | 154.67  | m
*/
float data[5];

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
}

void loop() {
  // make sure BME module works
  if (! bme.performReading()) {
    Serial.println("Failed to perform reading :(");
    return;
  }
  // get temperature
  Serial.print("Temperature = ");
  Serial.print(bme.temperature);
  Serial.println(" *C");
  data[0] = bme.temperature; // add latest temperature to array

  // get pressure
  Serial.print("Pressure = ");
  Serial.print(bme.pressure / 100.0);
  Serial.println(" hPa");
  data[1] = bme.pressure / 100.0; // add latest pressure to array

  // get humidity
  Serial.print("Humidity = ");
  Serial.print(bme.humidity);
  Serial.println(" %");
  data[2] = bme.humidity;       // add latest humidity to array

  // get gas
  Serial.print("Gas = ");
  Serial.print(bme.gas_resistance / 1000.0);
  Serial.println(" KOhms");
  data[3] = bme.gas_resistance / 1000.0;  // add latest gas to array

  // get altitude
  Serial.print("Approx. Altitude = ");
  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println(" m");
  data[4] = bme.readAltitude(SEALEVELPRESSURE_HPA); // add latest altitude to array

  // serial print the whole array
  for(int i = 0; i <= 4; i++){
    Serial.println(data[i]);
  }
  // wait 2 seconds before next reading
  Serial.println();
  delay(2000);

}
