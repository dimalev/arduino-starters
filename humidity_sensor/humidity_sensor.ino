#include <DHT.h>

DHT dht{3, DHT11};
const int BUZZER = 2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin();
  //pinMode(BUZZER, OUTPUT);
  //digitalWrite(BUZZER, LOW);
  pinMode(7, OUTPUT);
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  digitalWrite(7, HIGH);
  delay(1);
  long l = analogRead(A1);
  digitalWrite(7, LOW);

  // проверяем правильные ли данные получили
  if (isnan(t) || isnan(h)) {
    Serial.println("Error reading from DHT");
  } else {
    Serial.print("Humidity: "); 
    Serial.print(h);
    Serial.print(" %t");
    Serial.print(" Temperature: "); 
    Serial.print(t);
    Serial.print(" *C");
    Serial.print(" Water level: "); 
    Serial.print(l);
    Serial.println(" *C");
  }
  delay(5000);
}
