#ifndef __OscSender_h__
#define __OscSender_h__

#include "OscMessage.hpp"

class OscSender {
public:
  enum OscMessageId {
    STATUS = 0,
    CV_A,
    CV_B,
    TRIGGER_A,
    TRIGGER_B,
    MESSAGE_COUNT
  };
  OscMessage messages[MESSAGE_COUNT];

  OscSender(){
    messages[STATUS].setAddress("/status");
    messages[STATUS].addString();
    //    messages[CV_A].setAddress(OscCmd_a_cv "/out");
    messages[CV_A].setAddress("/a/cv");
    messages[CV_A].addFloat(.0f);
    //    messages[CV_B].setAddress(OscCmd_b_cv);
    messages[CV_B].setAddress("/b/cv");
    messages[CV_B].addFloat(.0f);
    //    messages[TRIGGER_A].setAddress(OscCmd_a_trigger);
    messages[TRIGGER_A].setAddress("/a/tr");
    messages[TRIGGER_A].addInt(0);
    //    messages[TRIGGER_B].setAddress(OscCmd_b_trigger);
    messages[TRIGGER_B].setAddress("/b/tr");
    messages[TRIGGER_B].addInt(0);
    // osc_status_msg.addString();
    // osc_a_cv_msg.addFloat(.0f);
    // osc_b_cv_msg.addFloat(.0f);
    // osc_a_trigger_msg.addInt(0);
    // osc_b_trigger_msg.addInt(0);
  // note_on_msg.add((int32_t)0);
  // note_on_msg.add((int32_t)0);
  // note_on_msg.add((int32_t)0);
  // note_off_msg.add((int32_t)0);
  // note_off_msg.add((int32_t)0);
  // control_change_msg.add((int32_t)0);
  // control_change_msg.add((int32_t)0);
  // control_change_msg.add((int32_t)0);
  // pitch_bend_msg.add((int32_t)0);
  // pitch_bend_msg.add((int32_t)0);
  }

  void setAddress(OscMessageId mid, char* address){
    if(mid < MESSAGE_COUNT)
      messages[mid].setAddress(address);
  }

  char* getAddress(OscMessageId mid){
    if(mid < MESSAGE_COUNT)
      return messages[mid].getAddress();
    return NULL;
  }

  void send(OscMessageId mid, int value);
  void send(OscMessageId mid, float value);
  void send(OscMessageId mid, const char* value);
};

#endif /* __OscSender_h__ */
