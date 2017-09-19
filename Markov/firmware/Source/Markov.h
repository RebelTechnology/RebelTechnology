#include <stdint.h>
#include <string.h>
#include <stdlib.h> // rand

#define MAX_ENTRIES 256
#define MAX_ENTRY_SIZE 16

class Token {
public:
  char* str;
  size_t len;
  bool matches(Token* other){
    return len == other->len && strncasecmp(str, other->str, len) == 0;
  }
  void set(char* s, size_t l){
    str = s;
    len = l;
  }
  void advance(size_t steps, size_t l){
    str += steps;
    len = l;
  }
  bool isSeparator(){
    return len < 1 || (str[0] == ',' || str[0] == '.');
  }
  bool isStop(){
    return len == 1 && str[0] == '.';
  }
};

class Entry : public Token {
public:
  Entry* successor[MAX_ENTRY_SIZE];
  uint16_t count;
  uint16_t next;
  void addSuccessor(Entry* other, uint16_t limit){
    successor[next++] = other;
    if(next >= MAX_ENTRY_SIZE)
      next = 0;
    if(++count >= limit)
      count = limit;
  }
  Entry* getNextEntry(float p){
    uint16_t index = next - 1 - p*count;
    return successor[index % MAX_ENTRY_SIZE];
  }
  void reset(){
    count = 0;
  }
  void set(Token* tok){
    str = tok->str;
    len = tok->len;
  }
};

class MarkovChain {
public:
  Entry entries[MAX_ENTRIES];
  uint16_t entryCount;
  // begins with one start entry
  MarkovChain() : entryCount(1) {}
    
  int getMatchingEntry(Token* tok){
    for(int i=0; i<entryCount; ++i){
      if(entries[i].matches(tok))
	return i;
    }
    return -1;
  }

  Entry* processToken(Token& tok, Entry* prev, uint16_t limit){
    int i = getMatchingEntry(&tok);
    if(i < 0 && tok.len > 0 && entryCount < MAX_ENTRIES){
      // add entry
      i = entryCount;
      entries[entryCount++].set(&tok);
    }
    if(i >= 0 && prev != NULL){
      prev->addSuccessor(&entries[i], limit);
      prev = &entries[i];
    }
    return prev;
  }
    
  void addToken(Token* tok){
    // add token as new entry if it is not already known    
    if(tok->len > 0 && entryCount < MAX_ENTRIES && getMatchingEntry(tok) < 0)
      entries[entryCount++].set(tok);
  }

  void learn(char* text, uint16_t limit){
    Entry* prev = &entries[0]; // start entry
    Token tok;
    tok.str = text;
    tok.len = 0;
    while(tok.str[tok.len] != '\0'){
      switch(tok.str[tok.len]){
      case '.':
      case ',':
      case ':':
      case ';':
	// process word
	prev = processToken(tok, prev, limit);
	tok.advance(tok.len, 1);
	// process delimiter
	prev = processToken(tok, prev, limit);
	tok.advance(1, 0);
	break;
      case ' ':
	prev = processToken(tok, prev, limit);
	tok.advance(tok.len+1, 0);
	break;
      default:
	tok.len++;
	break;
      }
    }
  }

  float randf(){
    return (float)rand()/RAND_MAX;
  }

  Entry* first(){
    return &entries[0];
  }

  Entry* next(Entry* previous, float chance){
    if(randf() < chance)
      return &entries[(int)((entryCount-2)*randf())+1]; // pick random, avoid start
    else
      return previous->getNextEntry(randf());      
  }
  
  // void generate(char* str, int words, float chance){
  //   Entry* ent = &entries[0];
  //   while(words--){
  //     if(randf() < chance)
  // 	ent = &entries[(int)((entryCount-2)*randf())+1]; // pick random, avoid start
  //     else
  // 	ent = ent->getNextEntry(randf());
  //     if(ent == NULL)
  // 	break;
  //     str = stpncpy(str, ent->str, ent->len);
  //     str = stpcpy(str, " ");
  //   }
  //   str = stpcpy(str, ".");
  //   *str = '\0';
  // }
};
