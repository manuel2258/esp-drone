#include "adjust_pkg.h"

#include <assert.h>

namespace pkg {

const uint8_t RotationShiftPkg::PKG_SIZE;

RotationShiftPkg::RotationShiftPkg(uint8_t *raw_pkg)
    : BasePkg(PkgType::RotationShift),
      rotation_x_shift(raw_pkg[0] << 8 | raw_pkg[1]),
      rotation_y_shift(raw_pkg[2] << 8 | raw_pkg[3]),
      rotation_z_shift(raw_pkg[4] << 8 | raw_pkg[5]) {}

RotationShiftPkg::RotationShiftPkg(int16_t rotation_x_shift,
                                   int16_t rotation_y_shift,
                                   int16_t rotation_z_shift)
    : BasePkg(PkgType::RotationShift), rotation_x_shift(rotation_x_shift),
      rotation_y_shift(rotation_y_shift), rotation_z_shift(rotation_z_shift) {}

void RotationShiftPkg::gen_pkg(uint8_t *pkg) {
  pkg[0] = rotation_x_shift >> 8;
  pkg[1] = (rotation_x_shift << 8) >> 8;

  pkg[2] = rotation_y_shift >> 8;
  pkg[3] = (rotation_y_shift << 8) >> 8;

  pkg[4] = rotation_z_shift >> 8;
  pkg[5] = (rotation_z_shift << 8) >> 8;
}

const uint8_t MultiplierPkg::PKG_SIZE;

MultiplierPkg::MultiplierPkg(uint8_t *raw_pkg)
    : BasePkg(PkgType::Multiplier), input_multi(raw_pkg[0]),
      rotation_multi(raw_pkg[1]) {}

MultiplierPkg::MultiplierPkg(uint8_t input_multi, uint8_t rotation_multi)
    : BasePkg(PkgType::Multiplier), input_multi(input_multi),
      rotation_multi(rotation_multi) {}

void MultiplierPkg::gen_pkg(uint8_t *pkg) {
  pkg[0] = input_multi;
  pkg[1] = rotation_multi;
}

const uint8_t ThresholdShiftPkg::PKG_SIZE;

ThresholdShiftPkg::ThresholdShiftPkg(uint8_t *raw_pkg)
    : BasePkg(PkgType::Multiplier),
      throttle_threshold(raw_pkg[0] << 8 | raw_pkg[1]) {}

ThresholdShiftPkg::ThresholdShiftPkg(int16_t throttle_threshold)
    : BasePkg(PkgType::Multiplier), throttle_threshold(throttle_threshold) {}

void ThresholdShiftPkg::gen_pkg(uint8_t *pkg) {
  pkg[0] = throttle_threshold >> 8;
  pkg[1] = (throttle_threshold << 8) >> 8;
}

} // namespace pkg