/*
 P1AM-100 State change detection switch (edge detection)

  This example shows how to detect when the P1AM-100 Toggle Swith 
  changes from off to on and on to off.

  Often, you don't need to know the state of a digital input all the time, but
  you just need to know when the input changes from one state to another.
  For example, you want to know when a button goes from OFF to ON. This is called
  state change detection, or edge detection.

  The circuit:
  - Toggle Switch on P1AM-100 "SWITCH_BUILTIN"
  - LED attached to P1AM-100 "LED_BUILTIN"

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

int newSwitchState = 0;         // current state of the switch
int oldSwitchState = 0;     // previous state of the switch

void setup() {
  Serial.begin(115200);  //initialize serial communication at 115200 bits per second
  pinMode(LED_BUILTIN,OUTPUT);  //Set our LED (Pin 32) to be an output
  pinMode(SWITCH_BUILTIN,INPUT);//Set our Switch (Pin 31) to be an input
}


void loop() {
  newSwitchState = digitalRead(SWITCH_BUILTIN);//Read the state of the switch

  // compare the buttonState to its previous state
  if (newSwitchState != oldSwitchState) {
    // if the state has changed, increment the counter
    if (newSwitchState == HIGH) {
      // if the current state is HIGH then the switch went from off to on:
      Serial.println("On");
      digitalWrite(LED_BUILTIN,newSwitchState);  //Update the LED
    } else {
      // if the current state is LOW then the switch went from on to off:
      Serial.println("Off");
      digitalWrite(LED_BUILTIN,newSwitchState);  //Update the LED
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state, for next time through the loop
  oldSwitchState = newSwitchState;

}
