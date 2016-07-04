#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int HD = 8;
const int HA = A0;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  pinMode(HD, INPUT);

  lcd.print("Hello,");
  lcd.setCursor(0, 1);
  lcd.print("how are you?");
}

void loop() {
  // put your main code here, to run repeatedly:
  int din = digitalRead(HD);
  int ain = analogRead(HA);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(String(din) + " / " + String(ain));

  delay(1000);
}

