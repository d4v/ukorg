#ifndef SYSEX_CODEC_H
#define SYSEX_CODEC_H

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

namespace ukorg {

class SysExCodec {
public:

  /**
   * Decode from midi data to common data
   *
   * @param buf_in 8 chars array
   * @param buf_out output char array
   * @param idx output array idx address
   */
  static void decode(unsigned char *buf_in,
                     unsigned char *buf_out,
                     unsigned int *out_idx);

};

}

#endif // SYSEX_CODEC_H
