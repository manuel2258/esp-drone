#ifndef DRONE_SRC_APP_SES_PIP_INPUT_PROCESSORS
#define DRONE_SRC_APP_SES_PIP_INPUT_PROCESSORS

#include "pipeline_types.h"

namespace pip {

class InputShifter : public IInputProcessor {
public:
  bool process(Input &in) override;
};

class InputMultiplier : public IInputProcessor {
public:
  bool process(Input &in) override;
};

class DefaultConverter : public IConverter {
public:
  void convert(Input &in, Output &out) override;
};

} // namespace pip

#endif