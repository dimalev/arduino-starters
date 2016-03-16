#include <CapacitiveSensor.h>
CapacitiveSensor capSensor = CapacitiveSensor(4, 2);

int threshold = 190;
const int LEDPin = 12;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LEDPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  long sensorValue = capSensor.capacitiveSensor(10);
  Serial.println(sensorValue);

  digitalWrite(LEDPin, sensorValue > threshold ? HIGH : LOW);

  delay(10);
}
