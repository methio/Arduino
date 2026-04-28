#include <Encoder.h>
// please install the following lib: Encoder by Paul Stoffregen
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>
#include <Adafruit_seesaw.h>
#include "boomers_logo_bw.h"

//ロータリー
#define BUTTON_IN     36
Encoder encoder(18, 19);

//スクリーン
#define TFT_CS  53
#define TFT_RST 9
#define TFT_DC  10

Adafruit_ST7789 screen(TFT_CS, TFT_DC, TFT_RST);

//soil sensor
Adafruit_seesaw ss;

//色
#define BLACK   0x0000
#define WHITE   0xFFFF
#define YELLOW  0xFFE0
#define CYAN    0x07FF
#define RED     0xF800
#define GREEN   0x07E0

//
enum Page {
  PAGE_START,
  PAGE_CONDITION,
  PAGE_SETTING
};

Page currentPage = PAGE_START;
unsigned long pageTimer = 0;

// profile
struct PlantProfile {
  const char* name;
  uint16_t moistMin;
  uint16_t moistMax;
  float tempMin;
  float tempMax;
};

// seesaw実測前提の例
PlantProfile plants[6] = {
  {"Type:A",     200, 350, 20.0, 35.0},
  {"Type:B",  250, 400, 18.0, 30.0},
  {"Type:C",    500, 750, 18.0, 28.0},
  {"Type:D",       450, 700, 15.0, 25.0},
  {"Type:E",      600, 850, 18.0, 26.0},
  {"Type:F",     300, 600, 15.0, 30.0}
};

int settingIndex = 0;
int selectedType = 0;

//bar range
#define MOIST_MIN 300
#define MOIST_MAX 900
#define TEMP_MIN  0
#define TEMP_MAX  40

// index position for menu
int lastPos = 0;


// time managing variables
uint16_t timer = 0;
uint16_t delayBetweenDeadlines = 10000;
uint16_t deadline = delayBetweenDeadlines;

//set-up
void setup() {
  
  Serial.begin(115200);

  Serial.println("seesaw Soil Sensor example!");
  
  if (!ss.begin(0x36)) {
    Serial.println("ERROR! seesaw not found");
    while(1) delay(1);
  } else {
    Serial.print("seesaw started! version: ");
    Serial.println(ss.getVersion(), HEX);
  }

  pinMode(BUTTON_IN, INPUT_PULLUP);

  screen.init(240, 320);
  screen.setRotation(0);
  screen.fillScreen(BLACK);

  pageTimer = millis();
}

//loop
void loop() {
  timer = millis();
  //soil sensor area
  
  // float tempC = ss.getTemp();
  // uint16_t moisture = ss.touchRead(0);

  //Serial.print("Temperature: "); Serial.print(tempC); Serial.println("*C");
  //Serial.print("moisture:"); Serial.println(moisture);
  delay(100);

  //encorder page change
  // uint16_t v = encoder.read();
  // Serial.println(v);

  switch (currentPage) {

    case PAGE_START:
      drawStartPage();
      if (millis() - pageTimer > 3000) {
        currentPage = PAGE_CONDITION;
        screen.fillScreen(BLACK);
      }
      break;

    case PAGE_CONDITION:
      if(timer >= deadline){
        drawConditionPage();
        delay(10);
        deadline = deadline + delayBetweenDeadlines;
      }

      if (digitalRead(BUTTON_IN) == LOW) {
        delay(100);
        encoder.write(settingIndex);
        currentPage = PAGE_SETTING;
        screen.fillScreen(BLACK);
      }
      break;

    case PAGE_SETTING:
      handleSettingPage();
      break;
  }
}

//start page setting

void drawStartPage() {
  screen.fillScreen(BLACK);
  screen.setTextColor(WHITE);
  screen.setTextSize(3);
  screen.setCursor(30, 140);
  

 screen.drawBitmap(56, 96, boomers_logo_bw, 128, 128, ST77XX_WHITE, ST77XX_BLACK);
 delay(3000);
}

//bar draw
void drawBar(int x, int y, int w, int h,
             float value, float minV, float maxV,
             uint16_t color) {

  value = constrain(value, minV, maxV);
  int fillW = map(value, minV, maxV, 0, w);

  screen.drawRect(x, y, w, h, WHITE);
  if (fillW > 2) {
    screen.fillRect(x + 1, y + 1, fillW - 2, h - 2, color);
  }
}

// condition page
void drawConditionPage() {
  screen.fillScreen(BLACK);

  float temperature = ss.getTemp();
  uint16_t moisture = ss.touchRead(0);

 // Serial.print("Temperature: "); Serial.print(temperature); Serial.println("*C");
 // Serial.print("moisture:"); Serial.println(moisture);

  PlantProfile p = plants[selectedType];

  screen.setTextSize(2);
  screen.setTextColor(CYAN);

  screen.setCursor(10, 10);
  screen.print(p.name);

  // Moisture
  screen.setCursor(10, 40);
  screen.print("Moist:");
  screen.setCursor(160, 40);
  screen.print(moisture);

  drawBar(
    10, 65, 220, 16,
    moisture, MOIST_MIN, MOIST_MAX,
    (moisture >= p.moistMin && moisture <= p.moistMax) ? GREEN : RED
  );

  screen.setCursor(10, 85);
  screen.print("OK ");
  screen.print(p.moistMin);
  screen.print("-");
  screen.print(p.moistMax);

  // Temperature
  screen.setCursor(10, 120);
  screen.print("Temp:");
  screen.setCursor(160, 120);
  screen.print(temperature, 1);
  screen.print("C");

  drawBar(
    10, 145, 220, 16,
    temperature, TEMP_MIN, TEMP_MAX,
    (temperature >= p.tempMin && temperature <= p.tempMax) ? GREEN : RED
  );

  screen.setCursor(10, 165);
  screen.print("OK ");
  screen.print(p.tempMin);
  screen.print("-");
  screen.print(p.tempMax);

  bool ok =
    moisture >= p.moistMin && moisture <= p.moistMax &&
    temperature >= p.tempMin && temperature <= p.tempMax;

  screen.setCursor(10, 200);
  screen.setTextColor(ok ? GREEN : RED);
  screen.print(ok ? "STATUS: OK" : "STATUS: NG");

  // SETTING
  screen.fillRect(40, 250, 160, 40, WHITE);
  screen.setTextColor(BLACK);
  screen.setCursor(75, 265);
  screen.print("SETTING");
}


void handleSettingPage() {

  int pos = encoder.read();
  pos = constrain(pos, 0, 5);
  delay(10);
  Serial.print("detected pos:");Serial.print(pos);Serial.print(" last pos:");Serial.println(lastPos);
  if (pos != lastPos) {
   settingIndex += (pos > lastPos) ? 1 : -1;
    // settingIndex = pos;
   // encoder.setPosition(settingIndex);
    lastPos = pos;
    screen.fillScreen(BLACK);
  }

  drawSettingPage();

  if (digitalRead(BUTTON_IN) == LOW) {
    delay(100);
    selectedType = settingIndex;
    currentPage = PAGE_CONDITION;
    screen.fillScreen(BLACK);
  }
}

void drawSettingPage() {

  screen.setTextSize(2);

  for (int i = 0; i < 6; i++) {
    int y = 40 + i * 30;
    screen.setCursor(20, y);
    screen.setTextColor(WHITE);
    screen.print(plants[i].name);
  }

  screen.fillRect(0, 38 + settingIndex * 30, 240, 28, YELLOW);
}