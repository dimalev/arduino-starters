#include <Servo.h>
Servo lock;

const int yellowPin = 3;
const int greenPin = 4;
const int redPin = 5;

const int buttonPin = 2;

const int servoPin = 9;

const int piezoPin = A0;

int knockVal = 0;
int switchVal = 0;

const int quietKnock = 20;
const int loudKnock = 100;

boolean locked = false;
int numberOfKnocks = 0;

void setup() {
  // put your setup code here, to run once:
  lock.attach(servoPin);

  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(buttonPin, INPUT);

  Serial.begin(9600);

  digitalWrite(greenPin, HIGH);
  digitalWrite(yellowPin, LOW);
  digitalWrite(redPin, LOW);
  lock.write(0);
  Serial.println("The box is unlocked");
}

void loop() {
  // put your main code here, to run repeatedly:
  if(!locked) {
    switchVal = digitalRead(buttonPin);

    if(switchVal == HIGH) {
      locked = true;
      digitalWrite(greenPin, LOW);
      digitalWrite(redPin, HIGH);
      lock.write(90);
      Serial.println("The box is locked!");
      delay(1000);
    }
  }

  if(locked) {
    knockVal = analogRead(piezoPin);
    if(numberOfKnocks < 3 && knockVal > 0) {
      if(checkForKnock(knockVal)) ++numberOfKnocks;
      Serial.print(3 - numberOfKnocks);
      Serial.println(" more knocks to go");
    }

    if(numberOfKnocks >= 3) {
      locked = false;
      lock.write(0);
      delay(20);
      digitalWrite(greenPin, HIGH);
      digitalWrite(redPin, LOW);
      Serial.println("The box is unlocked!");
      numberOfKnocks = 0;
    }
  }
}

boolean checkForKnock(int value) {
  if(value > quietKnock && value < loudKnock) {
    digitalWrite(yellowPin, HIGH);
    delay(50);
    digitalWrite(yellowPin, LOW);
    Serial.print("Valid knock of value: ");
    Serial.println(value);
    return true;
  }

  Serial.print("Bad knock value: ");
  Serial.println(value);
  return false;
}

