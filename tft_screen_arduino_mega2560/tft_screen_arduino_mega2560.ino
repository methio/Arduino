// https://adafruit.github.io/Adafruit-GFX-Library/html/class_adafruit___g_f_x.html#aded338777abeac3c457660023f5c0724
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>

#define TFT_CS        53
#define TFT_RST        9
#define TFT_DC         10
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

//
int16_t y=0;
uint16_t w = tft.width()-1;
uint16_t h = tft.height()-1;


void setup() {
  Serial.begin(9600);

  tft.init(240, 320, SPI_MODE0);
  delay(200);
  // set the direction you want
  tft.setRotation(0); // 0: 0 | 1: 90 | 2: 180
  // clean screen
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(0x001F);
  tft.setTextWrap(true);
  tft.setTextSize(3);
  tft.print("coucou le rap");
}

void loop() {
}