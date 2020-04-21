#ifndef DRONE_PKG_SRC_PKG_BASE_PKG
#define DRONE_PKG_SRC_PKG_BASE_PKG

#include <inttypes.h>

namespace pkg {

enum class PkgType : uint8_t {
  Hello = 0,
  Bye = 1,
  Input = 2,
  RotationShift = 3,
  Multiplier = 4,
  ThresholdShift = 5
};

class BasePkg {
public:
  const PkgType pkg_type;
  BasePkg(PkgType pkg_type) : pkg_type(pkg_type) {}

  virtual void gen_pkg(uint8_t *) = 0;
};

class PkgHeader : public BasePkg {
public:
  PkgHeader(uint8_t *pkg) : BasePkg(static_cast<PkgType>(pkg[0])) {}
  PkgHeader(PkgType pkg_type) : BasePkg(pkg_type) {}

  void gen_pkg(uint8_t *pkg) override { pkg[0] = (uint8_t)pkg_type; }
};

static constexpr uint8_t HEADER_SIZE = 1;
static constexpr uint8_t MAX_PKG_SIZE = 8;

static constexpr uint8_t MAX_TOTAL_SIZE = HEADER_SIZE + MAX_PKG_SIZE;

} // namespace pkg

#endif