// https://adafruit.github.io/Adafruit-GFX-Library/html/class_adafruit___g_f_x.html#aded338777abeac3c457660023f5c0724
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>

#define TFT_CS        10
#define TFT_RST        9
#define TFT_DC         8
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

//
int16_t y=0;
uint16_t w = tft.width()-1;
uint16_t h = tft.height()-1;


void setup() {
  Serial.begin(9600);

  tft.init(240, 320);
  delay(200);
  // set the direction you want
  tft.setRotation(0); // 0: 0 | 1: 90 | 2: 180
  // clean screen
  tft.fillScreen(ST77XX_BLACK);
}

void loop() {
  // tft.fillScreen(ST77XX_BLACK);
  
  // for (y=0; y < tft.height(); y+=10) {
  //   tft.drawLine(0, y, w, y, 0x001F);
  //   delay(1);
  // }

  tft.setCursor(0, 0);
  tft.setTextColor(0x001F);
  tft.setTextWrap(true);
  tft.setTextSize(3);
  tft.print("coucou le rap");

    
  delay(100);


}

void testfillcircles(uint8_t radius, uint16_t color) {
  for (int16_t x=radius; x < tft.width(); x+=radius*2) {
    for (int16_t y=radius; y < tft.height(); y+=radius*2) {
      tft.fillCircle(x, y, radius, color);
    }
  }
}
