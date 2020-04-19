#ifndef DRONE_SRC_APP_PKG_ADJUST_PKG
#define DRONE_SRC_APP_PKG_ADJUST_PKG

#include <inttypes.h>
#include <memory>

#include "base_pkg.h"

namespace pkg {

class RotationShiftPkg : public BasePkg {
public:
  static const uint8_t PKG_SIZE = 6;

  const int16_t rotation_x_shift;
  const int16_t rotation_y_shift;
  const int16_t rotation_z_shift;

  RotationShiftPkg(uint8_t *raw_pkg);

  RotationShiftPkg(int16_t rotation_x_shift, int16_t rotation_y_shift,
                   int16_t rotation_z_shift);

  void gen_pkg(uint8_t *buf) override;
};

class MultiplierPkg : public BasePkg {
public:
  static const uint8_t PKG_SIZE = 2;

  const uint8_t input_multi;
  const uint8_t rotation_multi;

  MultiplierPkg(uint8_t *raw_pkg);

  MultiplierPkg(uint8_t input_multi, uint8_t rotation_multi);

  void gen_pkg(uint8_t *buf) override;
};

class ThresholdShiftPkg : public BasePkg {
public:
  static const uint8_t PKG_SIZE = 2;

  const int16_t throttle_threshold;

  ThresholdShiftPkg(uint8_t *raw_pkg);

  ThresholdShiftPkg(int16_t throttle_threshold);

  void gen_pkg(uint8_t *buf) override;
};

} // namespace pkg

#endif