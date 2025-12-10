// ROTARY ENCODER DECLARATION
#include <RotaryEncoder.h>
  // RotaryEncoder by Matthias Hertel
  // lib: https://github.com/mathertel/RotaryEncoder/tree/master
// rotary pinout
#define PIN_ENCODER_A A0  // ENCA
#define PIN_ENCODER_B A1  // ENCB
                          // COMA -> GND
#define BUTTON_IN     7   // SW1
#define BUTTON_DOWN   6   // SW2
#define BUTTON_RIGHT  5   // SW3
#define BUTTON_UP     4   // SW4
#define BUTTON_LEFT   3   // SW5
                          // COMB -> GND
// rotary declaration
RotaryEncoder encoder(PIN_ENCODER_A, PIN_ENCODER_B, RotaryEncoder::LatchMode::TWO03);
// rotary variables
int curr_rotary = 0;
int last_rotary = 0;

// SCREEN DECLARATION
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>
  // GFX lib: https:adafruit.github.io/Adafruit-GFX-Library/html/class_adafruit___g_f_x.html
// screen pinout
                          // 5V   -> VIN 
                          // GND  -> GND
                          // SCK  -> 13
                          // MOSI -> 11
#define TFT_CS        10  // CS
#define TFT_RST        9  // RST
#define TFT_DC         8  // DC
// screen declaration
Adafruit_ST7789 screen = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
// screen variables
uint16_t w = screen.width()-1;   // width
uint16_t h = screen.height()-1;  // height
// colors
#define BLACK    0x0000
#define BLUE     0x001F
#define RED      0xF800
#define GREEN    0x07E0
#define CYAN     0x07FF
#define MAGENTA  0xF81F
#define YELLOW   0xFFE0 
#define WHITE    0xFFFF

void setup() {
  Serial.begin(9600);


  // intialize Screen
  screen.init(240, 320);
  screen.setRotation(0); // to rotate the screen 0: 0 | 1: 90 | 2: 180
  screen.fillScreen(BLACK);

  // welcome message on the screen
  screen.setCursor(0, 10);
  screen.setTextColor(CYAN);
  screen.setTextWrap(true);
  screen.setTextSize(5);
  screen.print("hello iefneizng");

  delay(200);    // small delay not mandatory

  // setup for encoder buttons
  pinMode(BUTTON_UP, INPUT_PULLUP);
  pinMode(BUTTON_DOWN, INPUT_PULLUP);
  pinMode(BUTTON_LEFT, INPUT_PULLUP);
  pinMode(BUTTON_RIGHT, INPUT_PULLUP);
  pinMode(BUTTON_IN, INPUT_PULLUP);

}

void loop() {

  // clean the screen


  // rotary device
  // encoder
  encoder.tick();
  curr_rotary = encoder.getPosition();
  // debug when rotate
  if (last_rotary != curr_rotary) {
  screen.fillScreen(RED);

    delay(50);
    screen.setCursor(0, 0);
    screen.print("pos:");
    screen.print(curr_rotary);
    screen.setCursor(0, 30);
    screen.print(" dir:");
    screen.println((int)(encoder.getDirection()));
    last_rotary = curr_rotary;
  }

  // //buttons
  int but_up_state = digitalRead(BUTTON_UP);
  Serial.print("up is ");Serial.println(but_up_state);
  int but_do_state = digitalRead(BUTTON_DOWN);
  Serial.print("do is ");Serial.println(but_do_state);
  int but_le_state = digitalRead(BUTTON_LEFT);
  Serial.print("le is ");Serial.println(but_le_state);
  int but_ri_state = digitalRead(BUTTON_RIGHT);
  Serial.print("ri is ");Serial.println(but_ri_state);
  int but_in_state = digitalRead(BUTTON_IN);
  Serial.print("in is ");Serial.println(but_in_state);


}
