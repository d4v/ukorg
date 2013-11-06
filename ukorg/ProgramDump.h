#ifndef PROGRAM_DUMP_H
#define PROGRAM_DUMP_H

namespace ukorg {

class ProgramDump {
public:
  ProgramDump() {}
  virtual ~ProgramDump() {}
  void init(void *);

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
