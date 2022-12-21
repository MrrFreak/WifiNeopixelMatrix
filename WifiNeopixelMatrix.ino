// https://forum.arduino.cc/t/nodemcu-und-ws2812b/539611/8
// https://learn.adafruit.com/adafruit-neopixel-uberguide/arduino-library-use
// https://developer.arm.com/documentation/ka002428/latest
// https://maker.pro/esp8266/tutorial/esp8266-tutorial-how-to-control-anything-from-the-internet


// https://forum.arduino.cc/t/umrechnung-hsv-nach-rgb/255462
// https://learn.adafruit.com/led-tricks-gamma-correction/the-issue
// https://learn.adafruit.com/led-tricks-gamma-correction/the-quick-fix

// https://arduino.stackexchange.com/questions/25945/how-to-read-and-write-eeprom-in-esp8266
// https://docs.arduino.cc/learn/built-in-libraries/eeprom


// Wlan Einstellungen
#include <ESP8266WiFi.h>
#include "vars.h" // ssid und password sind hier drin definiert
#include "gammavals.h"
#include "LEDPostions.h"
//const char* ssid = "";//type your ssid
//const char* password = "";//type your password
WiFiServer server(80);//Service Port

// Neopixle Compile Optionen
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#include <EEPROM.h>

// Neopixle Einstellungen
#define PIN_S1         D5 //oben
#define NUMPIXELS_S1   256 //1 Matrix mit 256 LEDs
Adafruit_NeoPixel pixels_S1(NUMPIXELS_S1, PIN_S1, NEO_GRB + NEO_KHZ800);
                                                  
//Globale Zeit Variablen die im EEPROM gesichert werden
unsigned long delayval;
unsigned long farbdelayval;
//Globale Zeit Variablen die temporär zur Laufzeit sind
unsigned long actual_time = 0;
unsigned long action_time = 0;
unsigned long farb_action_time = 0;
//Globale Schalter
int run_up = 1;
int r_up = 1;
int g_up = 1;
int b_up = 1;
//Gloable Konstanten
double x_m = 80.0;
double y_m = 80.0;
//Globale Werte die im EEPROM gesichert werden
int eeAddress;
int hue_val;
int delta_hue;
int modus;
int fixed_farbe;
int max_hell;
int min_hell;
int r;
int g;
int b;
int w;
double xbreite;
double ybreite;
double rbreite;
double r_delta;
//Globale Werte die temporär zur Laufzeit sind
int i_pixel = 0;
int tmpval = 0;
double x_cursor = 0.0;
double y_cursor = 0.0;
double r_cursor = 0.0;
double phi_glb;
int dimm_hell;
//Buildin LED Einstellungen
int aktiv = LOW;
int inaktiv = HIGH;
//Sound2Light Werte
#define puffer 100
float value;
float mittelwert; 
float circular_buffer_xc[puffer];
int circular_buffer_hue[puffer];
int flipflop;
float tmp_threshold;
float threshold;
float maxVal;
int idx = 0;
int glb_hell = 0;

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, inaktiv);
  /**********************************
   * EEPROM initialisieren
  **********************************/
  // commit 512 bytes of ESP8266 flash (for "EEPROM" emulation)
  // this step actually loads the content (512 bytes) of flash into 
  // a 512-byte-array cache in RAM
  EEPROM.begin(512);
  /**********************************
   * EEPROM initialisieren
  **********************************/
  eeAddress = 0*sizeof(int)+0*sizeof(double);
  //hue_val = 0;
  EEPROM.get(eeAddress,hue_val);
  //
  eeAddress = 1*sizeof(int)+0*sizeof(double);
  //modus = 0;
  EEPROM.get(eeAddress,modus);
  //
  eeAddress = 2*sizeof(int)+0*sizeof(double);
  //fixed_farbe = 0;
  EEPROM.get(eeAddress,fixed_farbe);
  //
  eeAddress = 3*sizeof(int)+0*sizeof(double);
  //xbreite = 800;
  EEPROM.get(eeAddress,xbreite);
  //
  eeAddress = 3*sizeof(int)+1*sizeof(double);
  //ybreite = 800;
  EEPROM.get(eeAddress,ybreite);
  //
  eeAddress = 3*sizeof(int)+2*sizeof(double);
  //delayval = 80;
  EEPROM.get(eeAddress,delayval);
  //
  eeAddress = 3*sizeof(int)+2*sizeof(double)+1*sizeof(unsigned long);
  //farbdelayval = 80;
  EEPROM.get(eeAddress,farbdelayval);
  //
  eeAddress = 3*sizeof(int)+2*sizeof(double)+2*sizeof(unsigned long);
  //rbreite = 80;
  EEPROM.get(eeAddress,rbreite);
  //
  eeAddress = 3*sizeof(int)+3*sizeof(double)+2*sizeof(unsigned long);
  //r_delta = 80;
  EEPROM.get(eeAddress,r_delta);
  //
  eeAddress = 3*sizeof(int)+4*sizeof(double)+2*sizeof(unsigned long);
  //max_hell = 150;
  EEPROM.get(eeAddress,max_hell);
  //
  eeAddress = 4*sizeof(int)+4*sizeof(double)+2*sizeof(unsigned long);
  //r = 150;
  EEPROM.get(eeAddress,r);
  //
  eeAddress = 5*sizeof(int)+4*sizeof(double)+2*sizeof(unsigned long);
  //g = 150;
  EEPROM.get(eeAddress,g);
  //
  eeAddress = 6*sizeof(int)+4*sizeof(double)+2*sizeof(unsigned long);
  //b = 150;
  EEPROM.get(eeAddress,b);
  //
  eeAddress = 7*sizeof(int)+4*sizeof(double)+2*sizeof(unsigned long);
  //w = 150;
  EEPROM.get(eeAddress,w);
  //
  eeAddress = 8*sizeof(int)+4*sizeof(double)+2*sizeof(unsigned long);
  //min_hell = 70;
  EEPROM.get(eeAddress,min_hell);
  //
  eeAddress = 9*sizeof(int)+4*sizeof(double)+2*sizeof(unsigned long);
  //delta_hue = 70;
  EEPROM.get(eeAddress,delta_hue);

  /**********************************
   * NeoPixel initialisieren
  **********************************/
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
    clock_prescale_set(clock_div_1);
  #endif
  // END of Trinket-specific code.
  pixels_S1.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels_S1.setBrightness(100); // Maximal möglich 255, möglicherweise wird die Matrix da zu heiss
  pixels_S1.clear(); // Set all pixel colors to 'off'
  switch_mode();
  /**********************************
   * Variablen initialisieren
  **********************************/
  
  
  /**********************************
   * WLAN Verbindung herstellen
  **********************************/
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  // Start the server
  server.begin();
  Serial.println("Server started");
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void loop() {
  actual_time = millis(); // Zeit bei Beginn eines Zyklus merken
  switch_mode();
  // Check if a client has connected
  //digitalWrite(LED_BUILTIN, aktiv); // Auskommentier für Sound2Light Test
  checkforhttprequest();
  //digitalWrite(LED_BUILTIN, inaktiv); // Auskommentier für Sound2Light Test
}

void switch_mode(){
  switch(modus){
    case 0:
      Show_RGB();
      break;
    case 1:
      Show_HUE();
      break;
    case 2:
      Show_RainbowRun();
      break;
    case 3:
      Show_MovingDot();
      break;
    case 4:
      Show_PulsatingCircle();
      break;
    case 5:
      Show_Cock();
      break;
    default:
      pixels_S1.clear();
      break;
  }
}
