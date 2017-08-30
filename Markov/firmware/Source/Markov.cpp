
class MarkovChain {
  Entry entries[256];

  void learn(const char* text);
  const char* generate();
};

class Token {
public:
  char* str;
  size_t len;
};

template<uint16_t SIZE>
class Entry : public Token {
public:
  Entry* successor[SIZE];
  uint16_t count;
  uint16_t next;
  void addSuccessor(Entry* other, uint16_t limit){
    successor[next++] = other;
    if(next >= SIZE)
      next = 0;
    if(++count >= limit)
      count = limit;
  }
  Entry* getNextEntry(float p){
    uint16_t index = next - p*count;
    return successor[index % SIZE];
  }
  void reset(){
    count = 0;
  }
  bool matches(Token* other){
    return len == other->len && strcasencmp(str, other->str, len) == 0;
  }
};
