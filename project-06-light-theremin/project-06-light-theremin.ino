int sensorPin = A0;
int thereminPin = 8;
int ledPin = 13;

int valLight = 0;
int minLight = 1023;
int maxLight = 0;

void setup() {
  // put your setup code here, to run once:

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);

  while(millis() < 5000) {
    valLight = analogRead(sensorPin);
    if(valLight > maxLight) maxLight = valLight;
    if(valLight < minLight) minLight = valLight;
  }

  digitalWrite(ledPin, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:

  valLight = analogRead(sensorPin);
  int pitch = map(valLight, minLight, maxLight, 50, 4000);
  tone(thereminPin, pitch, 20);

  delay(10);
}
