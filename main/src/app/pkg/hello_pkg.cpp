#include "hello_pkg.h"

#include <assert.h>

namespace pkg {

HelloPkg::HelloPkg(uint8_t *raw_pkg) : BasePkg(PkgType::Input) {
  assert(raw_pkg[0] == 0);
}

HelloPkg::HelloPkg() : BasePkg(PkgType::Input) {}

std::unique_ptr<uint8_t *> HelloPkg::gen_pkg() {
  auto pkg = std::make_unique<uint8_t *>();

  return pkg;
}

} // namespace pkg