#include "app/ses/session.h"
#include "mocks/mock_session.h"

BOOST_AUTO_TEST_SUITE(session_suite)

BOOST_AUTO_TEST_CASE(session_test) {
  ses::MockWatchdog mock_watchdog;
  ses::Session sut(&mock_watchdog);

  mock_watchdog.reset();
}

BOOST_AUTO_TEST_SUITE_END()