#ifndef DRONE_PKG_SRC_PKG_INPUT_PKG
#define DRONE_PKG_SRC_PKG_INPUT_PKG

#include <array>
#include <inttypes.h>
#include <memory>

#include "base_pkg.h"

namespace pkg {

/**
 * @brief Represents a input package
 */
class InputPkg : public BasePkg {

  // Public fields
public:
  static const uint8_t PKG_SIZE = 8;

  const int16_t throttle;
  const int16_t rotation_x;
  const int16_t rotation_y;
  const int16_t rotation_z;

  // API to generate a pkg object from a buffer
public:
  InputPkg(uint8_t *raw_pkg);

  // API to generate a buffer from pkg object
public:
  InputPkg(int16_t throttle, int16_t rotation_x, int16_t rotation_y,
           int16_t rotation_z);

  /**
   * @brief Writes pkg data to buffer from the current pkg's fields
   * @param pkg The to append to buffer
   */
  void gen_pkg(uint8_t *pkg) override;
};
} // namespace pkg

#endif