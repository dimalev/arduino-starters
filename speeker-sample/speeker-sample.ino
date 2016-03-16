const int SPEEKER = 3;
const int TONE = A0;

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:

  int toneLevel = map(analogRead(TONE), 1, 1024, 250, 10000);

  tone(SPEEKER, toneLevel, 200);
  delay(190);
}
