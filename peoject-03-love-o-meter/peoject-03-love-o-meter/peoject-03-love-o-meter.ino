const int sensorPin = A0;
const float baseTemp = 20.0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  for(int pinNumber = 2; pinNumber < 5; ++pinNumber) {
    pinMode(pinNumber, OUTPUT);
    digitalWrite(pinNumber, LOW);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorVal = analogRead(sensorPin);
  Serial.print("Sensor value: ");
  Serial.print(sensorVal);
  
  float voltage = (sensorVal / 1024.0) * 5.0;
  Serial.print(". Volts: ");
  Serial.print(voltage);

  float temperature = (voltage - .5) * 100;
  Serial.print(". degrees C: ");
  Serial.println(temperature);

  digitalWrite(2, temperature < baseTemp + 2 ? LOW : HIGH);
  digitalWrite(3, temperature < baseTemp + 4 ? LOW : HIGH);
  digitalWrite(4, temperature < baseTemp + 6 ? LOW : HIGH);

  delay(1);
}
