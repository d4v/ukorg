#ifndef PROGRAM_DUMP_H
#define PROGRAM_DUMP_H

#include "SysEx.h"

namespace ukorg {

class ProgramDump : public SysEx {
public:
  ProgramDump(void*);
  virtual ~ProgramDump();

  virtual void action();

  void print();

private:
  typedef struct _ProgMsg ProgMsg;
  typedef struct _SynthParams SynthParams;

  ProgMsg     *progMsg;
  SynthParams *synthParams1;
  SynthParams *synthParams2;
};

} // namespace ukorg

#endif // PROGRAM_DUMP_H
