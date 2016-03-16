const int COUNT = 4;
const int BUTTONS[] = {2, 3, 4, 5};
const int LIGHT[] = {8, 9, 10, 11};

void setup() {
  // put your setup code here, to run once:

  for(int i = 0; i < COUNT; ++i) {
    pinMode(BUTTONS[i], INPUT_PULLUP);
    //pinMode(BUTTONS[i], INPUT);
    pinMode(LIGHT[i], OUTPUT);
    digitalWrite(LIGHT[i], LOW);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

  for(int i = 0; i < COUNT; ++i) {
    int buttonVal = digitalRead(BUTTONS[i]);
    delay(5);
    digitalWrite(LIGHT[i], buttonVal == HIGH ? LOW : HIGH);
  }
  delay(20);
}
