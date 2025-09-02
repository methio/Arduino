// libs 
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

// joystick pins
#define HAXIS A0
#define VAXIS A1
#define BUT 13

int posX = 4;
int posY = 4;

// matrix setup
#define WIDTH 8
#define HEIGHT 8
#define LEDPIN 3
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(WIDTH, HEIGHT, LEDPIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
  NEO_GRB            + NEO_KHZ800);

uint16_t red = matrix.Color(255, 0, 0);
uint16_t color;
float col[3];
float hue = 0.0;


void setup() {
  matrix.begin();
  matrix.setBrightness(40);

  Serial.begin(9600);
  color = randomColor();

  pinMode(BUT, INPUT_PULLUP);
}

void loop() {
  // read joystick
  Serial.print("H - ");
  Serial.print(analogRead(HAXIS));
  Serial.print("\tV - ");
  Serial.println(analogRead(VAXIS));

  posX += convertJoystick(analogRead(HAXIS), 504);
  posX = constrain(posX, 0, WIDTH-1);
  posY += convertJoystick(analogRead(VAXIS), 516);
  posY = constrain(posY, 0, HEIGHT-1);

  // listen to click 
  if(digitalRead(BUT) == 0){
    Serial.println("clicked");
    color = randomColor();
  }


  matrix.clear();
  matrix.drawPixel(posX, posY, color);
  matrix.show();
  delay(200);

}

int convertJoystick(int val, int threshold){
  if(val < threshold-10){
    return -1;
  }else if(val > threshold+10){
    return +1;
  }else{
    return 0;
  }
}

uint16_t randomColor(){
  hue = random(0, 255)/255.0;
  hsv2rgb(hue, 1.0, 1.0, col);
  Serial.print("color: ");
  Serial.print(int(col[0]*255.));
  Serial.print(" - ");
  Serial.print(int(col[1]*255.));
  Serial.print(" - ");
  Serial.println(int(col[2]*255.0));


  return matrix.Color(int(col[0]*255.0), int(col[1]*255.0), int(col[2]*255.0));
}

// utils
float fract(float x) { return x - int(x); }
float mix(float a, float b, float t) { return a + (b - a) * t; }

// convert
float* hsv2rgb(float h, float s, float b, float* rgb) {
  rgb[0] = b * mix(1.0, constrain(abs(fract(h + 1.0) * 6.0 - 3.0) - 1.0, 0.0, 1.0), s);
  rgb[1] = b * mix(1.0, constrain(abs(fract(h + 0.6666666) * 6.0 - 3.0) - 1.0, 0.0, 1.0), s);
  rgb[2] = b * mix(1.0, constrain(abs(fract(h + 0.3333333) * 6.0 - 3.0) - 1.0, 0.0, 1.0), s);
  return rgb;
}