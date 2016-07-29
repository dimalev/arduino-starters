#include "U8glib.h"
#include <DHT.h>

const int MQ_PIN = A0;

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);  // I2C / TWI 
DHT dht{7, DHT11};

void setup() {
  // put your setup code here, to run once:
  u8g.setFont(u8g_font_unifont);
  u8g.drawStr( 0, 22, "Hello World!");

  // assign default color value
  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
    u8g.setColorIndex(255);     // white
  }
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
    u8g.setColorIndex(3);         // max intensity
  }
  else if ( u8g.getMode() == U8G_MODE_BW ) {
    u8g.setColorIndex(1);         // pixel on
  }
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255,255,255);
  }

  dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  int q = analogRead(MQ_PIN);

  if (isnan(t) || isnan(h)) {
    u8g.firstPage();  
    do {
      u8g.setFont(u8g_font_unifont);
      u8g.drawStr( 0, 22, "Error reading from DHT");
    } while( u8g.nextPage() );
  } else {
    String hstr = "H: " + String(h, 2) + "%t";
    String tstr = "T: " + String(t, 2) + "^C";
    String aq = "A/Q: " + String(float(q) / 1024., 2);
    u8g.firstPage();  
    do {
      u8g.setFont(u8g_font_unifont);
      u8g.drawStr( 0, 18, hstr.c_str()); 
      u8g.drawStr( 0, 36, tstr.c_str()); 
      u8g.drawStr( 0, 54, aq.c_str()); 
    } while( u8g.nextPage() );
  }

  delay(5000);
}
