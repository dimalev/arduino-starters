#include <Moisture.h>

Moisture m(0, 5);
/*
  Relays
*/
const int heat = 8;
const int light = 2; /* will come later */

/*
  Warnings
*/
const int tooHot = 9;
const int tooCold = 10;

/*
  Sensors input
*/

const int temperature = 3;
bool isHeating = false;
double temp;
bool isTooHot;
bool isTooCold;
const double tooColdLimit = 23.0;
const double lowHeatLimit = 28.0;
const double highHeatLimit = 35.0;
const double tooHotLimit = 37.0;
const double Vref = 1100.0;

const int sleepTime = 1000;

void setup() {
  Serial.begin(9600);
  m.setup();
  pinMode(heat, OUTPUT);
  pinMode(light, OUTPUT);
  pinMode(tooHot, OUTPUT);
  pinMode(tooCold, OUTPUT);
}

void loop() {
  m.run();
  checkHeating();
  checkLight();

  delay(sleepTime);
}

void checkHeating() {
  temp = double(analogRead(temperature)) * Vref / 1024.0 / 10.0;
  Serial.print(temp);
  Serial.println(" C");
  isTooHot = false;
  isTooCold = true;
  if(isHeating) {
    if(temp < highHeatLimit) {
      if(temp > tooHotLimit) isTooHot = true;
      return;
    }
    digitalWrite(heat, LOW);
    isHeating = false;
  } else {
    if(temp > lowHeatLimit) {
      if(temp < tooColdLimit) isTooCold = true;
      return;
    }
    digitalWrite(heat, HIGH);
    isHeating = true;
  }
  digitalWrite(tooCold, isTooCold ? HIGH : LOW);
  digitalWrite(tooHot, isTooHot ? HIGH : LOW);
}

void checkLight() {
  /*
    implement later.
    should allow to control light by hand, and reset on morning to handle day semantix.
  */
}

