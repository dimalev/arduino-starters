import processing.serial.*;
import interfascia.*;

Serial myPort;

PImage logo;

int bgColor = 0;

void setup() {
  //colorMode(HSB, 255);
  
  logo = loadImage("https://www.arduino.cc/new_home/assets/illu-arduino-UNO.png");
  //size(logo.width, logo.height);
  size(254, 181);
  
  println("Evailable serial ports:");
  String ports[] = Serial.list();
  int total = ports.length;
  for(int i = 0; i < total; ++i)
    println("==> " + ports[i]);
  
  myPort = new Serial(this, ports[0], 9600);
}

int reading = 0;
void draw() {
  if(myPort.available() > 0) {
    bgColor = myPort.read();
    println(reading + " " + bgColor);
    ++reading;
  }
  background(bgColor, 0, 0);
  image(logo, 0, 0);
}