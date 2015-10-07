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
//#define PASSWORD_LENGTH 8
#define PASSWORD_LENGTH 1
#define WRONG_PASSWORD_TONE 262
#define READY_TONE 880
#define DURATION 1000

//int password[PASSWORD_LENGTH] =
//{ SWITCH_UP, SWITCH_UP, SWITCH_DOWN, SWITCH_DOWN,
//  SWITCH_LEFT, SWITCH_RIGHT, SWITCH_LEFT, SWITCH_RIGHT
//};
int password[1] = {SWITCH_UP};
int userInput[PASSWORD_LENGTH];
int inputCount;

void setup() {
  setDefaults();
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
    setDefaults();
  }
}

boolean isPassword() {
  Serial.println("In isPassword()");
  for (int i = 0; i < PASSWORD_LENGTH; i++) {
    if (password[i] != userInput[i]) {
      return false;
    }
  }
  return true;
}

void readButtons() {
  if (Esplora.readButton(SWITCH_UP) == LOW) {
    setUserInput(SWITCH_UP);
  }
  else if (Esplora.readButton(SWITCH_DOWN) == LOW) {
    setUserInput(SWITCH_DOWN);
  }
  else if (Esplora.readButton(SWITCH_LEFT) == LOW) {
    setUserInput(SWITCH_LEFT);
  }
  else if (Esplora.readButton(SWITCH_RIGHT) == LOW) {
    setUserInput(SWITCH_RIGHT);
  }
}

void setUserInput(int value) {
  userInput[inputCount] = value;
  inputCount += 1;
}

void setDefaults() {
  inputCount = 0;
  for (int i = 0; i < PASSWORD_LENGTH; i++) {
    userInput[i] = 0;
  }
}
