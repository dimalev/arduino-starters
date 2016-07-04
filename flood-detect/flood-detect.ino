const int BEEPER = 2; // we will power it to signal problems
const int LIMIT_IN = 13; // power limit potentiometer
const int LIMIT_PIN = A0; // we will read limit from here
const int SILENCE_BUTTON = 12; // this button will silence out gadget
const int SENSOR_IN = 3; // we power this up to init sensor
const int SENSOR_OUT = A3; // we read result here
const int SILENCE_LED = 6; // we will singal silence

const unsigned long BEEP_INTERVAL = 1000L;
unsigned long lastBeep = 0L;
unsigned long lastBeepWait = 0L;
bool isFlooded = false;
bool isBeeperOn = false;
volatile bool isSilence = false;
bool isSilenceLEDOn = false;
int sensorVal = 0;
int limitVal = 1024;
int lastSilenceVal = LOW;
unsigned long lastSensorCheck = 0L;
const unsigned long SENSOR_CHECK_INTERVAL = 5000L;
const unsigned long FLOODED_SENSOR_CHECK_INTERVAL = 500L;
const unsigned long DEBUG_INTERVAL = 2000L;
unsigned long lastDebug = 0L;

inline void initLowDigital(int pin) {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
}

void setup() {
  Serial.begin(9600);
  initLowDigital(BEEPER);
  initLowDigital(SENSOR_IN);
  initLowDigital(SILENCE_LED);
  initLowDigital(LIMIT_IN);
  pinMode(SILENCE_BUTTON, INPUT);
}

void loop() {
  updateSilence();
  // put your main code here, to run repeatedly:
  if((isFlooded && millis() - lastSensorCheck > FLOODED_SENSOR_CHECK_INTERVAL) ||
     (!isFlooded && millis() - lastSensorCheck > SENSOR_CHECK_INTERVAL)) 
  {
    updateFloodSensor();
    updateLimit();
    checkFlood();
    lastSensorCheck = millis();

    debug();
  }

  updateSignal();

  updateSilenceLED();
}

void updateSilence() {
  static int silenceVal = LOW;
  int newSilenceVal = digitalRead(SILENCE_BUTTON);
  if(silenceVal != newSilenceVal) {
    if(silenceVal == HIGH) {
      isSilence = !isSilence;
    }
    silenceVal = newSilenceVal;
  }
}

void updateSilenceLED() {
  if(isSilence) {
    if(!isSilenceLEDOn) {
      digitalWrite(SILENCE_LED, HIGH);
      isSilenceLEDOn = true;
    }
  } else {
    if(isSilenceLEDOn) {
      digitalWrite(SILENCE_LED, LOW);
      isSilenceLEDOn = false;
    }
  }
}

void debug() {
  //if(millis() - lastDebug < DEBUG_INTERVAL) return;
  Serial.print("Sensor: ");
  Serial.print(sensorVal);
  Serial.print(" Limit: ");
  Serial.print(limitVal);
  Serial.print(" isSilence: ");
  Serial.print(isSilence ? "yes" : "no");
  Serial.print(" isFlooded: ");
  Serial.print(isFlooded ? "yes" : "no");
  Serial.print(" isBeeperOn: ");
  Serial.println(isBeeperOn ? "yes" : "no");
  Serial.print("last beep: ");
  Serial.print(millis() - lastBeep);
  Serial.print(" last beep wait ");
  Serial.println(millis() - lastBeepWait);
  //lastDebug = millis();
}

void updateSignal() {
  if(isFlooded) {
    if(!isSilence) {
      if(!isBeeperOn) {
        if(millis() - lastBeepWait > BEEP_INTERVAL) {
          digitalWrite(BEEPER, HIGH);
          isBeeperOn = true;
          lastBeep = millis();
        }
      } else {
        if(millis() - lastBeep > BEEP_INTERVAL) {
          digitalWrite(BEEPER, LOW);
          isBeeperOn = false;
          lastBeepWait = millis();
        }
      }
    } else {
      if(isBeeperOn) {
        digitalWrite(BEEPER, LOW);
        isBeeperOn = false;
        lastBeepWait = millis();
      }
    }
    return;
  }
  if(isBeeperOn && millis() - lastBeep > BEEP_INTERVAL) {
    digitalWrite(BEEPER, LOW);
    isBeeperOn = false;
    lastBeepWait = millis();
  }
}

void checkFlood() {
  isFlooded = limitVal <= sensorVal;
}

void updateLimit() {
  digitalWrite(LIMIT_IN, HIGH);
  delay(1);
  limitVal = analogRead(LIMIT_PIN);
  digitalWrite(LIMIT_IN, LOW);
}

void updateFloodSensor() {
  cli();
  digitalWrite(SENSOR_IN, HIGH);
  delay(isBeeperOn ? 3 : 1);
  sensorVal = analogRead(SENSOR_OUT);
  delay(1);
  digitalWrite(SENSOR_IN, LOW);
  sei();
}

