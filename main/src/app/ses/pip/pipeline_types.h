#ifndef DRONE_SRC_APP_SES_PIP_PIPELINE_TYPES
#define DRONE_SRC_APP_SES_PIP_PIPELINE_TYPES

#include <inttypes.h>

#include "../../pkg/base_pkg.h"
#include "../../pkg/input_pkg.h"

namespace pip {

struct Input {
  int16_t throttle;

  int16_t rotation_x;
  int16_t rotation_y;
  int16_t rotation_z;

  Input(pkg::InputPkg &net_pkg)
      : throttle(net_pkg.throttle), rotation_x(net_pkg.rotation_x),
        rotation_y(net_pkg.rotation_y), rotation_z(net_pkg.rotation_z) {}

  Input(int16_t throttle, int16_t rotation_x, int16_t rotation_y,
        int16_t rotation_z)
      : throttle(throttle), rotation_x(rotation_x), rotation_y(rotation_y),
        rotation_z(rotation_z) {}

  Input() : throttle(0), rotation_x(0), rotation_y(0), rotation_z(0) {}
};

struct Output {
  // Direct motor values
  uint16_t fl_motor;
  uint16_t fr_motor;
  uint16_t bl_motor;
  uint16_t br_motor;
};

class IInputProcessor {
public:
  virtual ~IInputProcessor() {}
  virtual bool process(Input &in) = 0;
};

class IConverter {
public:
  virtual ~IConverter() {}
  virtual void convert(Input &in, Output &out) = 0;
};

class IOutputProcessor {
public:
  virtual ~IOutputProcessor() {}
  virtual bool process(Output &out) = 0;
};

} // namespace pip

#endif