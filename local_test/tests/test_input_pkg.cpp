#include "app/pkg/input_pkg.h"

#define BOOST_TEST_MODULE InputPkgTest
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE(bufferparse_simple) {
  std::array<uint8_t, 10> buf = {2, 1, 128, 3, 6, 2, 255, 255, 2, 3};
  pkg::InputPkg sut(buf);

  BOOST_CHECK_EQUAL(sut.motors_on, true);
  BOOST_CHECK_EQUAL(-32765, sut.throttle);
  BOOST_CHECK_EQUAL(1538, sut.rotation_y);
  BOOST_CHECK_EQUAL(-1, sut.rotation_z);
  BOOST_CHECK_EQUAL(515, sut.rotation_x);
}

BOOST_AUTO_TEST_CASE(bufferparse_zero) {
  std::array<uint8_t, 10> buf = {2, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  pkg::InputPkg sut(buf);

  BOOST_CHECK_EQUAL(sut.motors_on, false);
  BOOST_CHECK_EQUAL(0, sut.throttle);
  BOOST_CHECK_EQUAL(0, sut.rotation_y);
  BOOST_CHECK_EQUAL(0, sut.rotation_z);
  BOOST_CHECK_EQUAL(0, sut.rotation_x);
}

BOOST_AUTO_TEST_CASE(buffergen_simple) {
  std::array<uint8_t, 10> want = {2, 1, 128, 3, 6, 2, 255, 255, 2, 3};

  pkg::InputPkg sut(true, -32765, 1538, -1, 515);
  auto have = sut.gen_pkg();

  for (int i = 0; i < 10; i++) {
    BOOST_CHECK_EQUAL(want[i], (*have)[i]);
  }
}

BOOST_AUTO_TEST_CASE(buffergen_zero) {
  std::array<uint8_t, 10> want = {2, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  pkg::InputPkg sut(false, 0, 0, 0, 0);
  auto have = sut.gen_pkg();

  for (int i = 0; i < 10; i++) {
    BOOST_CHECK_EQUAL(want[i], (*have)[i]);
  }
}