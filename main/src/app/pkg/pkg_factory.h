#ifndef DRONE_SRC_APP_PKG_PKG_FACTORY
#define DRONE_SRC_APP_PKG_PKG_FACTORY

#include <inttypes.h>
#include <unordered_map>

#include "adjust_pkg.h"
#include "base_pkg.h"
#include "hello_pkg.h"
#include "input_pkg.h"

namespace pkg {

std::unique_ptr<BasePkg> parse_pkg(uint8_t *raw_pkg) {
  PkgHeader header(raw_pkg);
  uint8_t *rest_pkg = raw_pkg + HEADER_SIZE;
  if (header.pkg_type == PkgType::Hello) {
    return std::unique_ptr<BasePkg>(new HelloPkg(rest_pkg));
  } else if (header.pkg_type == PkgType::Input) {
    return std::unique_ptr<BasePkg>(new InputPkg(rest_pkg));
  } else if (header.pkg_type == PkgType::RotationShift) {
    return std::unique_ptr<BasePkg>(new RotationShiftPkg(rest_pkg));
  } else if (header.pkg_type == PkgType::Multiplier) {
    return std::unique_ptr<BasePkg>(new MultiplierPkg(rest_pkg));
  } else if (header.pkg_type == PkgType::ThresholdShift) {
    return std::unique_ptr<BasePkg>(new ThresholdShiftPkg(rest_pkg));
  }
  return std::unique_ptr<BasePkg>(nullptr);
}

template <class T, class... Args>
std::unique_ptr<uint8_t[]> gen_pkg(Args... args) {
  static_assert(std::is_base_of<BasePkg, T>::value,
                "T must derive from pkg::BasePkg");

  auto full_buf = std::make_unique<uint8_t[]>(MAX_TOTAL_SIZE);
  PkgHeader header(T::PKG_TYPE);
  header.gen_pkg(full_buf.get());
  auto pkg_buf = full_buf.get() + HEADER_SIZE;

  T pkg(args...);
  pkg.gen_pkg(pkg_buf);

  return full_buf;
}

} // namespace pkg

#endif
