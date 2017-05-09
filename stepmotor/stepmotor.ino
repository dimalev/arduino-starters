constexpr int IN1 = 12;
constexpr int IN2 = 11;
constexpr int IN3 = 10;
constexpr int IN4 = 9;

constexpr int pins[] = {IN1, IN2, IN3, IN4};

int p = 0;

void setup() {
  // put your setup code here, to run once:
  for(int i = 0; i < 4; ++i) {
    pinMode(pins[i], OUTPUT);
  }
}

void loop() {
  for(int j = 0; j < 300000; ++j) {
  p = (p + 1) % 8;
  for(int i = 0; i < 4; ++i) {
    if(p / 2 == i || (p / 2 + p % 2) % 4 == i)
      digitalWrite(pins[i], HIGH);
    else
      digitalWrite(pins[i], LOW);
  }
    delay(1);
  }
  delay(1000);
}
