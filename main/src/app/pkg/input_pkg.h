#ifndef DRONE_PKG_SRC_PKG_DRONE_PKG
#define DRONE_PKG_SRC_PKG_DRONE_PKG

#include <array>
#include <inttypes.h>
#include <memory>

namespace pkg {

/**
 * @brief Represents a input package
 */
class InputPkg {

  // Public fields
public:
  const bool motors_on;
  const short throttle;
  const short rotation_y;
  const short rotation_z;
  const short rotation_x;

  // API to generate a pkg object from a buffer
public:
  InputPkg(std::array<uint8_t, 10> &raw_pkg);

  // API to generate a buffer from pkg object
public:
  InputPkg(bool motors_on, short throttle, short rotation_y, short rotation_z,
           short rotation_x);

  /**
   * @brief Generates a buffer from the current pkg's fields
   * @return std::unique_ptr<std::array<uint8_t, 5>> The generated buffer
   */
  std::unique_ptr<std::array<uint8_t, 10>> gen_pkg();
};
} // namespace pkg

#endif