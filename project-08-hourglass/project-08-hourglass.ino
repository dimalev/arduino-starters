int tiltSensorPin = 8;
int hourGlassPins[] = {2, 3, 4, 5, 6, 7};
int beepPin = 12;

int lastTime = 0;
int currentTime = 0;
const int interval = 2 * 1000;
int totalLEDs = 6;
bool isAllLEDLight = false;
int nextLED = 0;

int lastSensorValue = 0;
int currentSensorValue = 0;

bool isBeepOn = false;
int beepStart = 0;
int beepInterval = 2 * 1000;

void setup() {
  // put your setup code here, to run once:

  for(int i = 0; i < totalLEDs; ++i) {
    pinMode(hourGlassPins[i], OUTPUT);
    digitalWrite(hourGlassPins[i], LOW);
  }
  
  pinMode(beepPin, OUTPUT);
  noTone(beepPin);

  pinMode(tiltSensorPin, INPUT);
  lastSensorValue = digitalRead(tiltSensorPin);

  lastTime = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  if(isBeepOn) {
    delay(20);
    currentTime = millis();
    updateTone(currentTime);
    return;
  }

  currentSensorValue = digitalRead(tiltSensorPin);
  delay(5);

  if(currentSensorValue != lastSensorValue) {
    mute(true);
    resetLight();
    lastTime = millis();
  } else {
    currentTime = millis();
    if(!isAllLEDLight) {
      if(currentTime - lastTime > interval) {
        lastTime = currentTime;
        lightNextLED();
        if(isAllLEDLight) mute(false);
      }
    }
  }

  lastSensorValue = currentSensorValue;
}

void mute(bool m) {
  if(m && isBeepOn) {
    noTone(beepPin);
    isBeepOn = false;
    return;
  }
  if(!m && !isBeepOn) {
    //turnOffLight();
    tone(beepPin, 1000, beepInterval);
    isBeepOn = true;
    beepStart = millis();
  }
}

void updateTone(int curTime) {
  if(!isBeepOn) return;
  if(curTime - beepStart > beepInterval) mute(true);
}

void turnOffLight() {
  for(int i = 0; i < totalLEDs; ++i)
    digitalWrite(hourGlassPins[i], LOW);
}

void resetLight() {
  turnOffLight();
  nextLED = 0;
  isAllLEDLight = false;
}

void lightNextLED() {
  if(isAllLEDLight) return;
  digitalWrite(hourGlassPins[nextLED], HIGH);
  ++nextLED;
  if(nextLED == totalLEDs)
    isAllLEDLight = true;
}

