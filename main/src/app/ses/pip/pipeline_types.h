#ifndef DRONE_SRC_APP_SES_PIP_PIPELINE_TYPES
#define DRONE_SRC_APP_SES_PIP_PIPELINE_TYPES

#include "../../pkg/input_pkg.h"

namespace pip {

struct Input {
  // InputPkg values
  bool motors_on;
  short throttle;
  short rotation_y;
  short rotation_z;
  short rotation_x;

  // Additional values
  bool panic;

  Input(pkg::InputPkg in) {
    motors_on = in.motors_on;
    throttle = in.throttle;
    rotation_y = in.rotation_y;
    rotation_z = in.rotation_z;
    rotation_x = in.rotation_x;
  }
};

struct Output {
  // Direct motor values
  short fl_motor;
  short fr_motor;
  short bl_motor;
  short br_motor;
};

class IInputProcessor {
public:
  virtual bool process(Input &in) = 0;
};

class IConverter {
public:
  virtual void convert(Input &in, Output &out) = 0;
};

class IOutputProcessor {
public:
  virtual bool process(Output &out) = 0;
};

} // namespace pip

#endif