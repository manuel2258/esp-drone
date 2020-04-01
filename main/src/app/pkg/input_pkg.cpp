#include "input_pkg.h"

#include <assert.h>

namespace pkg {

InputPkg::InputPkg(std::array<uint8_t, 10> &raw_pkg)
    : motors_on((raw_pkg[1] << 7) >> 7), throttle(raw_pkg[2] << 8 | raw_pkg[3]),
      rotation_y(raw_pkg[4] << 8 | raw_pkg[5]),
      rotation_z(raw_pkg[6] << 8 | raw_pkg[7]),
      rotation_x(raw_pkg[8] << 8 | raw_pkg[9]) {
  assert(raw_pkg[0] == 1);
}

InputPkg::InputPkg(bool motors_on, short throttle, short rotation_y,
                   short rotation_z, short rotation_x)
    : motors_on(motors_on), throttle(throttle), rotation_y(rotation_y),
      rotation_z(rotation_z), rotation_x(rotation_x) {}

std::unique_ptr<std::array<uint8_t, 10>> InputPkg::gen_pkg() {
  auto pkg = std::make_unique<std::array<uint8_t, 10>>();

  (*pkg)[0] = 1;
  (*pkg)[1] = motors_on ? 1 : 0;

  (*pkg)[2] = throttle >> 8;
  (*pkg)[3] = (throttle << 8) >> 8;

  (*pkg)[4] = rotation_y >> 8;
  (*pkg)[5] = (rotation_y << 8) >> 8;

  (*pkg)[6] = rotation_z >> 8;
  (*pkg)[7] = (rotation_z << 8) >> 8;

  (*pkg)[8] = rotation_x >> 8;
  (*pkg)[9] = (rotation_x << 8) >> 8;

  return pkg;
}

} // namespace pkg