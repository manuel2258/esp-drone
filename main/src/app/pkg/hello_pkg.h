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
  HelloPkg(uint8_t *raw_pkg);

  // API to generate a buffer from pkg object
public:
  HelloPkg();

  void gen_pkg(uint8_t *pkg) override;
};
} // namespace pkg

#endif