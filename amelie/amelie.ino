const int BUTTON = 2;
const int SPEAKER = 5;

const int TONES[] = {
  262, // C (0)
  294, // D (1)
  330, // E (2)
  349, // F (3)
  392, // G (4)
  440, // A (5)
  494, // B (6)
  523, // C+ (7)
  587, // D+ (8)
  659  // E+ (9)
};

const int NOTES[] = {
  3830, // C (0)
  3400, // D (1)
  3038, // E (2)
  2864, // F (3)
  2550, // G (4)
  2272, // A (5)
  2028, // B (6)
  1912, // C+ (7)
  1702, // D+ (8)
  1516  // E+ (9)
};

//const int SHARPS[] = {
//  277, // C# (0)
//  311, // D# (1)
//  -1, 
//  370, // F# (2)
//  415, // G# (3)
//  466, // A# (4)
//  -1, 
//  554  // C# (5)
//};

#define DUR 1200

const unsigned long P16 = (1.0 / 16.0) * DUR;
const unsigned long P8 = (1.0 / 8.0) * DUR;
const unsigned long P4 = (1.0 / 4.0) * DUR;
const unsigned long P2 = (1.0 / 2.0) * DUR;
const unsigned long P1 = (1.0 / 1.0) * DUR;

unsigned char AMELIE[][2] = {
  {5, B00100},
  {6, B00100},
  {7, B00100},
  {6, B00100},
  {7, B00100},
  {8, B01100},
  {8, B01000},
  {8, B00010},
  {7, B00010},
  {6, B01100},
  {5, B01100},
  {8, B01100},
  {8, B00010},
  {9, B00010},
  {8, B00010},
  {7, B00010},
  {8, B00010},
  {7, B00010},

  {6, B01100}, 
  {5, B01100},
  {7, B01100},
  {7, B01000},
  {7, B00010},
  {6, B00010},
  {2, B01100},
  {3, B01000},
  {2, B00100},
  {7, B01100},
  {7, B00010},
  {8, B00010},
  {7, B00010},
  {6, B00010},
  {7, B00010},
  {6, B00010},

  {2, B01100},
   {2, B00100},
   {3, B00100},
   {2, B00100},
  {8, B00010},
  {2, B00010},
  {3, B00010},
  {2, B00010},
  {3, B00010},
  {2, B00010},
   {9, B00010},
   {2, B00010},
   {3, B00010},
   {7, B00010},
   {2, B00010},
   {3, B00010},
  {6, B00010},
  {1, B00010},
  {2, B00010},
  {1, B00010},
  {2, B00010},
  {1, B00010},
   {7, B00010},
   {0, B00010},
   {6, B00010},
   {2, B00010},
   {1, B00010},
   {0, B00010},

  {8, B00010},
  {2, B00010},
  {3, B00010},
  {2, B00010},
  {3, B00010},
  {2, B00010},
   {9, B00010},
   {2, B00010},
   {3, B00010},
   {7, B00010},
   {2, B00010},
   {3, B00010},
  {6, B00010},
  {1, B00010},
  {2, B00010},
  {1, B00010},
  {2, B00010},
  {1, B00010},
   {5, B00010},
   {0, B00010},
   {6, B00010},
   {1, B00010},
   {5, B00010},
   {0, B00010},
  {7, B00010},
  {2, B00010},
  {3, B00010},
  {2, B00010},
  {3, B00010},
  {2, B00010},
   {8, B00010},
   {2, B00010},
   {3, B00010},
   {2, B00010},
   {3, B00010},
   {1, B00010},

  {0, B00010},
  {1, B00010},
  {2, B00010},
  {1, B00010},
  {2, B00010},
  {1, B00010},
   {2, B00010},
   {1, B00010},
   {0, B00010},
   {2, B00010},
   {1, B00010},
   {0, B00010},
  {7, B00010},
  {2, B00010},
  {3, B00010},
  {2, B00010},
  {3, B00010},
  {2, B00010},
   {8, B00010},
   {2, B00010},
   {3, B00010},
   {2, B00010},
   {3, B00010},
   {1, B00010},
  {0, B00010},
  {1, B00010},
  {2, B00010},
  {1, B00010},
  {2, B00010},
  {1, B00010},
   {6, B00010},
   {1, B00010},
   {0, B00010},
   {2, B00010},
   {7, B00010},
   {0, B00010},

  {0, B00000}
};

int buttonMode = LOW;
int buttonModePrev = LOW;

void setup() {
  // put your setup code here, to run once:
  pinMode(BUTTON, INPUT);
  pinMode(SPEAKER, OUTPUT);
  noTone(SPEAKER);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonMode = digitalRead(BUTTON);
  if(buttonMode != buttonModePrev) {
    if(buttonMode == HIGH) {
      int i = 0;
      while(AMELIE[i][1] != 0) {
        decodeNote(AMELIE[i][0], AMELIE[i][1]);
        ++i;
      }
      noTone(SPEAKER);
    }
  }
  buttonModePrev = buttonMode;
  delay(40);
}

void decodeNote(int freqind, int durind) {
  long dur = 0;
  if(durind & B10000) dur += P1;
  if(durind & B01000) dur += P2;
  if(durind & B00100) dur += P4;
  if(durind & B00010) dur += P8;
  if(durind & B00001) dur += P16;
  tone(SPEAKER, TONES[freqind], dur);
  delay(dur);
}

