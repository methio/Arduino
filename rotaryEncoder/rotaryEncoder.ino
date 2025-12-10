// RotaryEncoder by Matthias Hertel
#include <RotaryEncoder.h>

// pins 
#define PIN_ENCODER_A A0  // ENCA
#define PIN_ENCODER_B A1  // ENCB
                          // COMA -> GND
#define BUTTON_IN     7   // SW1
#define BUTTON_DOWN   6   // SW2
#define BUTTON_RIGHT  5   // SW3
#define BUTTON_UP     4   // SW4
#define BUTTON_LEFT   3   // SW5
                          // COMB -> GND

RotaryEncoder encoder(PIN_ENCODER_A, PIN_ENCODER_B, RotaryEncoder::LatchMode::TWO03);
int last_rotary = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(BUTTON_UP, INPUT_PULLUP);
  pinMode(BUTTON_DOWN, INPUT_PULLUP);
  pinMode(BUTTON_LEFT, INPUT_PULLUP);
  pinMode(BUTTON_RIGHT, INPUT_PULLUP);
  pinMode(BUTTON_IN, INPUT_PULLUP);
}

void loop() {

  // rotary device
  // encoder
  encoder.tick();
  int curr_rotary = encoder.getPosition();
  // debug when rotate
  if (last_rotary != curr_rotary) {
    Serial.print("pos:");
    Serial.print(curr_rotary);
    Serial.print(" dir:");
    Serial.println((int)(encoder.getDirection()));
    last_rotary = curr_rotary;
  }

  //buttons
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

  delay(1000);
}
