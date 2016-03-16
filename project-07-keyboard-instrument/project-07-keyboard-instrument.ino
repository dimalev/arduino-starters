int notes[] = {262, 294, 330, 349};

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int keyVal = analogRead(A0);
  Serial.println(keyVal);

  if(keyVal == 1023) tone(8, notes[0]);
  else if(keyVal >= 990 && keyVal <= 1010) tone(8, notes[1]);
  else if(keyVal >= 502 && keyVal <= 517) tone(8, notes[2]);
  else if(keyVal >= 6 && keyVal <= 16) tone(8, notes[3]);
  else noTone(8);
}
