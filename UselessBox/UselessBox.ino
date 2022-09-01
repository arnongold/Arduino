/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 https://www.arduino.cc/en/Tutorial/LibraryExamples/Sweep
*/

#include <Servo.h>

Servo boxServo;  
Servo handServo;

int pos;
int switchPin = 3;

void setup() {
  boxServo.attach(9);  
  handServo.attach(8);

  pinMode(switchPin,INPUT);
}

void loop() {
  if (isSwitchOn())
  {
    ScenarioSwither();
  } else {
    ResetBox();
  }
  delay(200);
}
