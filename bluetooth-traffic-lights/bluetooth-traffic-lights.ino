const int RED = 10;
const int YELLOW = 11;
const int GREEN = 12;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()) {
    String command = Serial.readString();
    if(command == "go") configLights(LOW, LOW, HIGH);
    else if(command == "attention") configLights(LOW, HIGH, LOW);
    else if(command == "stop") configLights(HIGH, LOW, LOW);
    else if(command == "ready") configLights(HIGH, HIGH, LOW);
    else {
      Serial.println("not found (" + command + ")");
      return;
    }
    Serial.println("ok");
  }
}

void configLights(int red, int yellow, int green) {
  digitalWrite(RED, red);
  digitalWrite(YELLOW, yellow);
  digitalWrite(GREEN, green);
}

