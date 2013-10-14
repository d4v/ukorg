#include <fcntl.h>
#include <iostream>

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

void toMidi(unsigned char * buf_out, unsigned const char * buf_in, size_t size) {
  memset(buf_out,0,8);
  unsigned char *firstByte = buf_out[0];
  for(int idx = 0; idx < 7; idx++) {


  }
}

void dumpChunk(const char * chunk, size_t nb) {
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
  char buf_in[chunkSize];
  while((nbRead = read(data_in,buf_in,chunkSize)) > 0) {
    char buf_out[8];
    toMidi(buf_out,buf_in,nbRead);
    dumpChunk(buf_in,chunkSize);
    dumpChunk(buf_out,8);
  }

  return 0;
}

