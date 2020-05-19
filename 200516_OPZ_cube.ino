//
// OP-Z Cube
// (c) matesteinforth.com 2020
//
// based on DMXUSB https://github.com/DaAwesomeP/dmxusb/
// uses FastLED https://github.com/FastLED/FastLED

//
#define FASTLED_ALLOW_INTERRUPTS 0
#include "DMXUSB.h"
#include <FastLED.h>

#define DATA_PIN 3 // data pin
#define BRIGHTNESS 164 // LED brightness
#define MAXLED 15 // maximum LEDs per channel

//
// Define Matrix Mapping ala https://forum.arduino.cc/index.php?topic=45681.0
const byte map_array[16][15] PROGMEM = {
  {  1,  80, 150 },
  {  2,   6,  79,  85, 149, 145},
  { 11,   7,   3, 140, 144, 148, 153,  78,  84,  90 },
  { 16,  12,   8,   4,  77, 83,   89,  95, 135, 139, 143, 147 },
  { 21,  17,  13,   9,   5, 130, 134, 138, 142, 146,  76,  82,  88,  94, 100 },
  { 22,  18,  14,  10,  26, 129, 133, 137, 141,  55,  81,  87,  93,  99, 101 },
  { 23,  19,  15,  31,  27, 128, 132, 136,  54,  60,  86,  92,  98, 106, 102 },
  { 24,  20,  36,  32,  28, 127, 131,  53,  59,  65,  91,  97, 111, 107, 103 },
  { 25,  41,  37,  33,  29, 126,  52,  58,  64,  70,  96, 104, 108, 112, 116},
  { 46,  42,  38,  34,  30,  51,  57,  63,  69,  75, 121, 117, 113, 109, 105},
  { 47,  43,  39,  35,  56,  62,  68,  74, 122, 118, 114, 110},
  { 48,  44,  40,  61,  67,  73, 123, 119, 115},
  { 49,  45,  66,  72, 124, 120},
  { 50,  71, 125},
  {},
  {}
};


//
// no user serviceable parts down here
#define DMXUSB_BAUDRATE 115200 // Recommended Arduino baud rate: 115200 - DMX baud rate: 250000
#define NUM_LEDS 16*MAXLED+10 // Number of LEDs

// Define the array of LEDs
CRGB leds[NUM_LEDS];

// receive a DMX transmission, write data to LEDs and show it
void showLEDs(int universe, char buffer[512]) {

  // iterating over the channels
  for (int index = 0; index < 16; index++) {
    for ( int j = 0; j < MAXLED; ++j ) {
      byte myBarMain = pgm_read_byte(&(map_array[index][j])); // look up the LED ID in the mapping table
      if ( myBarMain > 0) { // all elements with 0 are passed, LED IDs are shifted by 1
        leds[myBarMain - 1] = CRGB(buffer[index * 3 + 1], buffer[index * 3], buffer[index * 3 + 2]); // GRB order
      }
    }
  }
  FastLED.show(); // Display the frame after processing all channels
}

DMXUSB DMXPC(
  // Stream serial,
  Serial,
  // int baudrate,
  DMXUSB_BAUDRATE,
  // int mode,
  // With mode==1, the library processes two universes for a total of 1024 DMX channels
  0,
  // void (*dmxInCallback)(int universe, unsigned int index, char buffer[512])
  showLEDs
);

void setup() {
  Serial.begin(DMXUSB_BAUDRATE);
  FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
  DMXPC.listen();
}
