// g++ Markov.cpp -o markov

#include <strings.h> // strncasecmp
#include <stdio.h>  // puts
#include <time.h> // time
#include "Markov.h"

MarkovChain markov;

// generate a phrase that fits in dest with at least @words, ending if possible with a full stop
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

int main(int argc, char** argv){
  srand(time(NULL));
  char* text = (char*)
    "IN THE BEGINNING, GOD CREATED THE HEAVENS AND THE EARTH. THE EARTH WAS WITHOUT FORM AND VOID, AND DARKNESS WAS OVER THE FACE OF THE DEEP. AND THE SPIRIT OF GOD WAS HOVERING OVER THE FACE OF THE WATERS. AND GOD SAID, LET THERE BE LIGHT, AND THERE WAS LIGHT. AND GOD SAW THAT THE LIGHT WAS GOOD. AND GOD SEPARATED THE LIGHT FROM THE DARKNESS. GOD CALLED THE LIGHT DAY, AND THE DARKNESS HE CALLED NIGHT. AND THERE WAS EVENING AND THERE WAS MORNING, THE FIRST DAY."; // 88 words, 460 chars.
  int words = 88;
  float chance = 0.0;
  int limit = 16;
  if(argc > 1)
    words = atoi(argv[1]);
  if(argc > 2)
    chance = atof(argv[2]);
  if(argc > 3)
    limit = atoi(argv[3]);
  if(argc > 4)
    text = argv[4];
  markov.learn(text, limit);
  int size = 1024*4;
  char dest[size];
  
  generate(dest, size, words, chance);
  printf("%s", dest);
}

// int main(int argc, char** argv){
//   srand(time(NULL));
//   char* text = (char*)
//     "IN THE BEGINNING, GOD CREATED THE HEAVENS AND THE EARTH. THE EARTH WAS WITHOUT FORM AND VOID, AND DARKNESS WAS OVER THE FACE OF THE DEEP. AND THE SPIRIT OF GOD WAS HOVERING OVER THE FACE OF THE WATERS. AND GOD SAID, LET THERE BE LIGHT, AND THERE WAS LIGHT. AND GOD SAW THAT THE LIGHT WAS GOOD. AND GOD SEPARATED THE LIGHT FROM THE DARKNESS. GOD CALLED THE LIGHT DAY, AND THE DARKNESS HE CALLED NIGHT. AND THERE WAS EVENING AND THERE WAS MORNING, THE FIRST DAY."; // 88 words, 460 chars.
//   int words = 88;
//   float chance = 0.1;
//   int limit = 16;
//   if(argc > 1)
//     words = atoi(argv[1]);
//   if(argc > 2)
//     chance = atof(argv[2]);
//   if(argc > 3)
//     limit = atoi(argv[3]);
//   if(argc > 4)
//     text = argv[4];
//   MarkovChain markov;
//   markov.learn(text, limit);
//   Entry* entry = markov.first();
//   while(--words){
//     entry = markov.next(entry, chance);
//     if(!entry->isSeparator()){
//       printf(" ");
//     }
//     printf("%.*s", entry->len, entry->str);
//   }
//   // markov.generate(dest, words, chance);
//   // puts(dest);
// }
