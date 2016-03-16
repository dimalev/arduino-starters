int buttonPin = 12;
int motorOutput = 9;

void setup() {
  // put your setup code here, to run once:

  pinMode(buttonPin, INPUT);
  pinMode(motorOutput, OUTPUT);

  digitalWrite(motorOutput, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:

  bool isClick = digitalRead(buttonPin) == HIGH;
  delay(5);

  analogWrite(motorOutput, isClick ? 20 : 0);
}
