#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1    // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#include "eyes.h"

Servo myServo;
Servo servo1;
Servo servo2;
const int servoPin = 11; // Main servo motor connected to pin 11
const int servoPin1 = 6; // Additional servo motor connected to pin 6
const int servoPin2 = 5; // Additional servo motor connected to pin 5

unsigned long previousMillis = 0; // Store the last time servo was updated
const long interval = 120000; // Interval for mode change (2 minutes)
const long holdTime = 2000; // Time to hold the random position (2 seconds)

void setup() {
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);

  myServo.attach(servoPin);
  myServo.write(90); // Initial position (straight forward)
  servo1.attach(servoPin1);
  servo1.write(90); // Initial position (straight forward)
  servo2.attach(servoPin2);
  servo2.write(90); // Initial position (straight forward)

  Serial.begin(115200);
  Serial.println("Booting");

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3c)) { // Address 0x3C for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  display.display();
  display.clearDisplay();
  display.display();
}

unsigned char readkey(void) {
  unsigned char ret = 0;
  if (digitalRead(8) == 0) ret = 1;  // left
  if (digitalRead(9) == 0) ret += 2; // up
  if (digitalRead(10) == 0) ret += 4; // down
  if (digitalRead(11) == 0) ret += 8; // fire
  return (ret);
}

int xp = 16;
int mood = 1;
bool playMode3 = false;
unsigned long mode3StartTime = 0;
bool playMode5 = false;
unsigned long mode5StartTime = 0;

void loop() {
  unsigned long currentMillis = millis();
  int n;
  static int xd = 0;
  static int espera = 0;
  static int step = 0;
  int x1, x2;
  if (espera > 0) {
    espera--;
    delay(1);
  } else {
    x1 = xd + (xp > 16 ? (16 + 2 * (xp - 16)) : xp);
    x2 = 64 + xd + (xp < 16 ? (-16 + (xp * 2)) : xp);
    switch (step) {
      case 0:
        display.clearDisplay(); // Clear the display buffer
        if (xp < 6) {
          display.drawBitmap(x1, 8, peyes[mood][2][0], 32, 32, WHITE);
          display.drawBitmap(x2, 8, peyes[mood][1][1], 32, 32, WHITE);
        } else if (xp < 26) {
          display.drawBitmap(x1, 8, peyes[mood][0][0], 32, 32, WHITE);
          display.drawBitmap(x2, 8, peyes[mood][0][1], 32, 32, WHITE);
        } else {
          display.drawBitmap(x1, 8, peyes[mood][1][0], 32, 32, WHITE);
          display.drawBitmap(x2, 8, peyes[mood][2][1], 32, 32, WHITE);
        }
        display.display();
        espera = random(250, 1000);
        n = random(0, 7);
        if (n == 6) {
          step = 1;
        } else {
          step = 2;
        }
        break;
      case 1:
        display.clearDisplay(); // Clear the display buffer
        display.drawBitmap(x1, 8, eye0, 32, 32, WHITE);
        display.drawBitmap(x2, 8, eye0, 32, 32, WHITE);
        display.display();
        espera = 100;
        step = 0;
        break;
      case 2:
        n = random(0, 10);
        if (n < 5) xd--;
        if (n > 5) xd++;
        if (xd < -4) xd = -3;
        if (xd > 4) xd = 3;
        espera = 0;
        step = 0;
        break;
    }
  }
  n = readkey();
  if (n == 2) xp = (xp <= 0 ? 0 : xp - 1);
  if (n == 4) xp = (xp >= 32 ? 32 : xp + 1);
  if (n == 1) {
    mood = (mood >= 5 ? 0 : mood + 1);
    do {} while (readkey() != 0);
  }
  if (n != 0) {
    espera = 0;
    step = 0;
  }

  // Servo control
  if (digitalRead(9) == LOW) { // If button on pin 9 is pressed
    myServo.write(135); // Move servo to the right
    delay(500);         // Hold position for 500ms
    myServo.write(90);  // Return to center position
  }

  if (digitalRead(10) == LOW) { // If button on pin 10 is pressed
    myServo.write(45);  // Move servo to the left
    delay(500);         // Hold position for 500ms
    myServo.write(90);  // Return to center position
  }

  if (digitalRead(3) == LOW) { // If button on pin 3 is pressed
    myServo.write(45);  // Move servo to the left
    delay(500);         // Hold position for 500ms
    myServo.write(90);  // Return to center position
  }

  // Mode 3 activation and servo movement
  if (digitalRead(4) == LOW && !playMode3) { // If button on pin 4 is pressed
    mood = 3;
    playMode3 = true;
    mode3StartTime = millis();
  }

  if (playMode3) {
    unsigned long currentTime = millis();
    if (currentTime - mode3StartTime <= 5000) {
      servo1.write(75); // Move servo1 to 75 degrees (15 degrees left from center)
      servo2.write(75); // Move servo2 to 75 degrees (15 degrees left from center)
      myServo.write(75); // Move main servo to 75 degrees (15 degrees left from center)
      delay(500);
      servo1.write(105); // Move servo1 to 105 degrees (15 degrees right from center)
      servo2.write(105); // Move servo2 to 105 degrees (15 degrees right from center)
      myServo.write(105); // Move main servo to 105 degrees (15 degrees right from center)
      delay(500);
      servo1.write(90); // Return servo1 to center position
      servo2.write(90); // Return servo2 to center position
      myServo.write(90); // Return main servo to center position
    } else {
      mood = 1; // Revert to mode 1 after 5 seconds
      playMode3 = false;
    }
  }

  // Mode 5 activation and servo movement
  if (digitalRead(7) == LOW && !playMode5) { // If button on pin 7 is pressed
    mood = 2; // Change to mode 2
    playMode5 = true;
    mode5StartTime = millis();
  }

  if (playMode5) {
    unsigned long currentTime = millis();
    if (currentTime - mode5StartTime <= 5000) {
      servo2.write(0); // Move servo2 to -90 degrees (negative degrees from starting position)
      delay(500);
      servo2.write(90); // Return servo2 to center position
      // Ensure that servo on pin 11 does not move
    } else {
      mood = 1; // Revert to mode 1 after 5 seconds
      playMode5 = false;
    }
  }

  // Random movement for servo on pin 11 every 2 minutes
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis; // Save the last update time

    // Randomly move the servo on pin 11 between 15 and 20 degrees
    int randomAngle = random(15, 21); // Random angle between 15 and 20 degrees
    myServo.write(randomAngle); // Move servo to random angle
    delay(2000); // Hold position for 2 seconds

    // Randomly change mood between 2 and 4
    mood = random(2, 5); // Random mood between 2 and 4
    if (mood == 4) {
      playMode5 = true; // Activate mode 5 if mood is 4
      mode5StartTime = millis();
    } else if (mood == 2) {
      playMode3 = true; // Activate mode 3 if mood is 2
      mode3StartTime = millis();
    }
    myServo.write(90); // Return servo to starting position
  }
}
