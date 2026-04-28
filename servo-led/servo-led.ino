#include <Servo.h>

// where components are plugged
#define SERVOPIN 3
#define LED1 5        //PWM
#define LED2 6        //PWM

// create servo object
Servo myservo;

// servo variables
uint16_t startTime;
uint16_t duration = 2000; // 2 seconds
int startAngle = 0;
int endAngle = 180;

// leds variables
bool bri1State = false;
bool bri2State = false;
uint16_t led1Duration = 5000;
uint16_t led2Duration = 4000;

void setup() {
  // attach servo to its pin
  myservo.attach(SERVOPIN);
  // attach leds to their pins
  pinMode(bri1, OUTPUT);
  pinMode(bri2, OUTPUT);
}

void loop() {

  // servo determine step
  uint16_t currentTime = millis();
  float t = (float)(currentTime - startTime) / duration;

  // restart servo animation
  if (t >= 1.0) {
    t = 1.0;
    startTime = millis(); 
    duration = random(500, 3000);
    startAngle = random(0, 90);
    endAngle = random(90, 180);
  }

  int currentAngle = startAngle + (endAngle - startAngle) * t;
  myservo.write(currentAngle);

  // leds 
  if(led1Duration >= currentTime){
      analogWrite(bri1, random(0, 255));
      led1Duration = led1Duration + random(200, 5000);
  }
  if(led2Duration >= currentTime){
      analogWrite(bri2, random(0, 255));
      led2Duration = led2Duration + random(100, 1000);
  }
}