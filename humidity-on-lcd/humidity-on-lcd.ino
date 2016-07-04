#include <LiquidCrystal.h>
#include <DHT.h>

const int MQ_PIN = A0;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
DHT dht{7, DHT11};

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("We start");

  dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  int q = analogRead(MQ_PIN);

  lcd.clear();
  lcd.setCursor(0, 0);
  if (isnan(t) || isnan(h)) {
    lcd.print("Error reading from DHT");
  } else {
    lcd.print("H: "); 
    lcd.print(int(h));
    lcd.print("%t T: "); 
    lcd.print(int(t));
    lcd.print("*C");
    lcd.setCursor(0, 1);
    lcd.print("A/Q: "); 
    lcd.print(float(q) / 1024.);
  }
  delay(5000);
}
