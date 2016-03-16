#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

byte rebbit[8] = {
  B00000,
  B10100,
  B10100,
  B11110,
  B10101,
  B10101,
  B11011,
  B01110,
};

byte smile[8] = {
  B00000,
  B00000,
  B01010,
  B00000,
  B10001,
  B01110,
  B00000,
  B00000,
};

byte sad[8] = {
  B00000,
  B00000,
  B01010,
  B00000,
  B01110,
  B10001,
  B00000,
  B00000,
};

byte peace[8] = {
  B00000,
  B01010,
  B01010,
  B01010,
  B11111,
  B01111,
  B01110,
  B00000,
};


const int switchPin = 6;
int switchState = 0;
int prevSwitchState = 0;
int reply;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  pinMode(switchPin, INPUT);

  lcd.createChar(0, rebbit);
  lcd.createChar(1, smile);
  lcd.createChar(2, sad);
  lcd.createChar(3, peace);

  lcd.setCursor(0,0);
  lcd.print("Ask the");
  lcd.setCursor(0, 1);
  lcd.print("Crystal Ball!");
  lcd.write(byte(0));
}

void loop() {
  // put your main code here, to run repeatedly:
  switchState = digitalRead(switchPin);

  if(switchState != prevSwitchState && switchState == LOW) {
    reply = random(8);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("The Ball Says:");
    lcd.setCursor(0, 1);

    switch(reply) {
      case 0: lcd.print("Yes!"); lcd.write(byte(1)); break;
      case 1: lcd.print("Most Likely"); lcd.write(byte(1)); break;
      case 2: lcd.print("Certainly"); lcd.write(byte(1)); break;
      case 3: lcd.print("Outlook good"); lcd.write(byte(3)); break;
      case 4: lcd.print("Unsure"); break;
      case 5: lcd.print("Ask again"); break;
      case 6: lcd.print("Doubtful"); break;
      case 7: lcd.print("No"); lcd.write(byte(2)); break;
    }
  }

  prevSwitchState = switchState;
}
