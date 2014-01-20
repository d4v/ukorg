#ifndef CODEC_H
#define CODEC_H

namespace ukorg {

void toMidi(unsigned char * buf_out,
            unsigned const char * buf_in, size_t size);

void fromMidi(unsigned char * buf_out,
              unsigned const char * buf_in, size_t size);
 
}



#endif // CODEC_H
