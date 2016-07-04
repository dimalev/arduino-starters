const int BUTTON = 2;
const int SERIAL_BROKEN = 3;
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


const unsigned long P = 1200;
const unsigned long P16 = (1.0 / 16.0) * P;

int songsLength[4] = {0, 0, 0, 0};
byte* songs[4] = {nullptr, nullptr, nullptr, nullptr};

// every command or data MUST end with \n
// if data part is not ended with \n - it is discarded, and all data before \n is junk
class SerialProtocol {
private:
  const char terminal = '\n';
  const int chunkSize = 30;

  char mBuffer[20]; // command buffer
  int mAfterLast = 0; // byte after last in buffer

  byte* mRandomData = nullptr; // random data read
  int mRandomDataSize = -1; // size of data reading
  int mRandomDataSizeLoaded = 0; // number of bytes of data size read
  int mRandomDataLoaded = -1; // currenly loaded data

public:
  char* readNextCommand() {
    if(isBroken && !skipBroken()) return nullptr;
    while(Serial.available() > 0) {
      char newChar = (char) Serial.read();
      if(newChar == terminal) {
        mBuffer[mAfterLast] = '\0';
        mAfterLast = 0;
        return mBuffer;
      } else {
        if(mAfterLast == 19) mAfterLast = 0;
        mBuffer[mAfterLast++] = newChar;
      }
    }
    return nullptr;
  }

  byte* readRandomData() {
    if(isBroken && !skipBroken()) return nullptr;
    if(mRandomDataSizeLoaded == 0) {
      mRandomDataSize = 0;
    }
    while(mRandomDataSizeLoaded < 2) {
      if(Serial.available() > 0) {
        byte newSizeChunk = (byte) Serial.read();
        mRandomDataSize += newSizeChunk << ((1 - mRandomDataSizeLoaded) * 8);
        if(++mRandomDataSizeLoaded == 2) {
          if(mRandomDataSize < 1024) {
            mRandomData = (byte*) malloc(mRandomDataSize * sizeof(byte));
            mRandomDataLoaded = 0;
          } else {
            setBroken();
            return nullptr;
          }
        }
      } else return nullptr;
    }
    while(mRandomDataLoaded < mRandomDataSize) {
      if(Serial.available() > 0) {
        mRandomData[mRandomDataLoaded++] = (byte) Serial.read();
        if(mRandomDataLoaded % chunkSize == 0) {
          Serial.println(F("CHUNK-OK"));
        }
      } else {
        return nullptr;
      }
    }
    if(Serial.available() > 0) {
      char lastChar = (char) Serial.read();
      if(terminal == lastChar) {
        return mRandomData;
      } else {
        delete mRandomData;
        setBroken();
      }
    }
  }

  bool const getIsBroken() { return isBroken; }
  int const getLastRandomDataSize() { return mRandomDataSize; }

protected:
  bool isBroken = false;
  bool skipBroken() {
    if(Serial.available() > 0) {
      char lastChar = (char) Serial.read();
      if(terminal == lastChar) {
        digitalWrite(SERIAL_BROKEN, LOW);
        isBroken = false;
        return true;
      }
    }
    return false;
  }
  
  void setBroken() {
    digitalWrite(SERIAL_BROKEN, HIGH);
    isBroken = true;
    // we should have serial broken - read up to most recent \n
  }
};

bool isWaitingForCommand = true;
bool isWaitingForSong = false;
int songToLoad = 0;

int buttonMode = LOW;
int buttonModePrev = LOW;

SerialProtocol protocol;

void setup() {
  // put your setup code here, to run once:
  pinMode(BUTTON, INPUT);
  pinMode(SPEAKER, OUTPUT);
  pinMode(SERIAL_BROKEN, OUTPUT);
  digitalWrite(SERIAL_BROKEN, LOW);
  noTone(SPEAKER);
  Serial.begin(9600);
}

void loop() {
  if(isWaitingForCommand) {
    char* command = protocol.readNextCommand();
    if(nullptr != command) {
      if(strcmp("SONG0", command) == 0) {
        isWaitingForCommand = false;
        isWaitingForSong = true;
        songToLoad = 0;
        Serial.println("OK");
      } else Serial.println("FAILED");
    }
  }
  if(isWaitingForSong) {
    byte* newSong = protocol.readRandomData();
    if(nullptr == newSong) {
      if(protocol.getIsBroken()) {
        isWaitingForCommand = true;
        isWaitingForSong = false;
        Serial.println("FAILED");
      }
    } else {
      Serial.println("OK");
      songsLength[songToLoad] = protocol.getLastRandomDataSize();
      songs[songToLoad] = newSong;
      isWaitingForCommand = true;
      isWaitingForSong = false;
    }
  }
  // put your main code here, to run repeatedly:
  int currentSongId = -1;
  buttonMode = digitalRead(BUTTON);
  if(buttonMode != buttonModePrev) {
    if(buttonMode == HIGH) {
      currentSongId = 0;
    }
  }
  buttonModePrev = buttonMode;
  if(currentSongId >= 0 && nullptr != songs[currentSongId]) {
    for(int i = 0; i < songsLength[currentSongId]; ++i) {
      decodeNote(songs[currentSongId][2 * i], songs[currentSongId][2 * i + 1]);
      ++i;
    }
  }
  noTone(SPEAKER);
  delay(40);
}

void decodeNote(int freqind, int durind) {
  tone(SPEAKER, TONES[freqind], durind * P16);
  delay(durind * P16);
}

