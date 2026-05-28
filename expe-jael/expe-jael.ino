// components
const int BUT = 21;
int state = 0; // variable to store button state

// pins for the RGB led
const int LEDR = A8;
const int LEDG = A9;
const int LEDB = A10;

// RGB Colors stored in arrays
// [0] -> R 
// [1] -> G
// [2] -> B
int y[3] = {255, 200, 50}; // y stands for a yellow-ish color

void setup() {
  Serial.begin(115200);
  pinMode(BUT, INPUT);
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
}

void setColor(int R, int G, int B){
  analogWrite(LEDR, R);
  analogWrite(LEDG, G);
  analogWrite(LEDB, B);
} 

void loop() {
  // update button state
  state = digitalRead(BUT);
  // Serial.println(state);

  if(state == 0){
    // when button not clicked
    setColor(0,0,0);
  }else{
    // when button clicked
    setColor(y[0], y[1], y[2]);
  }

  delay(300);
}
