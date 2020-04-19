#include "app/ses/builder.h"
#include "app/ses/eve/builder.h"
#include "app/ses/eve/event_types.h"
#include "app/ses/pip/builder.h"
#include "app/ses/session.h"

#include "mocks/mock_session.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(session_suite)

BOOST_AUTO_TEST_CASE(sessionbuilder_test) {
  auto mutex = new TestMutex();

  ses::SessionBuilder builder;

  auto session = builder.set_mutex(mutex).build();
}

BOOST_AUTO_TEST_CASE(sessioninputsimple_test) {
  auto mutex = new TestMutex();
  auto output_handler = new TestOutputHandler();
  auto converter = new pip::CurveConverter();
  pkg::InputPkg input(0, 0, 0, 0);

  ses::SessionBuilder builder;

  auto session = builder.set_mutex(mutex)
                     .add_output_handler(output_handler)
                     .set_converter(converter)
                     .build();

  session->on_new_pkg(&input);
  session->update();

  BOOST_CHECK_EQUAL(pip::CurveConverter::HOVER_THRESHOLD,
                    output_handler->received_output.fl_motor);
  BOOST_CHECK_EQUAL(pip::CurveConverter::HOVER_THRESHOLD,
                    output_handler->received_output.fr_motor);
  BOOST_CHECK_EQUAL(pip::CurveConverter::HOVER_THRESHOLD,
                    output_handler->received_output.bl_motor);
  BOOST_CHECK_EQUAL(pip::CurveConverter::HOVER_THRESHOLD,
                    output_handler->received_output.br_motor);
}

BOOST_AUTO_TEST_CASE(sessioninputcomplex_test) {
  auto mutex = new TestMutex();
  auto output_handler = new TestOutputHandler();
  auto converter = new pip::CurveConverter();
  auto shifter = new pip::InputShifter();
  pkg::InputPkg input(10000, 0, 10000, 500);
  pkg::RotationShiftPkg shift(1000, -1000, 500);
  pkg::MultiplierPkg multi(30, 20);
  pkg::ThresholdShiftPkg thresh((int16_t)150);

  ses::SessionBuilder builder;

  auto session = builder.set_mutex(mutex)
                     .add_output_handler(output_handler)
                     .set_converter(converter)
                     .add_input_processor(shifter)
                     .add_event_handler(converter, false)
                     .add_event_handler(shifter, false)
                     .build();

  pip::Output cmp;

  session->on_new_pkg(&input);

  session->on_new_pkg(&shift);
  session->on_new_pkg(&input);

  session->on_new_pkg(&multi);
  session->on_new_pkg(&input);

  session->on_new_pkg(&thresh);
  session->on_new_pkg(&input);

  session->update();

  BOOST_CHECK_NE(cmp.fl_motor, output_handler->received_output.fl_motor);
  BOOST_CHECK_NE(cmp.fr_motor, output_handler->received_output.fr_motor);
  BOOST_CHECK_NE(cmp.bl_motor, output_handler->received_output.bl_motor);
  BOOST_CHECK_NE(cmp.br_motor, output_handler->received_output.br_motor);

  cmp = output_handler->received_output;

  session->update();
  session->update();

  BOOST_CHECK_NE(cmp.fl_motor, output_handler->received_output.fl_motor);
  BOOST_CHECK_NE(cmp.fr_motor, output_handler->received_output.fr_motor);
  BOOST_CHECK_NE(cmp.bl_motor, output_handler->received_output.bl_motor);
  BOOST_CHECK_NE(cmp.br_motor, output_handler->received_output.br_motor);

  cmp = output_handler->received_output;

  session->update();
  session->update();

  BOOST_CHECK_NE(cmp.fl_motor, output_handler->received_output.fl_motor);
  BOOST_CHECK_NE(cmp.fr_motor, output_handler->received_output.fr_motor);
  BOOST_CHECK_NE(cmp.bl_motor, output_handler->received_output.bl_motor);
  BOOST_CHECK_NE(cmp.br_motor, output_handler->received_output.br_motor);

  cmp = output_handler->received_output;

  session->update();
  session->update();

  BOOST_CHECK_NE(cmp.fl_motor, output_handler->received_output.fl_motor);
  BOOST_CHECK_NE(cmp.fr_motor, output_handler->received_output.fr_motor);
  BOOST_CHECK_NE(cmp.bl_motor, output_handler->received_output.bl_motor);
  BOOST_CHECK_NE(cmp.br_motor, output_handler->received_output.br_motor);
}

BOOST_AUTO_TEST_SUITE_END()