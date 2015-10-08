/*
 * Cryptex
 * Board: Arduino Esplora
 *
 * David Siver
 * CS 4985
 * Fall 2015
 */

#include <Esplora.h>

#define DEBUG 1
#define PASSWORD_LENGTH 8
#define WRONG_PASSWORD_TONE 262
#define READY_TONE 880
#define DURATION 1000

int upButtonState, downButtonState, leftButtonState, rightButtonState;
int oldUpButtonState, oldDownButtonState, oldLeftButtonState, oldRightButtonState;
int inputCount, buttonStateSum;
String password;
String userInput;

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
  Serial.begin(9600);
}

void loop() {
  readButtons();
  if (inputCount == PASSWORD_LENGTH) {
    if (isPassword()) {
      Serial.println("Correct password");
    }
    else {
      Serial.println("Wrong password");
    }
    inputCount = 0;
    userInput = "";
  }
  delay(20);
}

boolean isPassword() {
  printPasswordAndInput();
  return userInput.equals(password);
}

void readButtons() {
  upButtonState = Esplora.readButton(SWITCH_UP);
  downButtonState = Esplora.readButton(SWITCH_DOWN);
  leftButtonState = Esplora.readButton(SWITCH_LEFT);
  rightButtonState = Esplora.readButton(SWITCH_RIGHT);

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
  oldUpButtonState = upButtonState;
  oldDownButtonState = downButtonState;
  oldLeftButtonState = leftButtonState;
  oldRightButtonState = rightButtonState;
}

void setUserInput(int switchNumber) {
  inputCount++;
  Serial.println("inputCount: " + String(inputCount));
  userInput += String(switchNumber);
}

void printPasswordAndInput() {
  Serial.println("password:\t" + password);
  Serial.println("userInput:\t" + userInput);
}

