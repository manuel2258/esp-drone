#ifndef DRONE_SRC_APP_PKG_PKG_FACTORY
#define DRONE_SRC_APP_PKG_PKG_FACTORY

#include <inttypes.h>

#include "base_pkg.h"
#include "hello_pkg.h"
#include "input_pkg.h"

namespace pkg {

std::unique_ptr<BasePkg> parse_pkg(std::array<uint8_t, 10> &raw_pkg) {
  if (raw_pkg[0] == 0) {
    return std::unique_ptr<BasePkg>(new HelloPkg(raw_pkg));
  } else {
    return std::unique_ptr<BasePkg>(new InputPkg(raw_pkg));
  }
}

} // namespace pkg

#endif
