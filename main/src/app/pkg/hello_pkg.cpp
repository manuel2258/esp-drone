#include "hello_pkg.h"

#include <assert.h>

namespace pkg {

HelloPkg::HelloPkg(std::array<uint8_t, MAX_PKG_SIZE> &raw_pkg)
    : BasePkg(PkgType::Input) {
  assert(raw_pkg[0] == 0);
}

HelloPkg::HelloPkg() : BasePkg(PkgType::Input) {}

std::unique_ptr<std::array<uint8_t, MAX_PKG_SIZE>> HelloPkg::gen_pkg() {
  auto pkg = std::make_unique<std::array<uint8_t, MAX_PKG_SIZE>>();

  return pkg;
}

} // namespace pkg