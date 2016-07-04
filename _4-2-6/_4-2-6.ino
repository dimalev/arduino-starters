#include <EEPROM.h>ini

const int HYGROMETER = 2; // reads hygrometer digital signal
const int TEST_AMOUNT = 4; // push button to push test water amount
const int MODE = 3; // switch operational mode (work/configure)

const int MODE_INDICATOR = 7;
const int AMOUNT_INPUT = A5;

const int PUMP = 12; // where pump is plugged

inline void initLowOutput(int pin) {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
}

class PushButton {
public:
  explicit PushButton(int PIN): PIN{PIN} {};
  void init() {
    initLowOutput(PIN);
    isValid = true;
  }

  void loop() {
    isClicked = false;
    if(previousState == HIGH) {
      if(digitalRead(PIN) == LOW) {
        previousState = LOW;
        isClicked = true;
      }
    } else {
      if(digitalRead(PIN) == HIGH) previousState = HIGH;
    }
  }

  bool getIsClicked() const { return isClicked; }
  bool getIsValid() const { return isValid; }
private:
  bool isValid = false;
  const int PIN;
  int previousState;
  bool isClicked;
};

class Watering {
public:
  Watering(int PIN, int AMOUNT_INPUT): PIN{PIN}, AMOUNT_PIN{AMOUNT_INPUT} {
  }

  void init() {
    initLowOutput(PIN);
    updateAmount();
    isValid = true;
  }

  void updateAmount() {
    wateringDuration = analogRead(AMOUNT_PIN) * 20L + 1000L;
  }

  void loop() {
    if(!isOn) return;
    if(millis() - wateringStarted > wateringDuration) off();
  }

  bool isTime() const {
    //Serial.println(String("T:") + millis() + " L:" + lastWateringTime + " D:" + (millis() - lastWateringTime) + " d:" + delta);
    return millis() - lastWateringTime > delta;
  }

  void timeOn() {
    markTime();
    on();
  }

  void markTime() { lastWateringTime = millis(); }

  void on() {
    if(isOn) return;
    wateringStarted = millis();
    isOn = true;
    digitalWrite(PIN, HIGH);
  }

  void off() {
    digitalWrite(PIN, LOW);
    isOn = false;
  }

  bool getIsOn() const { return isOn; }
  unsigned long wateringDuration;
private:
  bool isValid = false;
  const int PIN;
  const int AMOUNT_PIN;
  const unsigned long delta = 60L * 1000L;//3 * 60 * 1000;
  unsigned long lastWateringTime = 0L;
  unsigned long wateringStarted;
  bool isOn = false;
};

PushButton mode{MODE};
PushButton testAmount{TEST_AMOUNT};
Watering water(PUMP, AMOUNT_INPUT);
bool isMode = false;

void setup() {
  //Serial.begin(9600);

  // THE PUMP !!!
  water.init();
  
  // indicators
  initLowOutput(MODE_INDICATOR);

  // control
  pinMode(HYGROMETER, INPUT);
  testAmount.init();
  mode.init();
}

void loop() {
  if(water.getIsOn()) {
    testAmount.loop();
    if(testAmount.getIsClicked()) water.off();
    else water.loop();
  }
  else if(isMode) processMode();
  else processWait();
}

void processMode() {
  testAmount.loop();
  if(testAmount.getIsClicked()) {
    water.updateAmount();
    water.on();
    return;
  }
  mode.loop();
  if(mode.getIsClicked()) {
    isMode = false;
    digitalWrite(MODE_INDICATOR, LOW);
  }
}

void processWait() {
  if(water.isTime()) {
    if(digitalRead(HYGROMETER)) water.timeOn();
    else water.markTime();
    return;
  }
  mode.loop();
  if(mode.getIsClicked()) {
    isMode = true;
    digitalWrite(MODE_INDICATOR, HIGH);
  }
}

