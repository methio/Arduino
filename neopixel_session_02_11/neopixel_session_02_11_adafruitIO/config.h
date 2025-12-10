/************************ Adafruit IO Config *******************************/

// visit io.adafruit.com if you need to create an account,
// or if you need your Adafruit IO key.
// #define IO_USERNAME "your_username"
// #define IO_KEY "your_key"
#define IO_USERNAME  "methio"
#define IO_KEY       "aio_giqv83kW2b25N5yH9OwU5dthwYh1"

#define WIFI_SSID "thomaswifi"
#define WIFI_PASS "thomaswifi"

#include "AdafruitIO_WiFi.h"

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);