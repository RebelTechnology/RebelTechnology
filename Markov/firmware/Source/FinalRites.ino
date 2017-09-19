#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#ifndef PSTR
 #define PSTR // Make Arduino Due happy
#endif

#include "Markov.h"

#define PIN 3

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
  NEO_RGB            + NEO_KHZ400);

const uint16_t colors[] = {
  matrix.Color(0, 0, 255)
};

static const char GENESIS[] = "IN THE BEGINNING, GOD CREATED THE HEAVENS AND THE EARTH. THE EARTH WAS WITHOUT FORM AND VOID, AND DARKNESS WAS OVER THE FACE OF THE DEEP. AND THE SPIRIT OF GOD WAS HOVERING OVER THE FACE OF THE WATERS. AND GOD SAID, LET THERE BE LIGHT, AND THERE WAS LIGHT. AND GOD SAW THAT THE LIGHT WAS GOOD. AND GOD SEPARATED THE LIGHT FROM THE DARKNESS. GOD CALLED THE LIGHT DAY, AND THE DARKNESS HE CALLED NIGHT. AND THERE WAS EVENING AND THERE WAS MORNING, THE FIRST DAY.";
// 88 words, 37 unique, 460 chars.
MarkovChain markov;

int words = 6; // minimum number of words generated per paragraph
float chance = 0.0; // chance of producing a completely random token

void setup() {
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(10);
  matrix.setTextColor(colors[0]);
  markov.learn(GENESIS, 16);
  randomSeed(analogRead(0));
}

/*
 * Generate a paragraph that fits in @dest with at least @words, ending if possible with a full stop
 */
int generate(char* dest, int len, int words, float chance){
  Entry* entry = markov.first();
  int pos = 0;
  while(pos < len-12){
    entry = markov.next(entry, chance);
    if(!entry->isSeparator()){
      sprintf(dest+pos++, " ");
    }
    if(pos + entry->len < len-1){
      sprintf(dest+pos, "%.*s", entry->len, entry->str);
      pos += entry->len;
    }
    if(words-- <= 1 && entry->isStop())
      break;
  }
  // if(!entry->isSeparator())
  //   sprintf(dest+pos++, ".");
  // fill in with up to 6 spaces
  for(int i=0; i<6 && pos < len; ++i)
    sprintf(dest+pos++, " ");
  return pos;
}

char dest[512]; // destination character buffer
int x = 0;
int limit = 0;

void loop() {
  if(--x < -limit){
    int len = generate(dest, sizeof(dest), words, chance);
    limit = len*8;
    x = matrix.width();
  }
  matrix.fillScreen(0);
  matrix.setCursor(x, 0);
  matrix.print(dest);
  matrix.show();
  delay(50);
}
