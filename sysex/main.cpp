#include <fcntl.h>
#include <string.h>
#include <iostream>

/**
 * MIDI data converter
 *
 * Explanations from "micro KORG MIDI Implementation" Revision 1.4 (2002.06.27)
 *
 *
 * DATA ( 1set = 8bit x 7Byte )
 * b7      ~     b0   b7      ~     b0   b7     ~~      b0   b7     ~      b0
 * +-+-+-+-+-+-+-+-+  +-+-+-+-+-+-+-+-+  +-+-+-+-~~-+-+-+-+  +-+-+-+-+-+-+-+-+
 * | | | | | | | | |  | | | | | | | | |  | | | |    | | | |  | | | | | | | | |
 * +-+-+-+-+-+-+-+-+  +-+-+-+-+-+-+-+-+  +-+-+-+-~~-+-+-+-+  +-+-+-+-+-+-+-+-+
 *       7n+0               7n+1          7n+2   ~~   7n+5        7n+6
 *
 * MIDI DATA ( 1set = 7bit x 8Byte )
 *    b7b7b7b7b7b7b7     b6    ~     b0     b6   ~~~     b0     b6    ~     b0
 * +-+-+-+-+-+-+-+-+  +-+-+-+-+-+-+-+-+  +-+-+-+-~~-+-+-+-+  +-+-+-+-+-+-+-+-+
 * |0| | | | | | | |  |0| | | | | | | |  |0| | |    | | | |  |0| | | | | | | |
 * +-+-+-+-+-+-+-+-+  +-+-+-+-+-+-+-+-+  +-+-+-+-~~-+-+-+-+  +-+-+-+-+-+-+-+-+
 * 7n+6,5,4,3,2,1,0         7n+0          7n+1  ~~~  7n+5          7n+6
 *
 */

using namespace std;

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

void toMidi(unsigned char * buf_out,
            unsigned const char * buf_in, size_t size) {
  /* Initilize out buffer */
  memset(buf_out,0,8);

  /* First byte gathers the 7 following bytes first bit*/
  unsigned char *firstByte = buf_out;
  *firstByte = 0x00;

  /* First bit mask */
  static const char firstBit = 0x80; /* 1000 0000 */

  /* Byte to byte treatment */
  int max = size < 7 ? size : 7;
  for(int idx = 0; idx < max; idx++) {
    /* Get current byte first bit */
    unsigned char tmpByte = buf_in[idx] & firstBit;
    if(tmpByte) {
      /* First bit is 1 */
      tmpByte >>= idx+1;
      /* Set first byte corresponding bit */
      *firstByte |= tmpByte;
      /* Set the 6 others bits in the out chunk */
      buf_out[idx+1] = buf_in[idx] & ~firstBit;
    } else {
      /* First bit is 0 */
      /* Just put the byte at its place in out_buf */
      buf_out[idx+1] = buf_in[idx];
    }
  }
}

void dumpChunk(const unsigned char * chunk, size_t nb) {
  for(int idx = 0; idx < nb; idx++) {
    cout << bitdump(chunk[idx]) << "  ";
  }
  cout << endl;
}

int main(int argc, char* argv[]) {

  unsigned char c;

  int data_in = open("data", O_RDONLY);
  int data_midi = open("data_midi", O_WRONLY);

  static const size_t chunkSize = 7;

  int nbRead = 0;
  unsigned char buf_in[chunkSize];
  memset(buf_in,0,chunkSize);
  while((nbRead = read(data_in,buf_in,chunkSize)) > 0) {
    unsigned char buf_out[8];
    toMidi(buf_out,buf_in,nbRead);
    dumpChunk(buf_in,chunkSize);
    dumpChunk(buf_out,8);
    memset(buf_in,0,chunkSize);
  }

  return 0;
}

