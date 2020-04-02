#ifndef DRONE_PKG_SRC_PKG_HELLO_PKG
#define DRONE_PKG_SRC_PKG_HELLO_PKG

#include <array>
#include <inttypes.h>
#include <memory>

#include "base_pkg.h"

namespace pkg {

/**
 * @brief Represents a hello package
 */
class HelloPkg : public BasePkg {

  // API to generate a pkg object from a buffer
public:
  HelloPkg(std::array<uint8_t, MAX_PKG_SIZE> &raw_pkg);

  // API to generate a buffer from pkg object
public:
  HelloPkg();

  /**
   * @brief Generates a buffer from the current pkg's fields
   * @return std::unique_ptr<std::array<uint8_t, 5>> The generated buffer
   */
  std::unique_ptr<std::array<uint8_t, MAX_PKG_SIZE>> gen_pkg();
};
} // namespace pkg

#endif