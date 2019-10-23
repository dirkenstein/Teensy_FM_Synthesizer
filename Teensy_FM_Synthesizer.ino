#include <ArduinoJson.h>
#include <EEPROM.h>
#include <MIDI.h>
#include <TimeLib.h>

#ifdef WIFI
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiUdp.h>
#ifdef APPLEMIDI
#include "AppleMidi.h"
#endif
#endif
#ifdef ESP8266
#include <SC16IS750.h>
#include <i2s.h>
#endif

#include <SD.h>

#include "Teensy_FM_Synthesizer.h"
#include <Wire.h>

#include "Adafruit_MCP23017.h"
//#include<PCF8574.h>
#include "algorithms.h"
//#include <SSD1306_text.h>
#include <U8g2lib.h>
//#include "rom1a.h"

#ifdef WIFI
const char* ssid = "";

const char* password = "";

const char * host = "espDX7";

#endif 

__attribute__((always_inline)) inline void updateKnobsParameters(uint8_t operatorIndex);

// Synthesizer's IO and control info.
synth_t synth;
// Notes info.
note_t notes[MAX_POLYPHONY];
// Operators info.
operator_t operators[NUM_OPERATORS];

// Pointer to the algorithms functions when using an external DAC.
void (*DACAlgorithmsHandler[NUM_ALGORITHMS])(void) = {algorithm0, algorithm1, algorithm2, algorithm3, algorithm4, algorithm5, algorithm6, algorithm7,
                                                                                 algorithm8, algorithm9, algorithm10, algorithm11, algorithm12, algorithm13, algorithm14, algorithm15,
                                                                      algorithm16, algorithm17, algorithm18, algorithm19, algorithm20, algorithm21, algorithm22, algorithm23,
                                                                                 algorithm24, algorithm25, algorithm26, algorithm27, algorithm28, algorithm29, algorithm30, algorithm31};

#ifndef ESP8266
#define AUDIO_SAMPLE_RATE_EXACT 48000.0f

#include <Audio.h>
#include <AudioStream.h>


  IntervalTimer adsrTimer;
  //elapsedMicros fill_audio_buffer;
  int xrun = 0;
  int render_time_max = 0;

class AudioSourceFMSynth : public AudioStream {
       public:
         AudioSourceFMSynth() : AudioStream(0, NULL) { };   
         void update(void) {
            elapsedMicros render_time;
            audio_block_t *lblock, *rblock;
            lblock = allocate();
            if (!lblock) return;
            rblock = allocate();
            if(!rblock) {
              release(lblock);
              return;
            }
            for (int i=0; i < AUDIO_BLOCK_SAMPLES; i++) {
                DACAlgorithmsHandler[synth.algorithm]();
                synth.outputLeft = ((synth.outputLeft * synth.volume) >> VOLUME_SHIFT);
                synth.outputRight = ((synth.outputRight * synth.volume) >> VOLUME_SHIFT);
                lblock->data[i] = synth.outputLeft;
                rblock->data[i] = synth.outputRight;
                synth.outputLeft = 0;
                synth.outputRight = 0;
            }
            transmit(lblock, 0);
            transmit(rblock, 1);
            release(lblock);
            release(rblock);
            if (render_time > render_time_max) {
              render_time_max = render_time;
            }
        };                                                           
private:
};

AudioSourceFMSynth       synth1;
AudioOutputI2S           i2s1;      
AudioConnection          patchCord1(synth1, 0, i2s1, 0);
AudioConnection          patchCord2(synth1, 1, i2s1, 1);

#endif

#ifndef ESP8266
#define ICACHE_RAM_ATTR
#endif

void ICACHE_RAM_ATTR envelopeHandler(void);

#ifdef ESP8266
 SC16IS750 i2cuart = SC16IS750(SC16IS750_PROTOCOL_I2C,SC16IS750_ADDRESS_AA);
#endif 

#define SERIALMIDI
//#define APPLEMIDI

#ifdef SERIALMIDI

#define MIDI1 MIDI
// Sets MIDI to listen to Due's RX1 pin.
//MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);
//MIDI_CREATE_DEFAULT_INSTANCE();
#ifdef ESP8266
MIDI_CREATE_INSTANCE(SC16IS750, i2cuart, MIDI);
#else
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);
#endif
#endif

#ifdef APPLEMIDI
APPLEMIDI_CREATE_INSTANCE(WiFiUDP, AppleMIDI); // see definition in AppleMidi_Defs.h
#endif

Adafruit_MCP23017 expander;
Adafruit_MCP23017 expander2;
Adafruit_MCP23017 expander3;

void eepromUpdate(void);

#define MENU_LINES 5
#define MENU_ITEMS 2

typedef struct menu_struct_t {
  char * line;
  struct menu_struct_t * subMenu;
  uint8_t subMenuLength;
  uint8_t * data;  
  uint8_t minval;
  uint8_t maxval;
  char ** textdisp;
  void (*savefunc)();
} menu_t;


menu_t midiMenu[] = {
  {"MIDI CHAN: %-2d", NULL, 0, &synth.channel, 1, 31, NULL, eepromUpdate},
};

menu_t opMenu [] = { 

  {"OP0 SRC: %-2d %s", NULL, 0, &operators[0].src_sel, 0, MAX_SOURCES-1, sourcesDisp, NULL},
  {"OP1 SRC: %-2d %s", NULL, 0, &operators[1].src_sel, 0, MAX_SOURCES-1, sourcesDisp, NULL},
  {"OP2 SRC: %-2d %s", NULL, 0, &operators[2].src_sel, 0, MAX_SOURCES-1, sourcesDisp, NULL},
  {"OP3 SRC: %-2d %s", NULL, 0, &operators[3].src_sel, 0, MAX_SOURCES-1, sourcesDisp, NULL},
  {"OP4 SRC: %-2d %s", NULL, 0, &operators[4].src_sel, 0, MAX_SOURCES-1, sourcesDisp, NULL},
  {"OP5 SRC: %-2d %s", NULL, 0, &operators[5].src_sel, 0, MAX_SOURCES-1, sourcesDisp, NULL},

};


menu_t theMenu [] = { 
  {"MIDI     ", midiMenu, 1, NULL, 0, 0},
  {"OPERATOR ", opMenu, 6, NULL, 0, 0},
};

#define MENU_DEPTH 3

menu_t * currentMenu = theMenu;
menu_t * prevMenu[MENU_DEPTH] = {NULL, NULL, NULL};
uint8_t currentMenuItems = MENU_ITEMS;
uint8_t prevMenuItems[MENU_DEPTH] = {0, 0, 0};
uint8_t prevSelectedItem[MENU_DEPTH] = {0, 0, 0};
int prevWindowStart[MENU_DEPTH] = {0, 0, 0};
int windowStart = 0;
int selectedItem = 0;
int menuStack = 0;

int NumVoices[NUM_BANKS] = {0, 0};
int NumParams = 0;
char ** patchNames[NUM_BANKS];
uint8_t *  presetAlgorithm[NUM_BANKS];
int16_t *** presetVoice[NUM_BANKS];

int NumBanks = 1;

#define DISPLAY_CS 9
#define DISPLAY_DC 15
#define DISPLAY_RESET 14
//#define DISPLAY_RESET U8X8_PIN_NONE
//SSD1306_text display;
//U8G2_SSD1306_128X64_NONAME_F_HW_I2C display(U8G2_R0, DISPLAY_RESET);

U8G2_SSD1322_NHD_256X64_F_4W_HW_SPI display(U8G2_R0, /* cs=*/ DISPLAY_CS, /* dc=*/ DISPLAY_DC, /* reset=*/ DISPLAY_RESET);
volatile int knobs[MAX_KNOBS] = {MAX_DIGITAL_VALUE/2, MAX_DIGITAL_VALUE/2, MAX_DIGITAL_VALUE/2, 0, 0, MAX_DIGITAL_VALUE/2, MAX_DIGITAL_VALUE/2, 0, MAX_DIGITAL_VALUE/2};

#define NO_ENCODER_INTERRUPTS

volatile bool gotInt = false;
volatile unsigned long inttime;


int minvals [MAX_KNOBS];
int maxvals [MAX_KNOBS];
uint8_t lastSeq[MAX_KNOBS];
volatile bool buttons[MAX_BUTTONS];
volatile bool buttonsChanged[MAX_BUTTONS];
uint32_t lastButtonChange[MAX_BUTTONS];
uint32_t buttonChange[MAX_BUTTONS];

volatile bool knobChanged[MAX_KNOBS];

const uint8_t stateMachineR [] = {2, 0, 1, 3};
const uint8_t stateMachineL [] = {1, 0, 2, 3};
uint8_t stateLPos[MAX_KNOBS];
uint8_t stateRPos[MAX_KNOBS];
uint32_t lastInt[MAX_KNOBS];

volatile bool updatingDisplay = false;
volatile bool displayNeedsUpdating = false;
volatile bool knobsNeedUpdating = false;
uint32_t lastDisplayUpdate = 0;
volatile bool isConnected = false;

char * standbyMessage = NULL;
bool gotWifi = false;

bool sdEnabled = false;

volatile bool didInit = false;

bool eepromWrite = false;

elapsedMillis loopMillis;
elapsedMillis standbyMillis;
elapsedMillis eepromMillis;

void handleencbtn() {
  
  uint8_t seq;
  //int lastPin = expander.getLastInterruptPin();
  //int lastPin2 = expander2.getLastInterruptPin();
      //Serial.printf("pins %d %d\n", lastPin, lastPin2);
#ifdef NO_ENCODER_INTERRUPTS
      inttime = millis();   
#endif
      //if (lastPin != 255) { 
      uint16_t pins1ab = expander.readGPIOAB();
      uint16_t pins2ab = expander2.readGPIOAB();
      uint16_t pins3ab = expander3.readGPIOAB();
      
      uint8_t pins0 = (pins1ab & 0x7f);
      uint8_t pins1 = (pins1ab >> 8) & 0x7f;
      uint8_t pins2 = (pins2ab & 0x7f);
      uint8_t pins3 = (pins2ab >> 8) & 0x7f;
      uint8_t pins4 = (pins3ab & 0x7f);
      uint8_t pins5 = (pins3ab >> 8) & 0x7f;

      //uint32_t allpins =  (pins3 << 21) | (pins2 << 14) | (pins1 << 7)| pins0;
          for (int x = 0; x < MAX_BUTTONS; x++) {
            //Serial.print(buttonss>>x & 1);
            int bval;
            //if (x %2 == 0) bval = (pins2>>((6 - (x/2)))) & 1;
            //else bval = (pins3>>((6- (x/2)))) & 1;
            if (x < 7) bval = (pins4>>(x)) & 1;
            else bval = (pins5>>(x-7)) & 1;
            if (bval != buttons[x]) {
              buttonsChanged[x] = true;
              buttons[x] = bval;
              lastButtonChange[x] = buttonChange[x];
              buttonChange[x] = inttime;
            }
          }
      //}
      //if (lastPin2 != 255) { 
        //Serial.print("1");

         //uint16_t pins = expander2.readGPIOAB();
             // Serial.print("2");

         //expander2.readINTCAPAB();

       for (int x = 0; x < MAX_KNOBS; x++) {
        //seq = (pins & 0x3<<(2*x)) >>(2*x); 
        if (x < 7) seq = ((pins0 & 1<<x) >>x) | (((pins1 & 1<<x) >>x) <<1);
        else seq = ((pins2 & 1<<(x-7)) >>(x-7)) | (((pins3 & 1<<(x-7)) >>(x-7)) <<1);
 
        if (seq != lastSeq[x]) {
          //Serial.printf("enc %d : seq %d\n", x, seq);
          if (stateMachineL[stateLPos[x]] == seq) {
            stateLPos[x]++;
          } else {
            stateLPos[x] = 0;
          }
         if (stateMachineR[stateRPos[x]] == seq) {
          stateRPos[x]++;
          } else {
            stateRPos[x] = 0;
          }
          bool up = false;
          bool done = false;
          if (stateLPos[x] == 4) {
            up = false;
            done = true;
          }
          if (stateRPos[x] == 4) {
            if (done) {
              //Should never happen
              stateRPos[x] = 0;
              stateLPos[x] = 0;
              done = false;
            } else {
              up = true;
              done = true;
            }
          }
          if (done) {
            stateRPos[x] = 0;
            stateLPos[x] = 0;
            uint32_t tdif = inttime - lastInt[x];
            uint16_t stp = 1;
            lastInt[x] = inttime;
            if (tdif < 250) {
              stp = (250000/tdif)/1000;
              //stp = floor(spd);
            }
            if (up) knobs[x]+= stp;
            else knobs[x] -= stp;
            if (knobs[x] > maxvals[x]) knobs[x] = maxvals[x];
            if (knobs[x] < minvals[x]) knobs[x] = minvals[x];
            knobChanged[x] = true;
            //Serial.print (x);
            //Serial.print(" : ");
            //Serial.println(knobs[x]);
        }
        lastSeq[x] = seq;
       }
      }
              //Serial.print("3");

     //}
     //expander.readINTCAPAB();
     //expander2.readINTCAPAB();
}

void ISRgateway() {
  //Serial.print("X");
  if (gotInt) return;
  gotInt = true;
  inttime = millis();
  
}

/*
 * 
 * D0 GPIO16 CS
 * D1 GPIO5 SDA
 * D2 GPIO4 ISR for 8574
 * D3 GPIO0 SCL
 * D4 GPIO2 TX1 Word select (WS) (Default) CS remap to D0
 * D5 GPIO14    CLK
 * D6 GPIO12    MISO
 * D7 GPIO13    MOSI RXS
 * D8 GPIO15 TXS Data bit-clock (SCK)
 * RXD0 GPIO3 Data bits (SD)
 * TXD0 GPIO1
 * 
 */
#ifdef ESP8266
#define ISR_PIN D2
#define SCL_PIN D3
#define SDA_PIN D1
#else 
#define ISR_PIN 22
#endif

#define SD_CS_PIN 10

void setup_encoders() 
{
    for (int x =0; x < MAX_BUTTONS; x++) {
      buttons[x] = 1;
      buttonsChanged[x] = false;
      buttonChange[x] = 0;
      lastButtonChange[x] = 0;
    }
    for (int x =0; x < MAX_KNOBS; x++) {
      if (x == 3 || x == 4 || x == 6) {
        maxvals[x] = MAX_PARAMETERS_LEVEL;
        knobs[x] = 0;
      }
      else if (x == 9) {
        knobs[x] = 0; //Go to prev bank
        maxvals[x] = NumVoices[synth.bank] +1; //Not -1 
      }
      else {
        maxvals[x] = MAX_DIGITAL_VALUE;
        knobs[x] = MAX_DIGITAL_VALUE /2;
      }
      knobChanged[x] = false;
      minvals[x] =  0;
      lastSeq[x] = 0;
      stateLPos[x] = 0;
      stateRPos[x] = 0;
    }
    expander.begin(7);
    expander2.begin(1);
    expander3.begin(0);
#ifndef NO_ENCODER_INTERRUPTS
    expander.setupInterrupts(1, 1, LOW);
#endif
    for (int x =0; x < 7; x++) {
      expander.pinMode(x, INPUT);
#ifndef NO_ENCODER_INTERRUPTS
      expander.setupInterruptPin(x, CHANGE);
#endif
    }
    for (int x =8; x < 15; x++) {
      expander.pinMode(x, INPUT);
#ifndef NO_ENCODER_INTERRUPTS
      expander.setupInterruptPin(x, CHANGE);
#endif
    }
    expander.readGPIOAB();
#ifndef NO_ENCODER_INTERRUPTS
    expander2.setupInterrupts(1, 1, LOW);
#endif
    for (int x =0; x < 7; x++) {
      expander2.pinMode(x, INPUT);
#ifndef NO_ENCODER_INTERRUPTS
      expander2.setupInterruptPin(x, CHANGE);
#endif
    }
    for (int x =8; x < 15; x++) {
      expander2.pinMode(x, INPUT);
#ifndef NO_ENCODER_INTERRUPTS
      expander2.setupInterruptPin(x, CHANGE);
#endif
    }
    expander2.readGPIOAB();
#ifndef NO_ENCODER_INTERRUPTS
    expander3.setupInterrupts(1, 1, LOW);
#endif
    for (int x =0; x < 7; x++) {
      expander3.pinMode(x, INPUT);
#ifndef NO_ENCODER_INTERRUPTS
      expander3.setupInterruptPin(x, CHANGE);
#endif
    }
    for (int x =8; x < 15; x++) {
      expander3.pinMode(x, INPUT);
#ifndef NO_ENCODER_INTERRUPTS
      expander3.setupInterruptPin(x, CHANGE);
#endif
    }
    expander3.readGPIOAB();
#ifndef NO_ENCODER_INTERRUPTS
    pinMode(ISR_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(ISR_PIN), ISRgateway, FALLING);
#endif

}

void setDefaultVoice() 
{
  NumVoices[0] = PRESET_VOICES;
  NumParams = NUM_VOICE_PARAMS;
  patchNames[0] = new char * [NumVoices[0]];
  presetAlgorithm[0] = new uint8_t [NumVoices[0]];
  presetVoice[0] = new int16_t **[NumVoices[0]];
  for (int v = 0; v < NumVoices[0]; v++) {
    patchNames[0][v] = strdup(default_patchNames[v]);
    presetAlgorithm[0][v] = default_presetAlgorithm[v]; 
    presetVoice[0][v] = new int16_t * [NUM_OPERATORS];
    for (int o = 0; o < NUM_OPERATORS; o++) {
      presetVoice[0][v][o] = new int16_t [NUM_VOICE_PARAMS];
      for (int p = 0; p < NUM_VOICE_PARAMS; p++) {
         presetVoice[0][v][o][p] = default_presetVoice[v][o][p];
      }
    }
  }
}

void createUserBank(int bank, int nvoices) 
{
  int b = bank;
  NumVoices[b] = nvoices;
  //NumParams = NUM_VOICE_PARAMS;
  patchNames[b] = new char * [NumVoices[b]];
  presetAlgorithm[b] = new uint8_t [NumVoices[b]];
  presetVoice[b] = new int16_t **[NumVoices[b]];
  for (int v = 0; v < NumVoices[b]; v++) {
    char upatchname[11];
    sprintf (upatchname, "USER%-6d", v +1);
    patchNames[b][v] = strdup(upatchname);
    presetAlgorithm[b][v] = default_presetAlgorithm[0]; 
    presetVoice[b][v] = new int16_t * [NUM_OPERATORS];
    for (int o = 0; o < NUM_OPERATORS; o++) {
      presetVoice[b][v][o] = new int16_t [NUM_VOICE_PARAMS];
      for (int p = 0; p < NUM_VOICE_PARAMS; p++) {
         presetVoice[b][v][o][p] = default_presetVoice[0][o][p];
      }
    }
  }
}
void read_presets(uint8_t bank, char * fname) 
{   
    Serial.println("Read presets");    
    File f = SD.open(fname, FILE_READ);
    if (!f) {
      Serial.println("Unable to open presets file");
      setDefaultVoice();
      return;
    }
  DynamicJsonDocument  doc(75000);

  // Parse the root object
  DeserializationError error = deserializeJson(doc, f);
    f.close();
   if (error) {
    Serial.println(F("Failed to read file, using default preset"));
    Serial.println(error.c_str());
    setDefaultVoice();
  
    return;
  }
  int nvoice = doc["NUM_PRESET_VOICES"];
  int noperators = doc["NUM_OPERATORS"];
  if (noperators != NUM_OPERATORS) {
    Serial.println("Operator mismatch");
    setDefaultVoice();
    return;  
  }
  int nparam = doc["NUM_PARAMS"];
  int16_t *** presets = new int16_t**[nvoice];
  char ** names = new char *[nvoice];
  uint8_t * algs = new uint8_t[nvoice];
  
  for (int v = 0; v < nvoice; v++) {
    presets[v] = new int16_t * [noperators];
    names[v] = strdup(doc["presetVoices"][v]["name"]);
    algs[v] = doc["presetVoices"][v]["presetAlgorithm"];
    for (int o = 0; o < noperators; o++) {
      presets[v][o] = new int16_t [nparam];
      for (int p = 0; p < nparam; p++) {
         presets[v][o][p] = doc["presetVoices"][v]["operators"][o][p];
      }
    }
  }
  NumVoices[bank] = nvoice;
  NumParams = nparam;
  patchNames[bank] = names;
  presetAlgorithm[bank] = algs;
  presetVoice[bank] = presets;
  Serial.printf("Num voices: %d\n", nvoice);
  
  Serial.println("Read presets done");
  
}

void build_Preset_file(uint8_t bank, char *fname)
{
    DynamicJsonDocument  doc(75000);
    doc["NUM_PRESET_VOICES"] = NumVoices[bank];
    doc["NUM_OPERATORS"] = NUM_OPERATORS;
    doc["NUM_PARAMS"] = NumParams;
    JsonArray voices = doc.createNestedArray("presetVoices");
    for (int v = 0; v < NumVoices[bank]; v++) {
      JsonObject voice = voices.createNestedObject();
      voice ["name"] = patchNames[bank][v];
      voice["presetAlgorithm"] = presetAlgorithm[bank][v];
      JsonArray operators = voice.createNestedArray("operators");
      for (int o = 0; o < NUM_OPERATORS; o++) {
        JsonArray op = operators.createNestedArray();
        for (int p = 0; p < NumParams; p++) {
           op.add(presetVoice[bank][v][o][p]);
        }
      }
  }
  SD.remove(fname);
  File f = SD.open(fname, FILE_WRITE);
  if (!f) {
      Serial.println("Unable to open presets file for writing");
      return;
  }
  f.seek(0);
  serializeJsonPretty(doc, f);
  f.close();

}

void deallocate_presets(uint8_t bank)
{
  for (int v = 0; v < NumVoices[bank]; v++) {
      delete patchNames[bank][v];
      for (int o = 0; o < NUM_OPERATORS; o++) {
        delete presetVoice[bank][v][o];
      }
      delete presetVoice[bank][v];     
  }
  delete presetVoice[bank];
  delete presetAlgorithm[bank];
  delete patchNames[bank];
  presetVoice[bank] = NULL;
  presetAlgorithm[bank] = NULL;
  patchNames[bank] = NULL;
}

void read_wavetable_file(uint8_t src, char * fname) 
{   
    Serial.println("Read wavetable");    
    File f = SD.open(fname, FILE_READ);
    if (!f) {
      Serial.println("Unable to open wavetable file");
      return;
    }
  DynamicJsonDocument  doc(7000);

  // Parse the root object
  DeserializationError error = deserializeJson(doc, f);
  f.close();
  if (error) {
    Serial.println(F("Failed to  read wavetable file"));
    Serial.println(error.c_str());
    return;
  }
  
  int ssiz = doc["WAVE_TABLE_SIZE"];
  if (ssiz != SINE_TABLE_SIZE) {
    Serial.println("wave table size mismatch");
    return;  
  }

  int16_t * newsrc = new int16_t[ssiz];
  
  for (int s = 0; s < ssiz; s++) {
    newsrc[s] = doc["wavetable"][s];
  }
  sources[src] = newsrc;
  Serial.println("Read source wave table done");
  
}

void build_wavetable_file(uint8_t src, char *fname)
{
    DynamicJsonDocument  doc(5000);
    doc["WAVE_TABLE_SIZE"] = SINE_TABLE_SIZE;
    JsonArray  ar = doc.createNestedArray("wavetable");
    for (int s = 0; s < SINE_TABLE_SIZE; s++) {
       ar.add(sources[src][s]);
    }
  SD.remove(fname);
  File f = SD.open(fname, FILE_WRITE);
  if (!f) {
      Serial.println("Unable to open wavetable file for writing");
      return;
  }
  f.seek(0);
  serializeJsonPretty(doc, f);
  f.close();
}

void WriteEEPROM()
{

      uint8_t cksum = 0;
      EEPROM.write(0, 1);
      EEPROM.write(1, synth.channel);
      cksum = 1 + synth.channel;
      EEPROM.write(2, cksum);
}

void WriteDefaultEEPROM()
{
      synth.channel = 1;
      WriteEEPROM();
}

void ReadEEPROM ()
{
   uint8_t ver = EEPROM.read(0);
   if (ver != 1) {
      WriteDefaultEEPROM();
   }
   synth.channel = EEPROM.read(1);
   uint8_t cksum = EEPROM.read(2);
   uint8_t newcksum = synth.channel + 1;
   if (newcksum != cksum) {
      WriteDefaultEEPROM();
   }
}



void eepromUpdate() 
{
  eepromWrite = true;
  eepromMillis = 0;
}

//------------------------------------------------------------------------------
// call back for file timestamps
void dateTime(uint16_t* date, uint16_t* time) {
 time_t current = now();
 //sprintf(timestamp, "%4d-%02d-%02d %02d:%02d:%02d  \n",year(t), month(t),day(t), hour(t),minute(t),second(t));
 //Serial.println("yy");
 //Serial.println(timestamp);
 // return date using FAT_DATE macro to format fields
 *date = FAT_DATE(year(current), month(current), day(current));

 // return time using FAT_TIME macro to format fields
 *time = FAT_TIME(hour(current), minute(current), second(current));
}
//-----------------------------------------------------------------------------

time_t getTeensy3Time()
{
  return Teensy3Clock.get();
}

void setup()
{
    // Sets the default values for some parameters.
    reset();

    // Sets the serial monitor baud rate.
#ifdef ESP8266
    Serial.begin(115200);
    Wire.begin(SDA_PIN, SCL_PIN);
#else
    Wire.begin();
#endif
    setSyncProvider(getTeensy3Time);

    //display.init();
    display.begin();
    display.clear();
    display.setFont(u8g2_font_5x7_mf);
    display.setFontMode(0);
    display.setFontPosTop();
    display.setDrawColor(0);
    display.setCursor(0, 0);

    display.printf("ESP FM");
    display.setDrawColor(1);
    display.sendBuffer();
#ifdef ESP8266
    i2cuart.begin(31250);
    if (i2cuart.ping()!=1) {
        Serial.println("i2c uart  not found");
    }
#else
    Serial1.begin(31250);
#endif
   ReadEEPROM();
    SdFile::dateTimeCallback(dateTime);
   digitalWrite(DISPLAY_CS, HIGH);
   if (!SD.begin(SD_CS_PIN)) {
      Serial.println("Can't open SD card");
      setDefaultVoice();
      NumBanks = 1;
   } else {
    sdEnabled = true;
    read_presets(0, "presets.jsn");
    if (SD.exists("user.jsn")) {
      Serial.println("readin user bank");
      read_presets(USER_BANK, "user.jsn");
    } else {
      createUserBank(USER_BANK, 5);
      Serial.println("writing new user bank");

      build_Preset_file(USER_BANK, "user.jsn");

    }
    //build_wavetable_file(0, "wav1.jsn");
    read_wavetable_file(USER_WAVTABLE_1, "wav1.jsn");
    read_wavetable_file(USER_WAVTABLE_1, "wav2.jsn");

    NumBanks = NUM_BANKS;
   }
   digitalWrite(SD_CS_PIN, HIGH);

   setup_encoders();

#ifdef WIFI
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);    
    gotWifi = false;
    int numTries = 0;
    while (1) {
      int st = WiFi.status();
      if (st == WL_CONNECTED) {
        gotWifi = true;
        break;
      }
      delay(500);
      Serial.println("No WiFi");
      numTries++;
      if (numTries>20) {
        Serial.println("Skip WiFi");
        break;
      }
    }
    if (gotWifi) {
      Serial.print(F("IP address is ")); 
      Serial.println(WiFi.localIP()); 

    }
#endif

   
    // Calls the envelope function with the defined frequency.
#ifdef ESP8266
    timer1_attachInterrupt(envelopeHandler);
    timer1_enable(TIM_DIV16, TIM_EDGE, TIM_SINGLE);
    //160Mhz div 16 = 10MHz (10 ticks per us)
    timer1_write(((160/16)*1000000)/ENVELOPE_UPDATE_FREQUENCY);
#else
    adsrTimer.begin(envelopeHandler, 1000000/ENVELOPE_UPDATE_FREQUENCY);
#endif

#ifdef ESP8266
    // Configure transmitter for 2 channels, with external clock and 32 bits per channel. Calls the defined algorithm function when ready.
    i2s_begin();
    i2s_set_rate(SAMPLE_RATE);
    //HiFi.configureTx(HIFI_AUDIO_MODE_STEREO, HIFI_CLK_MODE_USE_MCK, 32);
    i2s_set_callback(DACAlgorithmsHandler[synth.algorithm]);
    //HiFi.enableTx(true);
#else
    // start audio card
    AudioNoInterrupts();
    AudioMemory(450);
    AudioInterrupts();
    AudioProcessorUsageMaxReset();
    AudioMemoryUsageMaxReset();
#endif   

    // Sets the MIDI note and control handlers and start the capture listening to the defined channel.
#ifdef SERIALMIDI
    MIDI.setHandleNoteOn(midiNoteOnHandler);
    MIDI.setHandleNoteOff(midiNoteOffHandler);
    MIDI.setHandleControlChange(midiControlChangeHandler);
    MIDI.setHandlePitchBend (midiPitchBendHandler);
    MIDI.setHandleProgramChange(midiProgramChangeHandler);
    MIDI.setHandleControlChange(midiControlChangeHandler);
    MIDI.begin(MIDI_IN_CHANNEL); 
#endif

#ifdef APPLEMIDI
    AppleMIDI.begin("espFM"); 
    AppleMIDI.OnConnected(OnAppleMidiConnected);
    AppleMIDI.OnDisconnected(OnAppleMidiDisconnected);
    AppleMIDI.OnReceiveNoteOn(midiNoteOnHandler);
    AppleMIDI.OnReceiveNoteOff(midiNoteOffHandler);
    AppleMIDI.OnReceiveControlChange(midiControlChangeHandler);
    AppleMIDI.OnReceivePitchBend (midiPitchBendHandler);
    AppleMIDI.OnReceiveProgramChange(midiProgramChangeHandler);
    //MIDI.begin(MIDI_IN_CHANNEL);
#endif
    Serial.println("setup done");
}

// Reset parameters to the default values.
void reset()
{
    // Sets the knobs to standby and sets the operator 0 and the algorithm 0 as active. Channel is assigned the value 1 so that it becomes 0 when the sound synthesis function is called for the first time.
    synth.control = STANDBY;
    synth.selectedOperator = 0;
    synth.algorithm = 0;
    synth.presetVoice = 0;
    synth.bank = 0;
    synth.channel = 1;
    synth.playMode = false;
    synth.outputLeft = 0;
    synth.outputBufferLeft = 0;
    synth.outputRight = 0;
    synth.outputBufferRight = 0;
    synth.volume = MAX_ANALOG_VALUE;
    synth.modified = false;
    // Sets the pitch bend and the sustain pedal as off.
    synth.pitchBend.bentDown = false;
    synth.pitchBend.value = 8192;
    synth.sustainPedalOn = false;
    synth.prevVoice = 0;
    synth.prevBank = 0;
    for (uint8_t l = 0; l < NUM_KEYS; ++l)
        synth.keyMapping[l].on = false;

    // Sets the operators, their feedback, their rate scaling and their level scaling as off.
    for (uint8_t j = 0; j < NUM_OPERATORS; ++j)
    {
        operators[j].src_sel = 0; 
        operators[j].source = sources[operators[j].src_sel];
        operators[j].fixed_freq_step = 0;
        operators[j].ratio = 0;
        operators[j].level = 0;
        operators[j].feedback = 0;
        operators[j].velocity = 6;
        operators[j].rateScaling = 0;
        operators[j].levelScaling.breakPointKey = SCALING_LOWEST_KEY;
        operators[j].levelScaling.depth[0] = 0;
        operators[j].levelScaling.depth[1] = 0;
        operators[j].levelScaling.sign[0] = 1;
        operators[j].levelScaling.sign[1] = 1;
        operators[j].levelScaling.function[0] = NONE;
        operators[j].levelScaling.function[1] = NONE;

        // Sets the default ADSR envelopes values.
        for (uint8_t k = 0; k < 4; ++k)
        {
            operators[j].adsr.rate[k] = 0;
            operators[j].adsr.level[k] = MAX_ANALOG_VALUE;
        }
    }

    // Sets the notes as off.
    for (uint8_t i = 0; i < MAX_POLYPHONY; ++i)
        notes[i].on = false;

    
}

bool knobTriggered(int knob)
{
          bool res =   knobChanged[knob];
              //(synth.knobs.oldValue[knob] != knobs[knob])
             
          
          if (knobChanged[knob]) {
            Serial.printf("knob %d : %d\n", knob, knobs[knob]);
            knobChanged[knob] = false;
          }
          if(res) {
            displayNeedsUpdating = true;
          }
          //if (res) {
          //  Serial.print("Triggered ");
          //  Serial.println(knob);
          //}
          
          return res;
}


levelScalingFunction_e cycleFunctions[] = {NONE, LINEAR, LINEAR, EXPONENTIAL, EXPONENTIAL};
int8_t cycleSigns[] = {1, 1, -1, 1, -1};
uint8_t cyclePos[2] = {0, 0};
#define MAX_LEVELSCALING_CYCLE 5

int lsToCycle(int which){
  levelScalingFunction_e func = operators[synth.selectedOperator].levelScaling.function[which];
  int8_t sign = operators[synth.selectedOperator].levelScaling.sign[which];
  for (int x = 0; x < MAX_LEVELSCALING_CYCLE; x++) {
    if (cycleFunctions[x] == func && cycleSigns[x] == sign) {
      return x; 
    }
  }
  return 0;
}

void levelScalingCycle(int which)
{
      switch (operators[synth.selectedOperator].levelScaling.function[which])
      {
          case NONE:
              operators[synth.selectedOperator].levelScaling.function[which] = LINEAR;
          break;

          case LINEAR:
              if (operators[synth.selectedOperator].levelScaling.sign[which] == 1)
                  operators[synth.selectedOperator].levelScaling.sign[which] = -1;
              else
              {
                  operators[synth.selectedOperator].levelScaling.function[which] = EXPONENTIAL;
                  operators[synth.selectedOperator].levelScaling.sign[which] = 1;
              }
          break;

          case EXPONENTIAL:
              if (operators[synth.selectedOperator].levelScaling.sign[which] == 1)
                  operators[synth.selectedOperator].levelScaling.sign[which] = -1;
              else
              {
                  operators[synth.selectedOperator].levelScaling.function[which] = NONE;
                  operators[synth.selectedOperator].levelScaling.sign[which] = 1;
              }
          break;
      }

      // Updates the actives notes scaled level values.
      updateNotesScaledOperatorLevel(synth.selectedOperator);
}

void restoreBankIfSave() {
  if (synth.control == SAVE) {
          synth.bank = synth.prevBank;
          synth.presetVoice = synth.prevVoice;
          maxvals[KNOB9] = NumVoices[synth.bank] + 1;
          minvals[KNOB9] = 0;
          knobs[KNOB9] = synth.presetVoice;
   }
}


void setStandbyMessage(const char * msg)
{
  standbyMillis = 0;
  standbyMessage = msg;
  displayNeedsUpdating = true;
}

void loop()
{   
  

    //uint16_t buttonValues =  lastButtons;
    //Serial.println((int)synth.playMode);
    //Serial.println(buttonValues, HEX);
    // Sets the knobs to change the parameters values of the operator 0.
    //buttons 0-5 are for operator parameters
    for (int x = MIN_PARAM_BUTTON; x < MAX_PARAM_BUTTON + 1; x++) {
      if (buttonsChanged[x] && buttons[x] == 0) {
        Serial.printf("button %d : %d\n", x, buttons[x]);
        buttonsChanged[x] = false;        
        restoreBankIfSave();
        synth.control = PARAMETERS;
        synth.playMode = false;
        synth.selectedOperator = x - MIN_PARAM_BUTTON;
        updateKnobsParameters(synth.selectedOperator);
        knobsNeedUpdating = true;
        displayNeedsUpdating = true;
      }
    }

    for (int x = MIN_STATEFUL_BUTTON; x < MAX_STATEFUL_BUTTON +1; x++) {
      if(buttonsChanged[x]) {
        Serial.printf("s button %d : %d %d\n", x, buttons[x], buttonChange[x] - lastButtonChange[x]);
        buttonsChanged[x] = false;
        if (buttons[x] == 1) {
               bool longPress = buttonChange[x] - lastButtonChange[x] > LONG_PRESS_TIME;
               bool reallyLongPress = buttonChange[x] - lastButtonChange[x] > REALLY_LONG_PRESS_TIME;
               if (reallyLongPress) longPress = false;
               //Serial.printf("s button %d actuated", x);
               if (longPress) {
                   Serial.println("long press");
               }
               
               switch(x) {
                
                  case ALGORITHM_BUTTON:
                    // Selects the synthesizer's algorithm.
                    restoreBankIfSave();
                    if (synth.algorithm >= NUM_ALGORITHMS - 1)
                        synth.algorithm = 0;
                    else
                      ++synth.algorithm;
                    synth.modified = true;
  #ifdef ESP8266
                    i2s_set_callback(DACAlgorithmsHandler[synth.algorithm]);
  #endif
                    break;
                 case LEVEL_SCALING_LEFT_BUTTON:
                    restoreBankIfSave();
                    levelScalingCycle(0);
                     synth.modified = true;
                    break;
                 case LEVEL_SCALING_RIGHT_BUTTON:
                    restoreBankIfSave();
                    levelScalingCycle(1);
                    synth.modified = true;
                    break;
                 case ADSR_BUTTON:
                    if (synth.control == MENU) {
                      if(longPress) {
                          --menuStack;
                          if (menuStack == 0) {
                            synth.control = STANDBY;
                            knobs[KNOB9] = synth.presetVoice;
                            maxvals[KNOB9] = NumVoices[synth.bank] + 1;
                            minvals[KNOB9] = 0;
                          } else {
                            currentMenu = prevMenu[menuStack];
                            selectedItem = prevSelectedItem[menuStack];
                            currentMenuItems = prevMenuItems[menuStack];
                            windowStart = prevWindowStart[menuStack];
                            knobs[KNOB9] = selectedItem;
                            maxvals[KNOB9] = currentMenuItems-1;
                            minvals[KNOB9] = 0;
                          }
                        } else {
                          if (currentMenu[selectedItem].subMenu) {
                            prevMenu[menuStack] = currentMenu;
                            prevSelectedItem[menuStack] = selectedItem;
                            prevMenuItems[menuStack] = currentMenuItems;
                            prevWindowStart[menuStack] = windowStart;
                            ++menuStack;
                            currentMenuItems = currentMenu[selectedItem].subMenuLength;
                            currentMenu = currentMenu[selectedItem].subMenu;
                            windowStart = 0;
                            selectedItem = 0;
                            knobs[KNOB9] = 0;
                            maxvals[KNOB9] = currentMenuItems-1;
                            minvals[KNOB9] = 0;
                          } else {
                            synth.control = MENU_EDIT;
                            knobs[KNOB9] = *currentMenu[selectedItem].data;
                            maxvals[KNOB9] = currentMenu[selectedItem].maxval;
                            minvals[KNOB9] =  currentMenu[selectedItem].minval;
                          }
                      }
                     } else if (synth.control == MENU_EDIT) {
                        if (!longPress) {
                          *currentMenu[selectedItem].data = knobs[KNOB9];
                          if (currentMenu[selectedItem].savefunc) {
                            currentMenu[selectedItem].savefunc();
                          }
                        }
                        synth.control = MENU;
                        knobs[KNOB9] = 0;
                        maxvals[KNOB9] = currentMenuItems-1;
                        minvals[KNOB9] = 0;
                     } else if (synth.control == SAVE) {
                        if (longPress) {
                          restoreBankIfSave();
                          synth.control = STANDBY;
                          setStandbyMessage("Not Saved...");

                        } else if (reallyLongPress) {
                            restoreBankIfSave();
                            synth.control = STANDBY;
                            synth.modified = false;
                            loadPresetVoice(synth.bank, synth.presetVoice -1);
                            setStandbyMessage("Discarded Changes...");
                        }else {
                          savePresetVoice(synth.bank, synth.presetVoice -1);
                          if (sdEnabled) {
                            digitalWrite(DISPLAY_CS, HIGH);
                           
                            build_Preset_file(USER_BANK, "user.jsn");
                            digitalWrite(SD_CS_PIN, HIGH);
                          }
                          synth.modified = false;
                          synth.control = STANDBY;
                          setStandbyMessage("Saved to User Bank...");
                        }
                     } else {
                      if (longPress) {
                        synth.control = MENU;
                        prevMenu[menuStack] = currentMenu;
                        prevSelectedItem[menuStack] = selectedItem;
                        prevMenuItems[menuStack] = currentMenuItems;
                        prevWindowStart[menuStack] = windowStart;
                        ++menuStack;
                        knobs[KNOB9] = 0;
                        maxvals[KNOB9] = currentMenuItems-1;
                        minvals[KNOB9] = 0;
                        
                      } else {
                        // Sets the knobs to change the ADSR values of an operator (increments with every press).
                        if (synth.control != ADSR)
                        {
                            synth.control = ADSR;
                            synth.playMode = false;
                            synth.selectedOperator = 0;
                        }
                        else if (synth.selectedOperator < (NUM_OPERATORS - 1))
                            ++synth.selectedOperator;
                        else
                            synth.selectedOperator = 0;        
                        updateKnobsParameters(synth.selectedOperator);
                        knobsNeedUpdating = true;
                       }
                    }                
                    break;
                 case PRESET_BUTTON:
                    //Blat the save
                    restoreBankIfSave();
                    synth.control = STANDBY;
                    if (synth.playMode == true) {
                        if (synth.presetVoice < NumVoices[synth.bank])
                        {
                            loadPresetVoice(synth.bank, synth.presetVoice);
                            ++synth.presetVoice;
                            knobs[KNOB9] = synth.presetVoice;
                        }
                        else
                        {
                            synth.bank++;
                            if (synth.bank == NUM_BANKS) synth.bank = 0;
                            loadPresetVoice(synth.bank, 0);
                            synth.presetVoice = 1;
                            knobs[KNOB9] = synth.presetVoice;
                            maxvals[KNOB9] = NumVoices[synth.bank] + 1;
                            minvals[KNOB9] = 0;
                        }
                    }
                    // Prints parameters to the serial monitor.
                    printParameters();
                    synth.playMode = true;
                    synth.modified = false;
                    break;
                 default:
                   Serial.printf("Unk Button %d\n", x);
                   break;
              }
              displayNeedsUpdating = true;
          }
      }
    }
    // Scans the parameters values for the selected operator. Each knob value should pass by the old parameter value once before it starts to update that value (takes into consideration an EPSILON).
    if (synth.control == PARAMETERS)
    {   

        if (knobTriggered(KNOB0))
        {
            operators[synth.selectedOperator].ratio = KNOBMAP(knobs[KNOB0]);
            synth.modified = true;
        }


        if (knobTriggered(KNOB1))
        {
            operators[synth.selectedOperator].level =  KNOBMAP(knobs[KNOB1]);
            synth.modified = true;
       }

        if (knobTriggered(KNOB2))
        {
            operators[synth.selectedOperator].feedback = KNOBMAP(knobs[KNOB2]);
            synth.modified = true;
        }

      
        if (knobTriggered(KNOB3))
        {
            operators[synth.selectedOperator].velocity = knobs[KNOB3];
            synth.modified = true;
       }

        if (knobTriggered(KNOB4))
        {
            operators[synth.selectedOperator].rateScaling = knobs[KNOB4];
            synth.modified = true;
       }
        

        if (knobTriggered(KNOB5))
        {
            operators[synth.selectedOperator].levelScaling.depth[0] = KNOBMAP(knobs[KNOB5]);
             synth.modified = true;
       }


        if (knobTriggered(KNOB6))
        {
            operators[synth.selectedOperator].levelScaling.breakPointKey = knobs[KNOB6];
            synth.modified = true;
        }

        if (knobTriggered(KNOB7))
        {
            operators[synth.selectedOperator].levelScaling.depth[1] = KNOBMAP(knobs[KNOB7]);
            synth.modified = true;
       }

        
        // Updates the active notes scaled level and scaled step values for the selected operator.
        updateNotesScaledOperatorLevel(synth.selectedOperator);
        if(operators[synth.selectedOperator].fixed_freq_step) updateFixedOperatorStep(synth.selectedOperator);
        else updateNotesScaledOperatorStep(synth.selectedOperator);   
    }
    // Scans the ADSR rate and level values for the selected operator. Each knob value should pass by the old parameter value once before it starts to update that value (takes into consideration an EPSILON).
    else if (synth.control == ADSR)
    {
        if (knobTriggered(KNOB0)) 
        {
            operators[synth.selectedOperator].adsr.level[3] = KNOBMAP(knobs[KNOB0]);
            synth.modified = true;
        }

        if (knobTriggered(KNOB1)) 
        {
            operators[synth.selectedOperator].adsr.rate[0] =  REVKNOBMAP(knobs[KNOB1]);
            synth.modified = true;
        }

        if (knobTriggered(KNOB2))
        {
            operators[synth.selectedOperator].adsr.level[0] = KNOBMAP(knobs[KNOB2]);
            synth.modified = true;
        }


        if (knobTriggered(KNOB3)) 
        {
            operators[synth.selectedOperator].adsr.rate[1] = REVKNOBMAP(knobs[KNOB3]);
            synth.modified = true;
        }

        if (knobTriggered(KNOB4)) 
        {
            operators[synth.selectedOperator].adsr.level[1] = KNOBMAP(knobs[KNOB4]);
            synth.modified = true;
        }


        if (knobTriggered(KNOB5)) 
        {
            operators[synth.selectedOperator].adsr.rate[2] = REVKNOBMAP(knobs[KNOB5]);
            synth.modified = true;
        }


        if (knobTriggered(KNOB6)) 
        {
            operators[synth.selectedOperator].adsr.level[2] = KNOBMAP(knobs[KNOB6]);
             synth.modified = true;
       }

        if (knobTriggered(KNOB7)) 
        {
            operators[synth.selectedOperator].adsr.rate[3] =  REVKNOBMAP(knobs[KNOB7]);
            synth.modified = true;
        }
    }
    // Scans for the overall volume.
    if (knobTriggered(KNOB8))
    {
          synth.volume = KNOBMAP(knobs[KNOB8]);
    }
    if (knobTriggered(KNOB9)) 
    {  
           if (synth.control == MENU) {
              selectedItem = knobs[KNOB9];
              if (selectedItem <  windowStart) {
                windowStart = selectedItem;
              } else if ((selectedItem -windowStart) + 1> MENU_LINES) {
                windowStart = selectedItem+1 -MENU_LINES;
              }
              displayNeedsUpdating=true;
           } else if (synth.control == MENU_EDIT) {
              //Do nothing
           } else if (synth.modified  && synth.control != SAVE && NumBanks > 1) {
          
             synth.prevBank = synth.bank;
             synth.prevVoice = synth.presetVoice; 
             synth.control = SAVE;
             synth.bank = USER_BANK;
             if (synth.presetVoice > NumVoices[synth.bank]) {
              synth.presetVoice = 1; 
             }
             knobs[KNOB9] = synth.presetVoice;
             maxvals[KNOB9] = NumVoices[synth.bank] +1;
             minvals[KNOB9] = 0;
           } else {
             if (synth.control != SAVE) synth.control = STANDBY;
           
             if (knobs[KNOB9] == 0) {
               if (synth.control != SAVE ) {
                if (synth.bank == 0) synth.bank = NumBanks-1;
                else synth.bank--;
               }
               synth.presetVoice = NumVoices[synth.bank];
               knobs[KNOB9] = NumVoices[synth.bank];
               maxvals[KNOB9] = NumVoices[synth.bank] +1;
               minvals[KNOB9] = 0;
             } else if (knobs[KNOB9] == NumVoices[synth.bank] +1) {
               if (synth.control != SAVE) {
                 if (synth.bank == NumBanks -1) synth.bank = 0;
                 else synth.bank++;
               }
               synth.presetVoice = 1;
               knobs[KNOB9] = 1;
               maxvals[KNOB9] = NumVoices[synth.bank] +1;
               minvals[KNOB9] = 0;

             } else {
               synth.presetVoice = knobs[KNOB9];
             }
             if (synth.control != SAVE) {
              loadPresetVoice(synth.bank, synth.presetVoice -1);
             
              synth.playMode = true;
              printParameters();
            }
           }
    }
    // Scans for MIDI note on/off messages.
    //MIDI.read();
    if (!didInit) {

      synth.playMode = true;
      loadPresetVoice(synth.bank, 0);
      synth.presetVoice = 1;
      printParameters();

      didInit = true;
    }
    MIDI1.read();


    if (displayNeedsUpdating && millis() - lastDisplayUpdate > 100) {
      updateDisplay();
      lastDisplayUpdate = millis();
    }
#ifndef NO_ENCODER_INTERRUPTS
    if(gotInt) {
      handleencbtn();
      gotInt =false;
    }

    if(digitalRead(ISR_PIN) == LOW) {
       Serial.println("Stuckint");
       expander.readINTCAPAB();
       expander2.readINTCAPAB();
       expander3.readINTCAPAB();
       handleencbtn();
       
       //handleencbtn();
    }
#else
    handleencbtn();
#endif
    if (knobsNeedUpdating) {
       updateRemoteKnobs();
       knobsNeedUpdating = false;
    }
    if (loopMillis > 2000) {
      loopMillis =0;
      show_audio_load();
    }
    if (standbyMessage && standbyMillis > 5000) {
      standbyMessage = NULL;
      displayNeedsUpdating = true;
    }
    if (eepromWrite && eepromMillis > 50) {
      WriteEEPROM();
      eepromWrite = false;
    }
}


void OnMIDI1Connected(uint32_t ssrc, char* name) {
  isConnected  = true;
  Serial.print(F("Connected to session "));
  Serial.println(name);
}

// -----------------------------------------------------------------------------
// rtpMIDI session. Device disconnected
// -----------------------------------------------------------------------------
void OnAppleMidiDisconnected(uint32_t ssrc) {
  isConnected  = false;
  Serial.println(F("Disconnected"));
}


void midiNoteOnHandler(byte channel, byte note, byte velocity)
{
    Serial.print("REceive cahnnel ");
    Serial.print(channel);
    Serial.print(" note ");
    Serial.println(note);
    
    // Check if the note is in the valid range.
    if (note >= LOWEST_KEY && note <= HIGHEST_KEY)
    {
        uint8_t keyIndex = note - LOWEST_KEY;
        uint8_t index = MAX_POLYPHONY;

        if (synth.keyMapping[keyIndex].on == false)
        {
            // If the maximum polyphony has not been reached, turns the note on.
            for (uint8_t i = 0; i < MAX_POLYPHONY; ++i)
                if (notes[i].on == false)
                {
                    index = i;

                    break;
                }
        }
        else
        {
            // Case where the note is already being played (release part of the ADSR envelope or sustain pedal).
            index = synth.keyMapping[keyIndex].index;

            notes[index].on = false;
        }

        if (index != MAX_POLYPHONY)
        {
            // Stores the key index and resets the feedback value.
            notes[index].keyIndex = keyIndex;
            notes[index].feedback = 0;

            // Assigns the sustain pedal value and set the note as not released.
            notes[index].sustained = synth.sustainPedalOn;
            notes[index].released = false;

            setEnvelopesParameters(index, keyIndex);

            for (uint8_t j = 0; j < NUM_OPERATORS; ++j)
            {
                // Stores the note velocity.
                notes[index].velocity[j] = velocityCurve[operators[j].velocity][velocity];

                // Resets the step accumulator value.
                notes[index].stepAccumulator[j] = 0;

                // Sets the note scaled level and scaled step values for this operator.
                setNoteScaledOperatorLevel(index, j);
                if(operators[j].fixed_freq_step) setFixedOperatorStep(index, j);
                else setNoteScaledOperatorStep(index, j);
            }

            // Stores the note index and set it as on (key mapper).
            synth.keyMapping[keyIndex].on = true;
            synth.keyMapping[keyIndex].index = index;

            // Set note as on.
            notes[index].on = true;
        }
    }
}

void midiNoteOffHandler(byte channel, byte note, byte velocity)
{
    if (note >= LOWEST_KEY && note <= HIGHEST_KEY)
    {
        uint8_t keyIndex = note - LOWEST_KEY;

        if (synth.keyMapping[keyIndex].on == true)
        {
            uint8_t index = synth.keyMapping[keyIndex].index;

            notes[index].released = true;

            // Checks if the sustain pedal is pressed.
            if (notes[index].sustained == false)
                // Starts the release part of the ADSR envelope.
                for (uint8_t j = 0; j < NUM_OPERATORS; ++j)
                {
                    notes[index].adsrStatus[j].parameter = RRELEASE;

                    if (notes[index].adsrStatus[j].releaseReady == false)
                        updateEnvelopeRelease(index, keyIndex, j);
                }
        }
    }
}

uint16_t last14BitCC[128];

void midiControlChangeHandler(byte channel, byte number, byte value)
{
    uint8_t newop, newalg, newsrc, newbank, lsPos, newLsPos;
    int8_t knob;
    uint16_t newvalue;
    // In case the message was from the sustain pedal.
    switch(number) {
        case SUSTAIN_PEDAL: 
        // In case it is now off.
          if (value == false)
          {
              synth.sustainPedalOn = false;
  
              for (uint8_t i = 0; i < MAX_POLYPHONY; ++i)
                  if (notes[i].sustained == true)
                  {
                      notes[i].sustained = false;
  
                      if (notes[i].released == true)
                          // Starts the release part of the ADSR envelope.
                          for (uint8_t j = 0; j < NUM_OPERATORS; ++j)
                          {
                              notes[i].adsrStatus[j].parameter = RRELEASE;
  
                              if (notes[i].adsrStatus[j].releaseReady == false)
                                  updateEnvelopeRelease(i, notes[i].keyIndex, j);
                          }
                  }
          }
          // In case it is now on.
          else
          {
              synth.sustainPedalOn = true;
  
              for (uint8_t i = 0; i < MAX_POLYPHONY; ++i)
                  if (notes[i].released == false)
                      notes[i].sustained = true;
          }
          break;
        case VOLUME_CC_MSB:
          last14BitCC[number]  = ((last14BitCC[number] & 0x7f) | ((value&0x7f)<<7));
          synth.volume = map(last14BitCC[number], 0, MAX_MIDI_VALUE_14, 0, MAX_ANALOG_VALUE);
          knobs[KNOB8] = map(synth.volume, 0, MAX_ANALOG_VALUE, 0, MAX_DIGITAL_VALUE);
          //Serial.printf("Volume = %d\n", last14BitCC[number]); 
          displayNeedsUpdating = true;
          break;
        case VOLUME_CC_LSB:
          last14BitCC[number-CC_LSB_MSB_OFFSET]  = (last14BitCC[number-CC_LSB_MSB_OFFSET] & 0xff80) | (value & 0x7f);
          synth.volume = map(last14BitCC[number-CC_LSB_MSB_OFFSET], 0, MAX_MIDI_VALUE_14, 0, MAX_ANALOG_VALUE);
          knobs[KNOB8] = map(synth.volume, 0, MAX_ANALOG_VALUE, 0, MAX_DIGITAL_VALUE);
          //Serial.printf("VolumeLSB = %d\n", last14BitCC[number-CC_LSB_MSB_OFFSET]); 
          displayNeedsUpdating = true;

          break;
        case SOUND_CC_1_LSB: //algorithm select
          //newalg  = map(value, 0, MAX_MIDI_VALUE_7, 0,NUM_ALGORITHMS -1);
          newalg = value;
          if (newalg > NUM_ALGORITHMS -1) newalg = NUM_ALGORITHMS -1;
          if (newalg != synth.algorithm) {
            synth.algorithm = newalg;
            //knobs[KNOB9] = newalg;
#ifdef ESP8266
            i2s_set_callback(DACAlgorithmsHandler[synth.algorithm]);
#endif
            displayNeedsUpdating = true;
            knobsNeedUpdating = true;

          }
          break;


        case BANKSEL_CC_MSB: //bank select
          newbank = value;
          if (newbank > NumBanks -1) newbank = NumBanks -1;
            if (newbank != synth.bank) {
              synth.bank = newbank;
              //Serial.println(program);
              if(synth.presetVoice > NumVoices[synth.bank]) synth.presetVoice = 1;
              loadPresetVoice(synth.bank, synth.presetVoice -1);
              synth.playMode = true;
              synth.control = STANDBY;
              printParameters();
              displayNeedsUpdating = true;
              knobsNeedUpdating = true;
            }
          break;
        case GP1_CC_MSB: //operator select
          newop = value;
          if (newop > NUM_OPERATORS -1) newop = NUM_OPERATORS -1;
          if (newop != synth.selectedOperator) {
            synth.playMode = false;
            if (synth.control != ADSR)
              synth.control = PARAMETERS;
            synth.selectedOperator = newop;
            updateKnobsParameters(synth.selectedOperator);
            displayNeedsUpdating = true;
            knobsNeedUpdating = true;
          }
          break;
        case GP2_CC_MSB: //Left level scaling
          lsPos = lsToCycle(0);
          //newLsPos = map(value,0, MAX_MIDI_VALUE_7, 0,MAX_LEVELSCALING_CYCLE -1) ;
          newLsPos = value;
          if (newLsPos > MAX_LEVELSCALING_CYCLE -1) newLsPos = MAX_LEVELSCALING_CYCLE -1; 
          if(lsPos != newLsPos) {
            operators[synth.selectedOperator].levelScaling.function[0] = cycleFunctions[newLsPos];
            operators[synth.selectedOperator].levelScaling.sign[0] =  cycleSigns[newLsPos];
            updateNotesScaledOperatorLevel(synth.selectedOperator);
            displayNeedsUpdating = true;
          }
          break;
        case GP3_CC_MSB: //Right level scaling
          lsPos = lsToCycle(1);
          //newLsPos = map(value,0, MAX_MIDI_VALUE_7, 0,MAX_LEVELSCALING_CYCLE -1) ;
          newLsPos = value;
          if (newLsPos > MAX_LEVELSCALING_CYCLE -1) newLsPos = MAX_LEVELSCALING_CYCLE -1; 
          if(lsPos != newLsPos) {
            operators[synth.selectedOperator].levelScaling.function[1] = cycleFunctions[newLsPos];
            operators[synth.selectedOperator].levelScaling.sign[1] =  cycleSigns[newLsPos];
            updateNotesScaledOperatorLevel(synth.selectedOperator);
            displayNeedsUpdating = true;
          }
          break;
        case GP4_CC_MSB: //function source (sine/tri/saw etc)
          //newop = map(value,0, MAX_MIDI_VALUE_7, 0,NUM_OPERATORS -1) ;
          newsrc = value;
          if (newsrc > MAX_SOURCES -1) newsrc = MAX_SOURCES -1;
          if (newsrc != operators[synth.selectedOperator].src_sel) {
            const int16_t * src = sources[newsrc];
            if (!src) newsrc = 0;
            operators[synth.selectedOperator].src_sel = newsrc;
            operators[synth.selectedOperator].source = src; 
            displayNeedsUpdating = true;
          }
          break;
        case GP5_CC_MSB: //Mode select
          if (value <=63) {
            synth.control = PARAMETERS;
            synth.playMode = false;
            //synth.selectedOperator = 0;
          } else {
            synth.control = ADSR;
            synth.playMode = false;
            //synth.selectedOperator = 0;
          }
          knobsNeedUpdating = true; 
          displayNeedsUpdating = true;
        default:
          knob = -1;
          if (number >= U1_CC_MSB && number <= U8_CC_MSB) {
            last14BitCC[number]  = ((last14BitCC[number] & 0x7f) | ((value&0x7f)<<7));
            knob = number - U1_CC_MSB;
            newvalue = last14BitCC[number];
          } else if (number >= U1_CC_LSB && number <= U8_CC_LSB) {
            last14BitCC[number - CC_LSB_MSB_OFFSET]  = (last14BitCC[number-CC_LSB_MSB_OFFSET] & 0xff80) | (value & 0x7f);
            knob = number - U1_CC_LSB;
            newvalue = last14BitCC[number- CC_LSB_MSB_OFFSET];

          } 
          int operatorIndex = synth.selectedOperator;
          if (knob >= 0) {
            //Serial.print("knob ");
            //Serial.println(knob);
            uint16_t oldvalue = knobs[knob];

            if (synth.control == PARAMETERS) { 
              if (knob == KNOB3 || knob == KNOB4) {
                //synth.knobs.oldValue[knob] = knobs[knob];
                maxvals[knob] = MAX_PARAMETERS_LEVEL;
                minvals[knob] = 0;
              } else if(knob == KNOB6) {
                 //synth.knobs.oldValue[knob] = knobs[knob];
                 maxvals[knob] = SCALING_HIGHEST_KEY;
                 minvals[knob] = SCALING_LOWEST_KEY;
              } else {
                //synth.knobs.oldValue[knob] = KNOBMAP(knobs[knob]);
                maxvals[knob] = MAX_DIGITAL_VALUE;
                minvals[knob] = 0;
              }
              if (newvalue > MAX_ANALOG_VALUE) {
                newvalue = MAX_ANALOG_VALUE;
              }
              switch(knob) {
                case KNOB0:
                  operators[operatorIndex].ratio = newvalue;
                  knobs[knob] = PARAMMAP(operators[operatorIndex].ratio);
                  break;
                case KNOB1:
                  operators[operatorIndex].level = newvalue;
                  knobs[knob] = PARAMMAP(operators[operatorIndex].level);
                  break;
                case KNOB2:
                  operators[operatorIndex].feedback =  newvalue;
                  knobs[knob] = PARAMMAP(operators[operatorIndex].feedback);
                  break;
                case KNOB3:
                  if (newvalue > MAX_PARAMETERS_LEVEL) {
                      newvalue = MAX_PARAMETERS_LEVEL;
                  }  
                  operators[operatorIndex].velocity = newvalue;
                  knobs[knob] = operators[operatorIndex].velocity;
                  break;
                case KNOB4:
                  if (newvalue > MAX_PARAMETERS_LEVEL) {
                      newvalue = MAX_PARAMETERS_LEVEL;
                  }   
                  operators[operatorIndex].rateScaling = newvalue;
                  knobs[knob] = operators[operatorIndex].rateScaling;
                  break;
                case KNOB5:
                  operators[operatorIndex].levelScaling.depth[0] = newvalue;
                  knobs[knob] = PARAMMAP(operators[operatorIndex].levelScaling.depth[0]);
                  break;
                case KNOB6:
                  if (newvalue > SCALING_HIGHEST_KEY) {
                      newvalue = SCALING_HIGHEST_KEY;
                  } 
                  if (newvalue < SCALING_LOWEST_KEY) {
                      newvalue = SCALING_LOWEST_KEY;
                  }
                  operators[operatorIndex].levelScaling.breakPointKey = newvalue; 
                  knobs[knob] = operators[operatorIndex].levelScaling.breakPointKey;
                  break;
                case KNOB7:
                  operators[operatorIndex].levelScaling.depth[1] = newvalue; 
                  knobs[knob] = PARAMMAP(operators[operatorIndex].levelScaling.depth[1]);
                  break;
              }
             } else if (synth.control == ADSR) {
                //if(knob % 2 == 0) synth.knobs.oldValue[knob] = KNOBMAP(knobs[knob]);
                //else synth.knobs.oldValue[knob] = REVKNOBMAP(knobs[knob]);
                maxvals[knob] = MAX_DIGITAL_VALUE;
                minvals[knob] = 0;
                if (newvalue > MAX_ANALOG_VALUE) {
                  newvalue = MAX_ANALOG_VALUE;
                }
                switch(knob) {
                  case KNOB0:
                    operators[operatorIndex].adsr.level[3] = newvalue;
                    knobs[knob] = PARAMMAP(operators[operatorIndex].adsr.level[3]);
                    break;
                  case KNOB1:
                    operators[operatorIndex].adsr.rate[0] = map(newvalue, 0, MAX_ANALOG_VALUE, MAX_ANALOG_VALUE, 0);
                    knobs[knob] = REVPARAMMAP(operators[operatorIndex].adsr.rate[0]);
                    break;
                  case KNOB2:
                    operators[operatorIndex].adsr.level[0] = newvalue;
                    knobs[knob] = PARAMMAP( operators[operatorIndex].adsr.level[0]);
                    break;
                  case KNOB3:
                    operators[operatorIndex].adsr.rate[1] =  map(newvalue, 0, MAX_ANALOG_VALUE, MAX_ANALOG_VALUE, 0);
                    knobs[knob] = REVPARAMMAP(operators[operatorIndex].adsr.rate[1]);
                    break;
                  case KNOB4:
                    operators[operatorIndex].adsr.level[1] = newvalue;
                    knobs[knob] = PARAMMAP( operators[operatorIndex].adsr.level[1]);
                    break;
                  case KNOB5:
                    operators[operatorIndex].adsr.rate[2] =  map(newvalue, 0, MAX_ANALOG_VALUE, MAX_ANALOG_VALUE, 0);
                    knobs[knob] = REVPARAMMAP(operators[operatorIndex].adsr.rate[2]);
                    break;
                  case KNOB6:
                    operators[operatorIndex].adsr.level[2] = newvalue;
                    knobs[knob] = PARAMMAP(operators[operatorIndex].adsr.level[2]);
                    break;
                  case KNOB7:
                    operators[operatorIndex].adsr.rate[3] =  map(newvalue, 0, MAX_ANALOG_VALUE, MAX_ANALOG_VALUE, 0);
                    knobs[knob] = REVPARAMMAP(operators[operatorIndex].adsr.rate[3]);
                    break;                   
                }
             }
             if (oldvalue != knobs[knob]) {
                displayNeedsUpdating = true;
             }

          }
          break;
    }
    
}

void midiProgramChangeHandler(byte channel,  byte program) 
{
    //Serial.println(program);
    if(program + 1 > NumVoices[synth.bank]) program = 0;
    loadPresetVoice(synth.bank, program);
    knobs[KNOB9] = program;
    synth.presetVoice = program + 1;
    synth.playMode = true;
    synth.control = STANDBY;
    printParameters();
    displayNeedsUpdating = true;
}

void midiPitchBendHandler(byte channel, int bend)
{
    if (bend < 0)
    {
        synth.pitchBend.bentDown = true;
        synth.pitchBend.value = map(abs(bend), 0, 8192, PITCH_BEND_UNIT, 2 * PITCH_BEND_UNIT);
    }
    else
    {
        synth.pitchBend.bentDown = false;
        synth.pitchBend.value = map(bend, 0, 8192, PITCH_BEND_UNIT, 2 * PITCH_BEND_UNIT);
    }

    for (uint8_t j = 0; j < NUM_OPERATORS; ++j)
        if(operators[j].fixed_freq_step) updateFixedOperatorStep(j);
        else updateNotesScaledOperatorStep(j);
}






// Updates the note scaled level value for this operator.
__attribute__((always_inline)) inline void setNoteScaledOperatorLevel(uint8_t noteIndex, uint8_t operatorIndex)
{
    int8_t breakPointDistance = operators[operatorIndex].levelScaling.breakPointKey - (notes[noteIndex].keyIndex + LOWEST_KEY);

    if (breakPointDistance == 0)
        notes[noteIndex].scaledLevel[operatorIndex] = map(notes[noteIndex].velocity[operatorIndex], 0, 127, 0, operators[operatorIndex].level);
    // Left side of the break point.
    else if (breakPointDistance > 0)
    {
        // Maps the curve to start in the break point.
        breakPointDistance = map(breakPointDistance, 0, (operators[operatorIndex].levelScaling.breakPointKey - SCALING_LOWEST_KEY), 0, (NUM_SCALING_KEYS - 1));

        switch (operators[operatorIndex].levelScaling.function[0])
        {
            case NONE:
                notes[noteIndex].scaledLevel[operatorIndex] = map(notes[noteIndex].velocity[operatorIndex], 0, 127, 0, operators[operatorIndex].level);
            break;

            case LINEAR:
                notes[noteIndex].scaledLevel[operatorIndex] = map(notes[noteIndex].velocity[operatorIndex], 0, 127, 0, constrain(operators[operatorIndex].level + (operators[operatorIndex].levelScaling.sign[0] * map(levelScalingFunction[0][breakPointDistance], 0, MAX_ANALOG_VALUE, 0, operators[operatorIndex].levelScaling.depth[0])), 0, MAX_ANALOG_VALUE));
            break;

            case EXPONENTIAL:
                notes[noteIndex].scaledLevel[operatorIndex] = map(notes[noteIndex].velocity[operatorIndex], 0, 127, 0, constrain(operators[operatorIndex].level + (operators[operatorIndex].levelScaling.sign[0] * map(levelScalingFunction[1][breakPointDistance], 0, MAX_ANALOG_VALUE, 0, operators[operatorIndex].levelScaling.depth[0])), 0, MAX_ANALOG_VALUE));
            break;
        }
    }
    // Right side of the break point.
    else
    {
        // Maps the curve to start in the break point.
        breakPointDistance = map(abs(breakPointDistance), 0, (NUM_SCALING_KEYS - (operators[operatorIndex].levelScaling.breakPointKey - SCALING_LOWEST_KEY) - 1), 0, (NUM_SCALING_KEYS - 1));

        switch (operators[operatorIndex].levelScaling.function[1])
        {
            case NONE:
                notes[noteIndex].scaledLevel[operatorIndex] = map(notes[noteIndex].velocity[operatorIndex], 0, 127, 0, operators[operatorIndex].level);
            break;

            case LINEAR:
                notes[noteIndex].scaledLevel[operatorIndex] = map(notes[noteIndex].velocity[operatorIndex], 0, 127, 0, constrain(operators[operatorIndex].level + (operators[operatorIndex].levelScaling.sign[1] * map(levelScalingFunction[0][breakPointDistance], 0, MAX_ANALOG_VALUE, 0, operators[operatorIndex].levelScaling.depth[1])), 0, MAX_ANALOG_VALUE));
            break;

            case EXPONENTIAL:
                notes[noteIndex].scaledLevel[operatorIndex] = map(notes[noteIndex].velocity[operatorIndex], 0, 127, 0, constrain(operators[operatorIndex].level + (operators[operatorIndex].levelScaling.sign[1] * map(levelScalingFunction[1][breakPointDistance], 0, MAX_ANALOG_VALUE, 0, operators[operatorIndex].levelScaling.depth[1])), 0, MAX_ANALOG_VALUE));
            break;
        }
    }
}

// Updates the active notes scaled level values.
__attribute__((always_inline)) inline void updateNotesScaledOperatorLevel(uint8_t operatorIndex)
{
    for (uint8_t i = 0; i < MAX_POLYPHONY; ++i)
        if (notes[i].on == true)
        {
            int8_t breakPointDistance = operators[operatorIndex].levelScaling.breakPointKey - (notes[i].keyIndex + LOWEST_KEY);

            if (breakPointDistance == 0)
                notes[i].scaledLevel[operatorIndex] = map(notes[i].velocity[operatorIndex], 0, 127, 0, operators[operatorIndex].level);
            // Left side of the break point.
            else if (breakPointDistance > 0)
            {
                // Maps the curve to start in the break point.
                breakPointDistance = map(breakPointDistance, 0, (operators[operatorIndex].levelScaling.breakPointKey - SCALING_LOWEST_KEY), 0, (NUM_SCALING_KEYS - 1));

                switch (operators[operatorIndex].levelScaling.function[0])
                {
                    case NONE:
                        notes[i].scaledLevel[operatorIndex] = map(notes[i].velocity[operatorIndex], 0, 127, 0, operators[operatorIndex].level);
                    break;

                    case LINEAR:
                        notes[i].scaledLevel[operatorIndex] = map(notes[i].velocity[operatorIndex], 0, 127, 0, constrain(operators[operatorIndex].level + (operators[operatorIndex].levelScaling.sign[0] * map(levelScalingFunction[0][breakPointDistance], 0, MAX_ANALOG_VALUE, 0, operators[operatorIndex].levelScaling.depth[0])), 0, MAX_ANALOG_VALUE));
                    break;

                    case EXPONENTIAL:
                        notes[i].scaledLevel[operatorIndex] = map(notes[i].velocity[operatorIndex], 0, 127, 0, constrain(operators[operatorIndex].level + (operators[operatorIndex].levelScaling.sign[0] * map(levelScalingFunction[1][breakPointDistance], 0, MAX_ANALOG_VALUE, 0, operators[operatorIndex].levelScaling.depth[0])), 0, MAX_ANALOG_VALUE));
                    break;
                }
            }
            // Right side of the break point.
            else
            {
                // Maps the curve to start in the break point.
                breakPointDistance = map(abs(breakPointDistance), 0, (NUM_SCALING_KEYS - (operators[operatorIndex].levelScaling.breakPointKey - SCALING_LOWEST_KEY) - 1), 0, (NUM_SCALING_KEYS - 1));

                switch (operators[operatorIndex].levelScaling.function[1])
                {
                    case NONE:
                        notes[i].scaledLevel[operatorIndex] = map(notes[i].velocity[operatorIndex], 0, 127, 0, operators[operatorIndex].level);
                    break;

                    case LINEAR:
                        notes[i].scaledLevel[operatorIndex] = map(notes[i].velocity[operatorIndex], 0, 127, 0, constrain(operators[operatorIndex].level + (operators[operatorIndex].levelScaling.sign[1] * map(levelScalingFunction[0][breakPointDistance], 0, MAX_ANALOG_VALUE, 0, operators[operatorIndex].levelScaling.depth[1])), 0, MAX_ANALOG_VALUE));
                    break;

                    case EXPONENTIAL:
                        notes[i].scaledLevel[operatorIndex] = map(notes[i].velocity[operatorIndex], 0, 127, 0, constrain(operators[operatorIndex].level + (operators[operatorIndex].levelScaling.sign[1] * map(levelScalingFunction[1][breakPointDistance], 0, MAX_ANALOG_VALUE, 0, operators[operatorIndex].levelScaling.depth[1])), 0, MAX_ANALOG_VALUE));
                    break;
                }
            }
        }
}

// Updates the note scaled step value for this operator.
__attribute__((always_inline)) inline void setNoteScaledOperatorStep(uint8_t noteIndex, uint8_t operatorIndex)
{
    uint16_t bentStep = sineTableStep[notes[noteIndex].keyIndex];

    if (synth.pitchBend.bentDown == true)
        bentStep = (bentStep << PITCH_BEND_SHIFT) / synth.pitchBend.value;
    else
        bentStep = (bentStep * synth.pitchBend.value) >> PITCH_BEND_SHIFT;

    notes[noteIndex].scaledStep[operatorIndex] = (bentStep * operators[operatorIndex].ratio) >> RATIO_SHIFT;
}

// Updates the active notes scaled step values for the given operator.
__attribute__((always_inline)) inline void updateNotesScaledOperatorStep(uint8_t operatorIndex)
{
    uint16_t bentStep;

    for (uint8_t i = 0; i < MAX_POLYPHONY; ++i)
        if (notes[i].on == true)
        {
            bentStep = sineTableStep[notes[i].keyIndex];

            if (synth.pitchBend.bentDown == true)
                bentStep = (bentStep << PITCH_BEND_SHIFT) / synth.pitchBend.value;
            else
                bentStep = (bentStep * synth.pitchBend.value) >> PITCH_BEND_SHIFT;

            notes[i].scaledStep[operatorIndex] = (bentStep  * operators[operatorIndex].ratio) >> RATIO_SHIFT;
        }
}

//frequency in centihertz
int fixedFreq2Step(int frq)
{
  //return (SINE_TABLE_SIZE*(frq*)/SAMPLE_RATE)<<11;  
  return  (((SINE_TABLE_SIZE*frq)<<9)/(25*SAMPLE_RATE));
}
// Updates the note scaled step value for this operator.
__attribute__((always_inline)) inline void setFixedOperatorStep(uint8_t noteIndex, uint8_t operatorIndex)
{
    uint16_t bentStep = operators[operatorIndex].fixed_freq_step;

    //if (synth.pitchBend.bentDown == true)
    //    bentStep = (bentStep << PITCH_BEND_SHIFT) / synth.pitchBend.value;
    //else
    //    bentStep = (bentStep * synth.pitchBend.value) >> PITCH_BEND_SHIFT;

    notes[noteIndex].scaledStep[operatorIndex] = (bentStep * operators[operatorIndex].ratio) >> RATIO_SHIFT;
}

// Updates the active notes scaled step values for the given operator.
__attribute__((always_inline)) inline void updateFixedOperatorStep(uint8_t operatorIndex)
{
    uint16_t bentStep;

    for (uint8_t i = 0; i < MAX_POLYPHONY; ++i)
        if (notes[i].on == true)
        {
            bentStep = operators[operatorIndex].fixed_freq_step;

            //if (synth.pitchBend.bentDown == true)
            //    bentStep = (bentStep << PITCH_BEND_SHIFT) / synth.pitchBend.value;
            //else
            //    bentStep = (bentStep * synth.pitchBend.value) >> PITCH_BEND_SHIFT;

            notes[i].scaledStep[operatorIndex] = (bentStep  * operators[operatorIndex].ratio) >> RATIO_SHIFT;
        }
}

// Sets the envelope increment and initial values.
__attribute__((always_inline)) inline void setEnvelopesParameters(uint8_t noteIndex, uint8_t keyIndex)
{
    int32_t levelDifference;

    for (uint8_t j = 0; j < NUM_OPERATORS; ++j)
    {
        // Sets the initial values of the ADSR envelope.
        notes[noteIndex].adsrStatus[j].value = operators[j].adsr.level[3];
        notes[noteIndex].adsrStatus[j].parameter = ATTACK;
        notes[noteIndex].adsrStatus[j].releaseReady = false;

        for (uint8_t k = 0; k < 4; ++k)
        {
            notes[noteIndex].adsrStatus[j].timer[k] = operators[j].adsr.rate[k] - rateScaling[operators[j].rateScaling][keyIndex + (LOWEST_KEY - SCALING_LOWEST_KEY)];

            if (k != 0)
            {
                notes[noteIndex].adsrStatus[j].incrementAccumulator[k] = (operators[j].adsr.level[k - 1] << ADSR_INC_SHIFT);
                levelDifference = ((operators[j].adsr.level[k] - operators[j].adsr.level[k - 1]) << ADSR_INC_SHIFT);
            }
            else
            {
                notes[noteIndex].adsrStatus[j].incrementAccumulator[0] = (operators[j].adsr.level[3] << ADSR_INC_SHIFT);
                levelDifference = ((operators[j].adsr.level[0] - operators[j].adsr.level[3]) << ADSR_INC_SHIFT);
            }

            if (levelDifference == 0 || notes[noteIndex].adsrStatus[j].timer[k] <= 0)
                notes[noteIndex].adsrStatus[j].timer[k] = 0;
            else
                notes[noteIndex].adsrStatus[j].increment[k] = levelDifference / notes[noteIndex].adsrStatus[j].timer[k];
        }
    }
}

// For when the envelope was interrupted before the release part.
__attribute__((always_inline)) inline void updateEnvelopeRelease(uint8_t noteIndex, uint8_t keyIndex, uint8_t operatorIndex)
{
    int32_t levelDifference;

    notes[noteIndex].adsrStatus[operatorIndex].timer[3] = operators[operatorIndex].adsr.rate[3] - rateScaling[operators[operatorIndex].rateScaling][keyIndex + (LOWEST_KEY - SCALING_LOWEST_KEY)];
    notes[noteIndex].adsrStatus[operatorIndex].incrementAccumulator[3] = (notes[noteIndex].adsrStatus[operatorIndex].value << ADSR_INC_SHIFT);

    levelDifference = ((operators[operatorIndex].adsr.level[3] - notes[noteIndex].adsrStatus[operatorIndex].value) << ADSR_INC_SHIFT);

    if (levelDifference == 0 || notes[noteIndex].adsrStatus[operatorIndex].timer[3] <= 0)
        notes[noteIndex].adsrStatus[operatorIndex].timer[3] = 0;
    else
        notes[noteIndex].adsrStatus[operatorIndex].increment[3] = levelDifference / notes[noteIndex].adsrStatus[operatorIndex].timer[3];

    notes[noteIndex].adsrStatus[operatorIndex].releaseReady = true;
}

// Applies the ADSR envelope in the active notes.
void ICACHE_RAM_ATTR envelopeHandler()
{
    uint8_t finishedOperatorsCounter;
    for (uint8_t i = 0; i < MAX_POLYPHONY; ++i)
        if (notes[i].on == true)
        {
            // Used to set the note as off if all the operators have reached their third level values.
            finishedOperatorsCounter = 0;

            for (uint8_t j = 0; j < NUM_OPERATORS; ++j)
                switch (notes[i].adsrStatus[j].parameter)
                {
                    // Release part of the ADSR envelope.
                    case RRELEASE:
                        if (notes[i].adsrStatus[j].releaseReady == true) {
                            if (notes[i].adsrStatus[j].timer[3] != 0)
                            {
                                notes[i].adsrStatus[j].incrementAccumulator[3] += notes[i].adsrStatus[j].increment[3];
                                notes[i].adsrStatus[j].value = (notes[i].adsrStatus[j].incrementAccumulator[3] >> ADSR_INC_SHIFT);
                                --notes[i].adsrStatus[j].timer[3];
                            }
                            else
                            {
                                notes[i].adsrStatus[j].value = operators[j].adsr.level[3];
                                ++finishedOperatorsCounter;
                            }
                        }
                    break;

                    // Sustain part of the ADSR envelope.
                    case SUSTAIN:
                        if (notes[i].adsrStatus[j].timer[2] != 0)
                        {
                            notes[i].adsrStatus[j].incrementAccumulator[2] += notes[i].adsrStatus[j].increment[2];
                            notes[i].adsrStatus[j].value = (notes[i].adsrStatus[j].incrementAccumulator[2] >> ADSR_INC_SHIFT);
                            --notes[i].adsrStatus[j].timer[2];
                        }
                        else
                        {
                            notes[i].adsrStatus[j].value = operators[j].adsr.level[2];
                            notes[i].adsrStatus[j].releaseReady = true;
                        }
                    break;

                    // Decay part of the ADSR envelope.
                    case DECAY:
                        if (notes[i].adsrStatus[j].timer[1] != 0)
                        {
                            notes[i].adsrStatus[j].incrementAccumulator[1] += notes[i].adsrStatus[j].increment[1];
                            notes[i].adsrStatus[j].value = (notes[i].adsrStatus[j].incrementAccumulator[1] >> ADSR_INC_SHIFT);
                            --notes[i].adsrStatus[j].timer[1];
                        }
                        else
                        {
                            notes[i].adsrStatus[j].value = operators[j].adsr.level[1];
                            notes[i].adsrStatus[j].parameter = SUSTAIN;
                        }
                    break;

                    // Attack part of the ADSR envelope.
                    case ATTACK:
                        if (notes[i].adsrStatus[j].timer[0] != 0)
                        {
                            notes[i].adsrStatus[j].incrementAccumulator[0] += notes[i].adsrStatus[j].increment[0];
                            notes[i].adsrStatus[j].value = (notes[i].adsrStatus[j].incrementAccumulator[0] >> ADSR_INC_SHIFT);
                            --notes[i].adsrStatus[j].timer[0];
                        }
                        else
                        {
                            notes[i].adsrStatus[j].value = operators[j].adsr.level[0];
                            notes[i].adsrStatus[j].parameter = DECAY;
                        }
                    break;
                }

            // Sets the note as off.
            if (finishedOperatorsCounter == NUM_OPERATORS)
            {
                notes[i].on = false;
                synth.keyMapping[notes[i].keyIndex].on = false;
            }
        }
#ifdef ESP8266
        timer1_write(((160/16)*1000000)/ENVELOPE_UPDATE_FREQUENCY);
#endif
}

// Updates knobs parameters to control the values updates.
__attribute__((always_inline)) inline void updateKnobsParameters(uint8_t operatorIndex)
{
   // for (uint8_t i = 0; i < 8; ++i)
   //     synth.knobs.triggered[i] = false;
    if (synth.control == PARAMETERS)
    {         
      for (int x = 0; x < MAX_KNOBS -2; x++)
      {
            if (x == KNOB3 || x == KNOB4) {
              //synth.knobs.oldValue[x] = knobs[x];
              maxvals[x] = MAX_PARAMETERS_LEVEL;
              minvals[x] = 0;
            } else if(x == KNOB6) {
               //synth.knobs.oldValue[x] = knobs[x];
               maxvals[x] = SCALING_HIGHEST_KEY;
               minvals[x] = SCALING_LOWEST_KEY;

            } else {
              //synth.knobs.oldValue[x] = KNOBMAP(knobs[x]);
              maxvals[x] = MAX_DIGITAL_VALUE;
              minvals[x] = 0;
            }
        }
        knobs[KNOB0] = PARAMMAP(operators[operatorIndex].ratio);
        knobs[KNOB1] = PARAMMAP(operators[operatorIndex].level);
        knobs[KNOB2] = PARAMMAP(operators[operatorIndex].feedback);
        knobs[KNOB3] = operators[operatorIndex].velocity;
        knobs[KNOB4] = operators[operatorIndex].rateScaling;
        knobs[KNOB5] = PARAMMAP(operators[operatorIndex].levelScaling.depth[0]);
        knobs[KNOB6] = operators[operatorIndex].levelScaling.breakPointKey;
        knobs[KNOB7] = PARAMMAP(operators[operatorIndex].levelScaling.depth[1]);

    }   
    else if (synth.control == ADSR)
    {
       for (int x = 0; x < MAX_KNOBS -2; x++)
       {   
            //if(x % 2 == 0) synth.knobs.oldValue[x] = KNOBMAP(knobs[x]);
            //else synth.knobs.oldValue[x] = REVKNOBMAP(knobs[x]);
            maxvals[x] = MAX_DIGITAL_VALUE;
            minvals[x] = 0;
       }
       knobs[KNOB0] = PARAMMAP(operators[operatorIndex].adsr.level[3]);
       knobs[KNOB1] = REVPARAMMAP(operators[operatorIndex].adsr.rate[0]);
       knobs[KNOB2] = PARAMMAP( operators[operatorIndex].adsr.level[0]);
       knobs[KNOB3] = REVPARAMMAP(operators[operatorIndex].adsr.rate[1]);
       knobs[KNOB4] = PARAMMAP( operators[operatorIndex].adsr.level[1]);
       knobs[KNOB5] = REVPARAMMAP(operators[operatorIndex].adsr.rate[2]);
       knobs[KNOB6] = PARAMMAP(operators[operatorIndex].adsr.level[2]);
       knobs[KNOB7] = REVPARAMMAP(operators[operatorIndex].adsr.rate[3]);

    }

    for (int x = KNOB8; x < MAX_KNOBS; x++) {
         //synth.knobs.oldValue[x] = KNOBMAP(knobs[x]);
         if (x == KNOB9) maxvals[x] = NumVoices[synth.bank] +1; //NOT -1  
         else maxvals[x] = MAX_DIGITAL_VALUE;
         minvals[x] = 0;
    }
    knobs[KNOB8] = PARAMMAP(synth.volume);
    knobs[KNOB9] = synth.presetVoice; //NOT -1
}

// Loads a preset voice.
__attribute__((always_inline)) inline void loadPresetVoice(uint8_t bank, uint8_t voice)
{
    synth.algorithm = presetAlgorithm[bank][voice];
    int b = bank;
    for (uint8_t i = 0; i < NUM_OPERATORS; ++i)
    {
        int n = 0;
        operators[i].src_sel = presetVoice[b][voice][i][n++];
        operators[i].source = sources[operators[i].src_sel];
        operators[i].ratio = presetVoice[b][voice][i][n++];
        operators[i].fixed_freq_step = presetVoice[b][voice][i][n++];
        operators[i].level = presetVoice[b][voice][i][n++];
        operators[i].feedback = presetVoice[b][voice][i][n++];
        operators[i].velocity = presetVoice[b][voice][i][n++];
        operators[i].rateScaling = presetVoice[b][voice][i][n++];
        operators[i].levelScaling.depth[0] = presetVoice[b][voice][i][n++];
        operators[i].levelScaling.breakPointKey = presetVoice[b][voice][i][n++];
        operators[i].levelScaling.depth[1] = presetVoice[b][voice][i][n++];
        operators[i].levelScaling.sign[0] = presetVoice[b][voice][i][n++];
        operators[i].levelScaling.sign[1] = presetVoice[b][voice][i][n++];
        operators[i].levelScaling.function[0] = (levelScalingFunction_e)(presetVoice[b][voice][i][n++]);
        operators[i].levelScaling.function[1] = (levelScalingFunction_e)(presetVoice[b][voice][i][n++]);
        operators[i].adsr.rate[0] = presetVoice[b][voice][i][n++];
        operators[i].adsr.rate[1] = presetVoice[b][voice][i][n++];
        operators[i].adsr.rate[2] = presetVoice[b][voice][i][n++];
        operators[i].adsr.rate[3] = presetVoice[b][voice][i][n++];
        operators[i].adsr.level[0] = presetVoice[b][voice][i][n++];
        operators[i].adsr.level[1] = presetVoice[b][voice][i][n++];
        operators[i].adsr.level[2] = presetVoice[b][voice][i][n++];
        operators[i].adsr.level[3] = presetVoice[b][voice][i][n++];
    }
#ifdef ESP8266
    i2s_set_callback(DACAlgorithmsHandler[synth.algorithm]);
#endif
}

// Loads a preset voice.
__attribute__((always_inline)) inline void savePresetVoice(uint8_t bank, uint8_t voice)
{
    int b =  bank; 
    presetAlgorithm[b][voice] = synth.algorithm;

    for (uint8_t i = 0; i < NUM_OPERATORS; ++i)
    {
        int n = 0;
        presetVoice[b][voice][i][n++] = operators[i].src_sel;
        presetVoice[b][voice][i][n++]=operators[i].ratio;
        presetVoice[b][voice][i][n++]=operators[i].fixed_freq_step;
        presetVoice[b][voice][i][n++]=operators[i].level;
        presetVoice[b][voice][i][n++]=operators[i].feedback;
        presetVoice[b][voice][i][n++]=operators[i].velocity;
        presetVoice[b][voice][i][n++]=operators[i].rateScaling;
        presetVoice[b][voice][i][n++]=operators[i].levelScaling.depth[0];
        presetVoice[b][voice][i][n++]=operators[i].levelScaling.breakPointKey;
        presetVoice[b][voice][i][n++]=operators[i].levelScaling.depth[1];
        presetVoice[b][voice][i][n++]= operators[i].levelScaling.sign[0];
        presetVoice[b][voice][i][n++]=operators[i].levelScaling.sign[1];
        presetVoice[b][voice][i][n++] = operators[i].levelScaling.function[0];
        presetVoice[b][voice][i][n++] = operators[i].levelScaling.function[1];
        presetVoice[b][voice][i][n++]= operators[i].adsr.rate[0];
        presetVoice[b][voice][i][n++]=operators[i].adsr.rate[1];
        presetVoice[b][voice][i][n++]=operators[i].adsr.rate[2];
        presetVoice[b][voice][i][n++]=operators[i].adsr.rate[3];
        presetVoice[b][voice][i][n++]=operators[i].adsr.level[0];
        presetVoice[b][voice][i][n++]=operators[i].adsr.level[1];
        presetVoice[b][voice][i][n++]=operators[i].adsr.level[2];
        presetVoice[b][voice][i][n++]= operators[i].adsr.level[3];
    }
}




__attribute__((always_inline)) inline void updateDisplay()
{
  updatingDisplay = true;
  const uint8_t font_height = 7;
  int o = synth.selectedOperator;
  int n = 0;
  display.clearBuffer();
  display.setCursor(0,n++*font_height);
  display.printf("PATCH: %02d %s", synth.presetVoice, patchNames[synth.bank][synth.presetVoice -1]);    
  display.setCursor(0,n++*font_height);
  display.printf("ALG: %-4d  VOL: %-4d%% ", synth.algorithm, map(synth.volume, 0, MAX_ANALOG_VALUE, 0, 100));    
  display.setCursor(0,n++*font_height);
  display.printf("MOD: %s", knobsControlDisp[synth.control]);
  if (synth.control == PARAMETERS || synth.control == ADSR) {
    display.printf(" %-2d %s", o, sourcesDisp[operators[o].src_sel]);
  } 
  display.setCursor(0,n++*font_height);
  display.printf("LSL: %s%-2d LSR: %s%-2d",
    levelScalingFunctionDisp[operators[o].levelScaling.function[0]],
    operators[o].levelScaling.sign[0],
    levelScalingFunctionDisp[operators[o].levelScaling.function[1]],
    operators[o].levelScaling.sign[1]);
  if (synth.control == PARAMETERS) {
    display.setCursor(0,n++*font_height);
    display.printf("RAT: %-4d  LVL: %-4d", operators[o].ratio, operators[o].level);
    display.setCursor(0,n++*font_height);      
    display.printf("FB : %-4d  VEL: %-4d", operators[o].feedback, operators[o].velocity);
    display.setCursor(0, n++*font_height); 
    display.printf("RS : %-4d", operators[o].rateScaling);    
    display.setCursor(0, n++*font_height); 
    display.printf("LSD: %-4d  RSD %-4d", operators[o].levelScaling.depth[0],  
          operators[o].levelScaling.depth[1]);
    display.setCursor(0,n++*font_height); 
    display.printf("BPK: %-4d   ",  operators[o].levelScaling.breakPointKey);
    }
  if (synth.control == ADSR) {
        display.setCursor(0,n++*font_height);
        display.printf("RA1: %-4d LV1: %-4d",operators[o].adsr.rate[0], operators[o].adsr.level[0]);
        display.setCursor(0,n++*font_height);
        display.printf("RA2: %-4d LV2: %-4d",operators[o].adsr.rate[1],operators[o].adsr.level[1]);
        display.setCursor(0,n++*font_height);
        display.printf("RA3: %-4d LV3: %-4d",operators[o].adsr.rate[2], operators[o].adsr.level[2]);
        display.setCursor(0,n++*font_height);
        display.printf("RA4: %-4d LV4: %-4d",operators[o].adsr.rate[3], operators[o].adsr.level[3]);
  }
  if (synth.control == STANDBY) {
     n+= 2;
     display.setCursor(0,n*font_height);
     if (standbyMessage) display.printf(standbyMessage);
  }
  if (synth.control == SAVE) {
     n+=2;
     display.setCursor(0,n*font_height);
     display.printf("Select voice to save.");
  }
  if (synth.control == MENU || synth.control == MENU_EDIT) {
     for (int x = 0; x < MENU_LINES ; x++) {
      display.setCursor(0,n++*font_height);
      if(x+windowStart < currentMenuItems) {
        char * prt = currentMenu[x + windowStart].line;
        uint8_t data =  *currentMenu[x].data;
        if (x+windowStart == selectedItem && synth.control == MENU_EDIT) {
             data =  knobs[KNOB9];
        }  
        char * disp = "";
        if (currentMenu[x + windowStart].textdisp) {
          disp = currentMenu[x + windowStart].textdisp[data];
        }
        display.printf(prt, data, disp);
        if (x+windowStart == selectedItem) {
          
           display.write (0xab);
        } 
      }
     }  
  }
  display.sendBuffer();
  updatingDisplay = false;
  displayNeedsUpdating = false;
}


__attribute__((always_inline)) inline void updateRemoteKnobs()
{
  int o = synth.selectedOperator;
#define DEL 5

   MIDI1.sendControlChange( SOUND_CC_1_LSB, synth.algorithm, synth.channel); 
  
   MIDI1.sendControlChange(synth.channel, VOLUME_CC_MSB, synth.volume >>7);    
   MIDI1.sendControlChange(synth.channel, VOLUME_CC_LSB, synth.volume &0x7f);    
  //MIDI1.sendControlChange(synth.channel, GP5_CC_MSB, (synth.control == ADSR) *127);
  if (synth.control == PARAMETERS || synth.control == ADSR) {
    delay(DEL);
    MIDI1.sendControlChange(GP1_CC_MSB, o, synth.channel);
    delay(DEL);
    MIDI1.sendControlChange(GP4_CC_MSB, operators[o].src_sel, synth.channel);
    delay(DEL);
  } 
  
  MIDI1.sendControlChange(GP2_CC_MSB, lsToCycle(0), synth.channel);
  delay(DEL);
  MIDI1.sendControlChange(GP3_CC_MSB, lsToCycle(1), synth.channel);
  if (synth.control == PARAMETERS) {
    delay(DEL);
    MIDI1.sendControlChange(U1_CC_MSB, operators[o].ratio >> 7 & 0x7f, synth.channel);
    delay(DEL);
    MIDI1.sendControlChange(U1_CC_LSB, operators[o].ratio& 0x7f, synth.channel);
    delay(DEL);
    MIDI1.sendControlChange(U2_CC_MSB, operators[o].level >> 7, synth.channel);
    delay(DEL);
    MIDI1.sendControlChange(U2_CC_LSB, operators[o].level & 0x7f, synth.channel);
    delay(DEL);
    MIDI1.sendControlChange(U3_CC_MSB, operators[o].feedback >> 7, synth.channel);
    delay(DEL);
    MIDI1.sendControlChange(U3_CC_LSB, operators[o].feedback & 0x7f, synth.channel);
    delay(DEL);
    MIDI1.sendControlChange(U4_CC_MSB, 0, synth.channel);
    delay(DEL);
    MIDI1.sendControlChange(U4_CC_LSB, operators[o].velocity &0x7f, synth.channel);
    delay(DEL);
   MIDI1.sendControlChange(U5_CC_MSB, 0, synth.channel);    
    delay(DEL);
    MIDI1.sendControlChange(U5_CC_LSB, operators[o].rateScaling & 0x7f, synth.channel);    
    delay(DEL);
   MIDI1.sendControlChange(U6_CC_MSB, operators[o].levelScaling.depth[0] >> 7, synth.channel);  
    delay(DEL);
   MIDI1.sendControlChange(U6_CC_LSB, operators[o].levelScaling.depth[0] & 0x7f, synth.channel);  
     delay(DEL);
    MIDI1.sendControlChange(U7_CC_MSB, operators[o].levelScaling.depth[1] >> 7, synth.channel);
    delay(DEL);
    MIDI1.sendControlChange(U7_CC_LSB, operators[o].levelScaling.depth[1] & 0x7f, synth.channel);
    delay(DEL);
    MIDI1.sendControlChange(U8_CC_MSB, 0, synth.channel);
    delay(DEL);
    MIDI1.sendControlChange(U8_CC_LSB, operators[o].levelScaling.breakPointKey, synth.channel);
    delay(DEL);
 }
  if (synth.control == ADSR) {
     delay(DEL);
       MIDI1.sendControlChange(U1_CC_MSB, (operators[o].adsr.rate[0] >> 7) & 0x7f, synth.channel);
    delay(DEL);
        MIDI1.sendControlChange(U1_CC_LSB, (operators[o].adsr.rate[0] & 0x7f), synth.channel);
    delay(DEL);
        MIDI1.sendControlChange(U2_CC_MSB, operators[o].adsr.level[0] >> 7, synth.channel);
    delay(DEL);
        MIDI1.sendControlChange(U2_CC_LSB, operators[o].adsr.level[0] & 0x7f, synth.channel);
    delay(DEL);
        MIDI1.sendControlChange(U3_CC_MSB, operators[o].adsr.rate[1] >> 7, synth.channel);
    delay(DEL);
        MIDI1.sendControlChange(U3_CC_LSB, operators[o].adsr.rate[1] & 0x7f, synth.channel);
    delay(DEL);
        MIDI1.sendControlChange(U4_CC_MSB, operators[o].adsr.level[1] >> 7, synth.channel);
    delay(DEL);
        MIDI1.sendControlChange(U4_CC_LSB, operators[o].adsr.level[1] &0x7f, synth.channel);
    delay(DEL);
        MIDI1.sendControlChange(U5_CC_MSB, operators[o].adsr.rate[2] >> 7, synth.channel);
    delay(DEL);
        MIDI1.sendControlChange(U5_CC_LSB, operators[o].adsr.rate[2] & 0x7f, synth.channel);
    delay(DEL);
        MIDI1.sendControlChange(U6_CC_MSB, operators[o].adsr.level[2] >> 7, synth.channel);
    delay(DEL);
        MIDI1.sendControlChange(U6_CC_LSB, operators[o].adsr.level[2]  &0x7f, synth.channel);
    delay(DEL);
        MIDI1.sendControlChange(U7_CC_MSB, operators[o].adsr.rate[3] >> 7, synth.channel);
    delay(DEL);
        MIDI1.sendControlChange(U7_CC_LSB, operators[o].adsr.rate[3] & 0x7f, synth.channel);
    delay(DEL);
        MIDI1.sendControlChange(U8_CC_MSB, operators[o].adsr.level[3] >> 7, synth.channel);
    delay(DEL);
        MIDI1.sendControlChange(U8_CC_LSB, operators[o].adsr.level[3] & 0x7f, synth.channel);
    delay(DEL);
  }
}

// Prints parameters to the serial monitor.
__attribute__((always_inline)) inline void printParameters()
{

    Serial.print("BANK ");
    Serial.println(synth.bank);
    Serial.print("PATCH ");
    Serial.println(patchNames[synth.bank][synth.presetVoice -1]);
    Serial.print("ALGORITHM ");
    Serial.println(synth.algorithm);

    for (uint8_t j = 0; j < NUM_OPERATORS; ++j)
    {
        Serial.print("OP");
        Serial.print(j);
        Serial.print(": ");
        Serial.print(operators[j].src_sel);
        Serial.print(", ");
        Serial.print(operators[j].ratio);
        Serial.print(", ");
        Serial.print(operators[j].fixed_freq_step);
        Serial.print(", ");
        Serial.print(operators[j].level);
        Serial.print(", ");
        Serial.print(operators[j].feedback);
        Serial.print(", ");
        Serial.print(operators[j].velocity);
        Serial.print(", ");
        Serial.print(operators[j].rateScaling);
        Serial.print(", ");
        Serial.print(operators[j].levelScaling.depth[0]);
        Serial.print(", ");
        Serial.print(operators[j].levelScaling.breakPointKey);
        Serial.print(", ");
        Serial.print(operators[j].levelScaling.depth[1]);
        Serial.print("\tLS:");
        Serial.print(operators[j].levelScaling.sign[0]);
        Serial.print(", ");
        Serial.print(operators[j].levelScaling.sign[1]);
        Serial.print(", ");
        Serial.print(operators[j].levelScaling.function[0]);
        Serial.print(", ");
        Serial.print(operators[j].levelScaling.function[1]);
        Serial.print("\tADSR: ");
        Serial.print(operators[j].adsr.rate[0]);
        Serial.print(", ");
        Serial.print(operators[j].adsr.rate[1]);
        Serial.print(", ");
        Serial.print(operators[j].adsr.rate[2]);
        Serial.print(", ");
        Serial.print(operators[j].adsr.rate[3]);
        Serial.print(", ");
        Serial.print(operators[j].adsr.level[0]);
        Serial.print(", ");
        Serial.print(operators[j].adsr.level[1]);
        Serial.print(", ");
        Serial.print(operators[j].adsr.level[2]);
        Serial.print(", ");
        Serial.println(operators[j].adsr.level[3]);
    }

    Serial.println("");
}

void show_audio_load()
{
  time_t t = now();
  Serial.printf("%4d-%02d-%02d %02d:%02d:%02d ",year(t), month(t),day(t), hour(t),minute(t),second(t));
  Serial.print(F("CPU: "));
  Serial.print(AudioProcessorUsage(), 2);
  Serial.print(F("%   CPU MAX: "));
  Serial.print(AudioProcessorUsageMax(), 2);
  Serial.print(F("%  MEM: "));
  Serial.print(AudioMemoryUsage(), DEC);
  Serial.print(F("   MEM MAX: "));
  Serial.print(AudioMemoryUsageMax(), DEC);
  Serial.print(F("   RENDER_TIME_MAX: "));
  Serial.print(render_time_max, DEC);
  /*Serial.print(F("   XRUN: "));
  Serial.print(xrun, DEC);
  Serial.print(F("   OVERLOAD: "));
  Serial.print(overload, DEC);
  Serial.print(F("   PEAK: "));
  Serial.print(peak, DEC); */
  Serial.print(F(" BLOCKSIZE: "));
  Serial.print(AUDIO_BLOCK_SAMPLES, DEC);
  Serial.print(F(" ACTIVE_VOICES: "));
  int active_voices = 0;
  for (uint8_t i = 0; i < MAX_POLYPHONY; ++i)
     if (notes[i].on == true)
          active_voices++;
      
  Serial.print(active_voices, DEC);
  Serial.println();
  AudioProcessorUsageMaxReset();
  AudioMemoryUsageMaxReset();
}
