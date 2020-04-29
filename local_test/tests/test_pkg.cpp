#include "app/pkg/adjust_pkg.h"
#include "app/pkg/input_pkg.h"
#include "app/pkg/pkg_factory.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(hellopkg_suite)

BOOST_AUTO_TEST_CASE(pkgfactorygen_simple) {
  uint8_t want[pkg::MAX_TOTAL_SIZE] = {(uint8_t)pkg::PkgType::Hello};

  auto sut = pkg::gen_pkg<pkg::HelloPkg>();

  auto have = sut.get();

  for (int i = 0; i < pkg::HelloPkg::PKG_SIZE + 1; i++) {
    BOOST_CHECK_EQUAL(want[i], have[i]);
  }
}

BOOST_AUTO_TEST_CASE(pkgfactoryparse_simple) {
  uint8_t have[pkg::MAX_TOTAL_SIZE] = {(uint8_t)pkg::PkgType::Hello};

  auto sut = pkg::parse_pkg(have);

  BOOST_CHECK_EQUAL((uint8_t)sut->pkg_type, (uint8_t)pkg::PkgType::Hello);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(inputpkg_suite)

BOOST_AUTO_TEST_CASE(bufferparse_simple) {
  uint8_t buf[pkg::MAX_PKG_SIZE] = {128, 3, 6, 2, 255, 255, 2, 3};
  pkg::InputPkg sut(buf);

  BOOST_CHECK_EQUAL(-32765, sut.throttle);
  BOOST_CHECK_EQUAL(1538, sut.rotation_x);
  BOOST_CHECK_EQUAL(-1, sut.rotation_y);
  BOOST_CHECK_EQUAL(515, sut.rotation_z);
}

BOOST_AUTO_TEST_CASE(bufferparse_zero) {
  uint8_t buf[pkg::MAX_PKG_SIZE] = {0, 0, 0, 0, 0, 0, 0, 0};
  pkg::InputPkg sut(buf);

  BOOST_CHECK_EQUAL(0, sut.throttle);
  BOOST_CHECK_EQUAL(0, sut.rotation_y);
  BOOST_CHECK_EQUAL(0, sut.rotation_z);
  BOOST_CHECK_EQUAL(0, sut.rotation_x);
}

BOOST_AUTO_TEST_CASE(buffergen_simple) {
  uint8_t want[pkg::MAX_PKG_SIZE] = {128, 3, 6, 2, 255, 255, 2, 3};

  pkg::InputPkg sut(-32765, 1538, -1, 515);

  uint8_t have[pkg::MAX_PKG_SIZE];
  sut.gen_pkg(have);

  for (int i = 0; i < pkg::InputPkg::PKG_SIZE; i++) {
    BOOST_CHECK_EQUAL(want[i], have[i]);
  }
}

BOOST_AUTO_TEST_CASE(buffergen_zero) {
  uint8_t want[pkg::MAX_PKG_SIZE] = {0, 0, 0, 0, 0, 0, 0, 0};

  pkg::InputPkg sut(0, 0, 0, 0);

  uint8_t have[pkg::MAX_PKG_SIZE];
  sut.gen_pkg(have);

  for (int i = 0; i < pkg::InputPkg::PKG_SIZE; i++) {
    BOOST_CHECK_EQUAL(want[i], have[i]);
  }
}

BOOST_AUTO_TEST_CASE(pkgfactorygen_simple) {
  uint8_t want[pkg::MAX_TOTAL_SIZE] = {
      (uint8_t)pkg::PkgType::Input, 128, 3, 6, 2, 255, 255, 2, 3};

  auto sut = pkg::gen_pkg<pkg::InputPkg>(-32765, 1538, -1, 515);

  auto have = sut.get();

  for (int i = 0; i < pkg::InputPkg::PKG_SIZE + 1; i++) {
    BOOST_CHECK_EQUAL(want[i], have[i]);
  }
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(rotationshiftpkg_suite)

BOOST_AUTO_TEST_CASE(bufferparse_simple) {
  uint8_t buf[pkg::MAX_PKG_SIZE] = {128, 3, 6, 2, 255, 255};
  pkg::RotationShiftPkg sut(buf);

  BOOST_CHECK_EQUAL(-32765, sut.rotation_x_shift);
  BOOST_CHECK_EQUAL(1538, sut.rotation_y_shift);
  BOOST_CHECK_EQUAL(-1, sut.rotation_z_shift);
}

BOOST_AUTO_TEST_CASE(bufferparse_zero) {
  uint8_t buf[pkg::MAX_PKG_SIZE] = {0, 0, 0, 0, 0, 0};
  pkg::RotationShiftPkg sut(buf);

  BOOST_CHECK_EQUAL(0, sut.rotation_x_shift);
  BOOST_CHECK_EQUAL(0, sut.rotation_y_shift);
  BOOST_CHECK_EQUAL(0, sut.rotation_z_shift);
}

BOOST_AUTO_TEST_CASE(buffergen_simple) {
  uint8_t want[pkg::MAX_PKG_SIZE] = {128, 3, 6, 2, 255, 255};

  pkg::RotationShiftPkg sut(-32765, 1538, -1);

  uint8_t have[pkg::MAX_PKG_SIZE];
  sut.gen_pkg(have);

  for (int i = 0; i < pkg::RotationShiftPkg::PKG_SIZE; i++) {
    BOOST_CHECK_EQUAL(want[i], have[i]);
  }
}

BOOST_AUTO_TEST_CASE(buffergen_zero) {
  uint8_t want[pkg::MAX_PKG_SIZE] = {0, 0, 0, 0, 0, 0};

  pkg::RotationShiftPkg sut(0, 0, 0);

  uint8_t have[pkg::MAX_PKG_SIZE];
  sut.gen_pkg(have);

  for (int i = 0; i < pkg::RotationShiftPkg::PKG_SIZE; i++) {
    BOOST_CHECK_EQUAL(want[i], have[i]);
  }
}

BOOST_AUTO_TEST_CASE(pkgfactorygen_simple) {
  uint8_t want[pkg::MAX_TOTAL_SIZE] = {
      (uint8_t)pkg::PkgType::RotationShift, 128, 3, 6, 2, 255, 255};

  auto sut = pkg::gen_pkg<pkg::RotationShiftPkg>(-32765, 1538, -1);

  auto have = sut.get();

  for (int i = 0; i < pkg::RotationShiftPkg::PKG_SIZE + 1; i++) {
    BOOST_CHECK_EQUAL(want[i], have[i]);
  }
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(multiplierpkg_suite)

BOOST_AUTO_TEST_CASE(bufferparse_simple) {
  uint8_t buf[pkg::MAX_PKG_SIZE] = {128, 255};
  pkg::MultiplierPkg sut(buf);

  BOOST_CHECK_EQUAL(128, sut.input_multi);
  BOOST_CHECK_EQUAL(255, sut.rotation_multi);
}

BOOST_AUTO_TEST_CASE(bufferparse_zero) {
  uint8_t buf[pkg::MAX_PKG_SIZE] = {0, 0};
  pkg::MultiplierPkg sut(buf);

  BOOST_CHECK_EQUAL(0, sut.input_multi);
  BOOST_CHECK_EQUAL(0, sut.rotation_multi);
}

BOOST_AUTO_TEST_CASE(buffergen_simple) {
  uint8_t want[pkg::MAX_PKG_SIZE] = {128, 255};

  pkg::MultiplierPkg sut(128, 255);

  uint8_t have[pkg::MAX_PKG_SIZE];
  sut.gen_pkg(have);

  for (int i = 0; i < pkg::MultiplierPkg::PKG_SIZE; i++) {
    BOOST_CHECK_EQUAL(want[i], have[i]);
  }
}

BOOST_AUTO_TEST_CASE(buffergen_zero) {
  uint8_t want[pkg::MAX_PKG_SIZE] = {0, 0};

  pkg::MultiplierPkg sut(0, 0);

  uint8_t have[pkg::MAX_PKG_SIZE];
  sut.gen_pkg(have);

  for (int i = 0; i < pkg::MultiplierPkg::PKG_SIZE; i++) {
    BOOST_CHECK_EQUAL(want[i], have[i]);
  }
}

BOOST_AUTO_TEST_CASE(pkgfactorygen_simple) {
  uint8_t want[pkg::MAX_TOTAL_SIZE] = {(uint8_t)pkg::PkgType::Multiplier, 128,
                                       255};

  auto sut = pkg::gen_pkg<pkg::MultiplierPkg>(128, 255);

  auto have = sut.get();

  for (int i = 0; i < pkg::MultiplierPkg::PKG_SIZE + 1; i++) {
    BOOST_CHECK_EQUAL(want[i], have[i]);
  }
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(thresholdshiftpkg_suite)

BOOST_AUTO_TEST_CASE(bufferparse_simple) {
  uint8_t buf[pkg::MAX_PKG_SIZE] = {128, 3};
  pkg::ThresholdShiftPkg sut(buf);

  BOOST_CHECK_EQUAL(-32765, sut.throttle_threshold);
}

BOOST_AUTO_TEST_CASE(bufferparse_zero) {
  uint8_t buf[pkg::MAX_PKG_SIZE] = {0, 0};
  pkg::ThresholdShiftPkg sut(buf);

  BOOST_CHECK_EQUAL(0, sut.throttle_threshold);
}

BOOST_AUTO_TEST_CASE(buffergen_simple) {
  uint8_t want[pkg::MAX_PKG_SIZE] = {128, 3};

  pkg::ThresholdShiftPkg sut(-32765);

  uint8_t have[pkg::MAX_PKG_SIZE];
  sut.gen_pkg(have);

  for (int i = 0; i < pkg::ThresholdShiftPkg::PKG_SIZE; i++) {
    BOOST_CHECK_EQUAL(want[i], have[i]);
  }
}

BOOST_AUTO_TEST_CASE(buffergen_zero) {
  uint8_t want[pkg::MAX_PKG_SIZE] = {0, 0};

  pkg::ThresholdShiftPkg sut((int16_t)0);

  uint8_t have[pkg::MAX_PKG_SIZE];
  sut.gen_pkg(have);

  for (int i = 0; i < pkg::ThresholdShiftPkg::PKG_SIZE; i++) {
    BOOST_CHECK_EQUAL(want[i], have[i]);
  }
}

BOOST_AUTO_TEST_CASE(pkgfactorygen_simple) {
  uint8_t want[pkg::MAX_TOTAL_SIZE] = {(uint8_t)pkg::PkgType::ThresholdShift,
                                       128, 3};

  auto sut = pkg::gen_pkg<pkg::ThresholdShiftPkg>(-32765);

  auto have = sut.get();

  for (int i = 0; i < pkg::ThresholdShiftPkg::PKG_SIZE + 1; i++) {
    BOOST_CHECK_EQUAL(want[i], have[i]);
  }
}

BOOST_AUTO_TEST_SUITE_END()