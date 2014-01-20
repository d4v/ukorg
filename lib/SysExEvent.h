#ifndef SYSEX_EVENT_H
#define SYSEX_EVENT_H

#include "stdlib.h"
#include "MidiEvent.h"

namespace ukorg {

class SysEx;

class SysExEvent : public MidiEvent {
 
public:
  SysExEvent();
  virtual ~SysExEvent() {}

  virtual void cat(const unsigned char);

  virtual bool ready();

  virtual void action();

  void finish();

  void addData(const unsigned char);

private:
  // System exclusive msg header
  static const size_t mHeaderSize = 4;
  unsigned char mHeader[mHeaderSize];

  // Received event size
  size_t mSize;

  // Event status (= type)
  unsigned char mStatus;

  // Event channel
  unsigned int mChannel;

  // System exclusive decoded msg
  static const size_t mSysExMsgSize = 37888; // 32Ko
  unsigned char mSysExMsg[mSysExMsgSize];
  unsigned int  mSysExMsgIdx;

  // System exclusive encoded msg chunk
  static const size_t mBufSize = 8;
  unsigned char mBuf[mBufSize];
  unsigned int  mBufIdx;

  // Event ready to be actionned
  bool mbReady;

  int mDataCount;

  SysEx *mSysEx;
};

} // namespace ukorg

#endif // SYSEX_EVENT_H
