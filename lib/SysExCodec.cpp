#include <iostream>
#include <string.h>
#include "SysExCodec.h"

using namespace std;
using namespace ukorg;

namespace ukorg {
string bitdump(const char c) {
  string s;
  unsigned char mask = 0x80; /* 1000 0000 */
  for(int i = 0; i < 2; i++) {
    for(int j = 0; j < 4; j++) {
      if(mask & c)
        s += '1';
      else
        s += '0';

      mask >>= 1;
    }
    if(i == 0)
      s += ' ';
  }
  return s;
}
}

void dumpChunk(const unsigned char * chunk, size_t nb) {
  for(unsigned int idx = 0; idx < nb; idx++) {
    cout << bitdump(chunk[idx]) << "  ";
  }
  cout << endl;
}

void SysExCodec::decode(unsigned char *buf_in,
                        unsigned char *buf_out,
                        unsigned int  *out_idx) {

  /* Initialize out 7 next bytes */
  memset(buf_out,0,7);

  /* First byte gathers the 7 following bytes first bit*/
  unsigned char firstByte = buf_in[0];

  /* First bit mask */
  static const char firstBit = 0x80; /* 1000 0000 */

  /* Byte to byte treatment */
  for(int idx = 7; idx > 0; idx--) {
    /* Get next first bit by shifting the first byte */
    firstByte <<= 1;
    /* Give back its first bit to current byte and set it to output */
    buf_out[idx-1] = buf_in[idx] | (firstByte & firstBit);
  } 

  cout << "MIDI :";
  dumpChunk(buf_in,8);
  cout << "Data :           ";
  dumpChunk(buf_out,7);

  *out_idx += 7;
}



