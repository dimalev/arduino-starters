const int LATCH = 2;
const int CLOCK = 4;
const int DS = 3;

void setup() {
  // put your setup code here, to run once:
  pinMode(LATCH, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(DS, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int numberToDisplay = 0; numberToDisplay < 256; numberToDisplay++) {
    // take the latchPin low so 
    // the LEDs don't change while you're sending in bits:
    digitalWrite(LATCH, LOW);
    // shift out the bits:
    shiftOut(DS, CLOCK, MSBFIRST, numberToDisplay);  

    //take the latch pin high so the LEDs will light up:
    digitalWrite(LATCH, HIGH);
    // pause before next value:
    delay(500);
  }
}
