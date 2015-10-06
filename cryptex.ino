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

int password[PASSWORD_LENGTH] = 
{SWITCH_UP, SWITCH_UP, SWITCH_DOWN, SWITCH_DOWN, 
SWITCH_LEFT, SWITCH_RIGHT, SWITCH_LEFT, SWITCH_RIGHT};
int userInput[PASSWORD_LENGTH];
int inputPosition;

void setup() {
  clearUserInput();
  inputPosition = 0;
}

void loop() {
  readButtons();
}

void readButtons(){
  if(Esplora.readButton(SWITCH_UP) == LOW){
     setUserInput(SWITCH_UP);
  }
  else if (Esplora.readButton(SWITCH_DOWN) == LOW){
    setUserInput(SWITCH_DOWN);
  }
  else if (Esplora.readButton(SWITCH_LEFT) == LOW){
    setUserInput(SWITCH_LEFT);
  }
  else if (Esplora.readButton(SWITCH_RIGHT) == LOW){
    setUserInput(SWITCH_RIGHT);
  }
}

void setUserInput(int value){
  userInput[inputPosition] = value;
  inputPosition +=1;
}

void clearUserInput(){
  for(int i = 0; i < PASSWORD_LENGTH; i++){
    userInput[i] = 0;
  }
}

