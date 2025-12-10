
// variables for the timer 
const unsigned long COUNTDOWN_TIME = 300; // 5 minutes in seconds
unsigned long startTime;
unsigned long currentTime;
unsigned long elapsedTime;

void setup() {
  // Record the starting time
  startTime = millis(); 

}

void loop() {

  // Get the current time
  currentTime = millis(); 
  // Calculate elapsed time in seconds
  elapsedTime = (currentTime - startTime) / 1000;

  // before the countdown ends
  if (elapsedTime <= COUNTDOWN_TIME) {
    unsigned long remainingTime = COUNTDOWN_TIME - elapsedTime;

    // Do the maths remaining time in Minutes:Seconds format
    unsigned int minutes = remainingTime / 60;
    unsigned int seconds = remainingTime % 60;

    // display on the LCD screen
    lcd.clear();
    // display minutes
    lcd.setCursor(0,0);
    lcd.print(minutes);
    // display separator
    lcd.setCursor(0,3);
    lcd.print(":");
    // display seconds
    lcd.setCursor(0,4);
    lcd.print(seconds);
  } 

}
