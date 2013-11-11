#ifndef SYSTEM_EXCLUSIVE_H
#define SYSTEM_EXCLUSIVE_H

namespace ukorg {

class SysEx {
public:
  virtual ~SysEx() {}

  virtual void action() = 0;
};

}

#endif // SYSTEM_EXCLUSIVE_H
