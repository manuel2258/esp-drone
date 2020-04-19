#include "app/ses/pip/pipeline.h"
#include "app/ses/pip/pipeline_types.h"
#include "app/ses/pip/processors.h"

#include <boost/test/unit_test.hpp>
#include <climits>
#include <iostream>

BOOST_AUTO_TEST_SUITE(pipeline_processors_suite)

BOOST_AUTO_TEST_CASE(inputshifter_minimal) {
  pip::Input input(0, 100, 100, 100);

  pip::InputShifter sut;

  sut.set_shifts(5, 0, -5);

  sut.process(input);

  BOOST_CHECK_EQUAL(105, input.rotation_x);
  BOOST_CHECK_EQUAL(100, input.rotation_y);
  BOOST_CHECK_EQUAL(95, input.rotation_z);
}

BOOST_AUTO_TEST_CASE(inputshifter_overflow) {
  pip::Input input(0, 0, 0, 0);

  input.rotation_x = SHRT_MIN + 1;
  input.rotation_y = SHRT_MAX - 1;

  pip::InputShifter sut;

  sut.set_shifts(-5, 5, 0);

  sut.process(input);

  BOOST_CHECK_EQUAL(SHRT_MIN, input.rotation_x);
  BOOST_CHECK_EQUAL(SHRT_MAX, input.rotation_y);
}

BOOST_AUTO_TEST_CASE(curveconverter_hover_simple) {
  pip::Input input(0, 0, 0, 0);
  pip::Output output = {};

  pip::CurveConverter sut;

  sut.set_values(1, 1, 0);

  sut.convert(input, output);

  BOOST_CHECK_EQUAL(pip::CurveConverter::HOVER_THRESHOLD, output.fl_motor);
  BOOST_CHECK_EQUAL(pip::CurveConverter::HOVER_THRESHOLD, output.fr_motor);
  BOOST_CHECK_EQUAL(pip::CurveConverter::HOVER_THRESHOLD, output.bl_motor);
  BOOST_CHECK_EQUAL(pip::CurveConverter::HOVER_THRESHOLD, output.br_motor);
}

BOOST_AUTO_TEST_CASE(curveconverter_hover_threshold_shift) {
  pip::Input input(0, 0, 0, 0);
  pip::Output output = {};

  pip::CurveConverter sut;

  sut.set_values(1, 1, 50);

  sut.convert(input, output);

  BOOST_CHECK_EQUAL(pip::CurveConverter::HOVER_THRESHOLD + 50, output.fl_motor);
  BOOST_CHECK_EQUAL(pip::CurveConverter::HOVER_THRESHOLD + 50, output.fr_motor);
  BOOST_CHECK_EQUAL(pip::CurveConverter::HOVER_THRESHOLD + 50, output.bl_motor);
  BOOST_CHECK_EQUAL(pip::CurveConverter::HOVER_THRESHOLD + 50, output.br_motor);
}

#define BOOST_TEST_RANGE(val, min, max) BOOST_TEST((val >= min && val <= max))

#define CHECK_CURVE(val, multi, min, max)                                      \
  {                                                                            \
    pip::Input input(val, 0, 0, 0);                                            \
    pip::Output output = {};                                                   \
    pip::CurveConverter sut;                                                   \
    sut.set_values(multi, 1, 0);                                               \
    sut.convert(input, output);                                                \
    BOOST_TEST_RANGE(output.fl_motor, min, max);                               \
    BOOST_TEST_RANGE(output.fr_motor, min, max);                               \
    BOOST_TEST_RANGE(output.bl_motor, min, max);                               \
    BOOST_TEST_RANGE(output.br_motor, min, max);                               \
  }

BOOST_AUTO_TEST_CASE(curveconverter_max_throttle) {
  CHECK_CURVE(SHRT_MAX, 1, USHRT_MAX - 1, USHRT_MAX);
}

BOOST_AUTO_TEST_CASE(curveconverter_min_throttle) {
  CHECK_CURVE(SHRT_MIN, 1, 0, 2);
}

BOOST_AUTO_TEST_CASE(curveconverter_linear_vals) {
  CHECK_CURVE(1000, 1, 33766, 33768);
  CHECK_CURVE(11000, 1, 43767, 43768);
  CHECK_CURVE(21000, 1, 53767, 53768);
  CHECK_CURVE(31000, 1, 63767, 63768);

  CHECK_CURVE(-1000, 1, 31766, 31770);
  CHECK_CURVE(-11000, 1, 21766, 21770);
  CHECK_CURVE(-21000, 1, 11766, 11770);
  CHECK_CURVE(-31000, 1, 1766, 1770);
}

BOOST_AUTO_TEST_CASE(curveconverter_log_vals) {
  CHECK_CURVE(1000, 0.25, 46461, 46464);
  CHECK_CURVE(11000, 0.25, 57708, 57711);
  CHECK_CURVE(21000, 0.25, 62084, 62088);
  CHECK_CURVE(31000, 0.25, 65082, 65086);

  CHECK_CURVE(-1000, 0.25, 19070, 19074);
  CHECK_CURVE(-11000, 0.25, 7824, 7828);
  CHECK_CURVE(-21000, 0.25, 3448, 3452);
  CHECK_CURVE(-31000, 0.25, 448, 452);
}

BOOST_AUTO_TEST_CASE(curveconverter_cubic_vals) {
  CHECK_CURVE(1000, 3, 32766, 46470);
  CHECK_CURVE(11000, 3, 34005, 34009);
  CHECK_CURVE(21000, 3, 41390, 41394);
  CHECK_CURVE(31000, 3, 60512, 60516);

  CHECK_CURVE(-1000, 3, 32764, 32768);
  CHECK_CURVE(-11000, 3, 31525, 31529);
  CHECK_CURVE(-21000, 3, 24140, 24144);
  CHECK_CURVE(-31000, 3, 5018, 5022);
}

BOOST_AUTO_TEST_SUITE_END()