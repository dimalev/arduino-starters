import interfascia.*;
import processing.serial.*;

GUIController c;
IFButton go, attention, ready, stop;

Serial myPort;

void setup() {
  size(600, 400);
  background(155);
  
  c = new GUIController(this);
  
  stop = new IFButton("Stop", 150, 50, 300, 60);
  attention = new IFButton("Attention", 50, 150, 200, 60);
  ready = new IFButton("Ready", 350, 150, 200, 60);
  go = new IFButton("Go", 150, 250, 300, 60);

  stop.addActionListener(this);
  attention.addActionListener(this);
  ready.addActionListener(this);
  go.addActionListener(this);

  c.add(stop);
  c.add(attention);
  c.add(ready);
  c.add(go);

  String ports[] = Serial.list();
  myPort = new Serial(this, ports[0], 9600);
}

void draw() {

}

void actionPerformed (GUIEvent e) {
  if (e.getSource() == go) {
    sendChars("go");
  } else if (e.getSource() == ready) {
    sendChars("ready");
  } else if (e.getSource() == attention) {
    sendChars("attention");
  } else if (e.getSource() == stop) {
    sendChars("stop");
  }
  if(myPort.available() > 0) {
    String data = myPort.readString();
    print(data);
  }
}

void sendChars(String chars) {
  println("Sending: " + chars + " of length " + chars.length());
  for(int i = 0; i < chars.length(); ++i) {
    myPort.write(chars.charAt(i));
  }
  //myPort.write('\n');
}