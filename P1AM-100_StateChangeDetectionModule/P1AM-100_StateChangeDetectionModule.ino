/*
  P1AM-100 State change detection module (edge detection)

  This example shows how to detect when a P1AM input module
  changes from off to on and on to off.

  Often, you don't need to know the state of a digital input all the time, but
  you just need to know when the input changes from one state to another.
  For example, you want to know when a button goes from OFF to ON. This is called
  state change detection, or edge detection.

  The circuit:
  - P1-08SIM Input Simulator

  created  27 Sep 2005\
  modified 30 Aug 2011\
  by Tom Igoe

  modified 27 Feb 2020
  by AutomationDirect

  This example code is in the public domain.
  http://www.arduino.cc/en/Tutorial/ButtonStateChange

  Required Library which needs to be installed.
  https://github.com/facts-engineering/P1AM
*/

#include <P1AM.h> //Needed for the Pin definitions

int newInputs = 0;              // current state of input Simulator switches
bool newInputBits[8] = {};      // store the inputs into a boolean array
bool oldInputBits[8] = {};      // copy of previous states

void setup() {
  Serial.begin(115200);  //initialize serial communication at 115200 bits per second 
  while (!P1.init()){ 
    ; //Wait for Modules to Sign on   
  }
}

void loop() {
  newInputs = P1.readDiscrete(1); //Read the state of Slot 1, bits stored into a word.
  for(int i=0;i<8;i++){ //unpack from int to boolean array
    int testBit = 1 << i; //create bit mask
    newInputBits[i]=newInputs & testBit; //copy from bit of word into array
  }

  for(int i=0;i<8;i++){ //scan for differences between old and new states.
    if(newInputBits[i] != oldInputBits[i]){
      if (newInputBits[i]) {
        // if the current state is HIGH then the input went from off to on:
        Serial.print(i+1);
        Serial.println(" On");
      } else {
        // if the current state is LOW then the input went from on to off:
        Serial.print(i+1);
        Serial.println(" Off");
      }
    }
  }
  memcpy(oldInputBits,newInputBits,8); //Copy new states to old states.
}
