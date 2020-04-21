#include "hello_pkg.h"

#include <assert.h>

namespace pkg {

HelloPkg::HelloPkg(uint8_t *raw_pkg) : BasePkg(PkgType::Input) {
  assert(raw_pkg[0] == 0);
}

HelloPkg::HelloPkg() : BasePkg(PkgType::Input) {}

void HelloPkg::gen_pkg(uint8_t *pkg) {}

} // namespace pkg