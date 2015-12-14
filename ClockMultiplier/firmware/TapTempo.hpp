#ifndef __TapTempo_hpp__
#define __TapTempo_hpp__

template<int TRIGGER_LIMIT>
class TapTempo {
private:
  uint16_t limit;
  uint16_t trig;
  uint16_t speed;
  bool ison;
public:
  TapTempo(uint32_t tempo) : 
    limit(tempo), trig(TRIGGER_LIMIT), 
    speed(2048), ison(false) {}
  void trigger(bool on){
    trigger(on, 0);
  }
  void trigger(bool on){
    // if(trig < TAP_THRESHOLD)
    //   return;
    if(on && !ison){
      if(trig < TRIGGER_LIMIT){
	limit = trig;
      }
      trig = 0;
    }
    ison = on;
  }
  void setSpeed(int16_t s){
    if(abs(speed-s) > 16){
      int64_t delta = (int64_t)limit*(speed-s)/2048;
      limit = max(1, limit+delta);
      speed = s;
    }
  }
  uint16_t getPeriod(){
    return limit;
  }
  void clock(){
    if(trig < TRIGGER_LIMIT)
      trig++;
  }
  void clock(uint32_t steps){
    trig += steps;
    if(trig > TRIGGER_LIMIT)
      trig = TRIGGER_LIMIT;
  }
};

#endif   // __TapTempo_hpp__
