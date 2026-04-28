int MOTORPIN = 9; 
// uint16_t state = 0;

void setup() {
  pinMode(MOTORPIN, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  digitalWrite(MOTORPIN, HIGH);
  delay(500);
  digitalWrite(MOTORPIN, LOW);
  delay(1000);

}
