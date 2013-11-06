#include <string.h>
#include <iostream>
#include "SysExEvent.h"
#include "SysExCodec.h"
#include "ProgramDump.h"

using namespace std;
using namespace ukorg;

SysExEvent::SysExEvent() : 
 mSize(1), // First header byte must be 0xF0
 mSysExMsgIdx(0),
 mBufIdx(0),
 mbReady(false) {
  memset(mHeader,0,mHeaderSize);
  memset(mBuf,0,mBufSize);
  memset(mSysExMsg,0,mSysExMsgSize);
  
  mHeader[0] = 0xF0;
}

void SysExEvent::addData(const unsigned char c) {
  mBuf[mBufIdx++] = c;
  if(mBufIdx == 8) {
    SysExCodec::decode(mBuf,mSysExMsg + mSysExMsgIdx,&mSysExMsgIdx);
    mBufIdx = 0;
    memset(mBuf,0,mBufSize);
  }
}

void SysExEvent::finish() {
  if(mBufIdx > 1) {
    SysExCodec::decode(mBuf,mSysExMsg + mSysExMsgIdx,&mSysExMsgIdx);
  }

  mbReady = true;
}

#define END_OF_EXCLUSIVE 0xF7

void SysExEvent::cat(const unsigned char c) {
  cout << "SysExEvent::cat, c:" << hex << (int)c << endl;
  if(mSize < 4) {
    mHeader[mSize] = c;
  } else
  if(mSize == 4) {
    mStatus = c;
    // Midi channel goes from 1 (0x30) to 16 (0x3F)
    mChannel = mHeader[2] - 0x29; 
  } else
  if(c == END_OF_EXCLUSIVE) {
    finish();
  } else
    addData(c);

  mSize++;
}
  
bool SysExEvent::ready() {
  return mbReady;
}

void SysExEvent::action() {
  cout << "SysExEvent, status : " << hex << (int) mStatus;
  cout << " on channel : " << mChannel << endl;
  ProgramDump progDump;
  progDump.init(mSysExMsg);

}

