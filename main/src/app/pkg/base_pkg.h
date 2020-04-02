#ifndef DRONE_PKG_SRC_PKG_BASE_PKG
#define DRONE_PKG_SRC_PKG_BASE_PKG

#include <inttypes.h>

namespace pkg {

enum class PkgType {
  Hello = 0,
  Bye = 1,
  Input = 2,
};

class BasePkg {
public:
  const PkgType pkg_type;
  BasePkg(PkgType pkg_type) : pkg_type(pkg_type) {}
};

static constexpr uint8_t MAX_PKG_SIZE = 10;

} // namespace pkg

#endif