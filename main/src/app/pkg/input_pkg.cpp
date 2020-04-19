#include "input_pkg.h"

#include <assert.h>

namespace pkg {

InputPkg::InputPkg(uint8_t *raw_pkg)
    : BasePkg(PkgType::Input), throttle(raw_pkg[0] << 8 | raw_pkg[1]),
      rotation_x(raw_pkg[2] << 8 | raw_pkg[3]),
      rotation_y(raw_pkg[4] << 8 | raw_pkg[5]),
      rotation_z(raw_pkg[6] << 8 | raw_pkg[7]) {}

InputPkg::InputPkg(int16_t throttle, int16_t rotation_x, int16_t rotation_y,
                   int16_t rotation_z)
    : BasePkg(PkgType::Input), throttle(throttle), rotation_x(rotation_x),
      rotation_y(rotation_y), rotation_z(rotation_z) {}

void InputPkg::gen_pkg(uint8_t *pkg) {
  pkg[0] = throttle >> 8;
  pkg[1] = (throttle << 8) >> 8;

  pkg[2] = rotation_x >> 8;
  pkg[3] = (rotation_x << 8) >> 8;

  pkg[4] = rotation_y >> 8;
  pkg[5] = (rotation_y << 8) >> 8;

  pkg[6] = rotation_z >> 8;
  pkg[7] = (rotation_z << 8) >> 8;
}

} // namespace pkg