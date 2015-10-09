/*
 * Cryptex
 * Board: Arduino Esplora
 *
 * David Siver
 * CS 4985
 * Fall 2015
 */

#include <Esplora.h>
#include <Servo.h>

#define DEBUG 1
#define LOOP_DELAY 20
#define PASSWORD_LENGTH 8
#define WRONG_PASSWORD_TONE 262
#define READY_TONE 1000
#define TONE_DURATION 1000
#define RESET_DELAY 1500
#define SERVO_PIN 11
#define SERVO_MIN 3
#define SERVO_MAX 173
#define SERIAL_BAUD_RATE 9600

int upButtonState, downButtonState, leftButtonState, rightButtonState;
int oldUpButtonState, oldDownButtonState, oldLeftButtonState, oldRightButtonState;
int inputCount, buttonStateSum;
String password;
String userInput;
Servo servo;
int servoPosition;

void setup() {
  upButtonState = 0;
  downButtonState = 0;
  leftButtonState = 0;
  rightButtonState = 0;
  oldUpButtonState = 0;
  oldDownButtonState = 0;
  oldLeftButtonState = 0;
  oldRightButtonState = 0;
  buttonStateSum = 0;
  inputCount = 0;
  password = String(SWITCH_UP) + String(SWITCH_UP) + String(SWITCH_DOWN) +
             String(SWITCH_DOWN) + String(SWITCH_LEFT) + String(SWITCH_RIGHT) +
             String(SWITCH_LEFT) + String(SWITCH_RIGHT);
  Serial.begin(SERIAL_BAUD_RATE);
  servoPosition = SERVO_MIN;
  servo.attach(SERVO_PIN);
  servo.write(servoPosition);
}

void loop() {
  readButtons();
  if (inputCount == PASSWORD_LENGTH) {
    if (isPassword()) {
      Serial.println("Correct password");
      servo.write(SERVO_MAX);
      delay(RESET_DELAY);
      servo.write(SERVO_MIN);
      delay(RESET_DELAY);
      Esplora.tone(READY_TONE, TONE_DURATION);
    }
    else {
      Serial.println("Wrong password");
      Esplora.tone(WRONG_PASSWORD_TONE, TONE_DURATION);
    }
    inputCount = 0;
    userInput = "";
  }
  delay(LOOP_DELAY);
}

void readButtons() {
  upButtonState = Esplora.readButton(SWITCH_UP);
  downButtonState = Esplora.readButton(SWITCH_DOWN);
  leftButtonState = Esplora.readButton(SWITCH_LEFT);
  rightButtonState = Esplora.readButton(SWITCH_RIGHT);

  setUserInputByButtonPress();

  oldUpButtonState = upButtonState;
  oldDownButtonState = downButtonState;
  oldLeftButtonState = leftButtonState;
  oldRightButtonState = rightButtonState;
}

void setUserInputByButtonPress() {
  if (upButtonState != oldUpButtonState) {
    if (upButtonState == LOW) {
      setUserInput(SWITCH_UP);
    }
  }
  else if (downButtonState != oldDownButtonState) {
    if (downButtonState == LOW) {
      setUserInput(SWITCH_DOWN);
    }
  }
  else if (leftButtonState != oldLeftButtonState) {
    if (leftButtonState == LOW) {
      setUserInput(SWITCH_LEFT);
    }
  }
  else if (rightButtonState != oldRightButtonState) {
    if (rightButtonState == LOW) {
      setUserInput(SWITCH_RIGHT);
    }
  }
  else if (Esplora.readJoystickButton() == LOW) {
    Serial.println("Servo position: " + String(servo.read()));
  }
}

void setUserInput(int switchNumber) {
  inputCount++;
  Serial.println("inputCount: " + String(inputCount));
  userInput += String(switchNumber);
}

boolean isPassword() {
  printPasswordAndInput();
  return userInput.equals(password);
}

void printPasswordAndInput() {
  Serial.println("password:\t" + password);
  Serial.println("userInput:\t" + userInput);
}

