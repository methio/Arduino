/* 
  documentation from course: https://makerslabemlyon.notion.site/12-LEDs-Neopixels-ring-ec9bd8299ccc4f63835257a08fa594c4?source=copy_link
  documentation from Adafruit: https://adafruit.github.io/Adafruit_NeoPixel/html/class_adafruit___neo_pixel.html
*/
// libraries
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




void setup() {
  // INITIALIZE NeoPixel ring object (REQUIRED)
  ring.begin();   
  
  // Set BRIGHTNESS 
  ring.setBrightness(brightness); 

}

void loop() {
  // Set all pixel colors to 'off'
  ring.clear();

  // Set color to fill the ring 
  ring.fill(red);
  // ring.fill(red, 2, 8); you can define first led to switch on and how many leds to light

  // Now we display color
  ring.show();
}
