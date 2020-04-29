#include "app/ses/eve/builder.h"
#include "app/ses/eve/event_chain.h"
#include "app/ses/eve/event_types.h"
#include "app/ses/session_types.h"

#include "mocks/mock_events.h"
#include "mocks/mock_session.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(eventchain_suite)

BOOST_AUTO_TEST_CASE(simpleevent_test) {
  TestEventHandler test_handler1;
  TestEventHandler test_handler2;
  auto test_mutex = new TestMutex();
  auto event = new eve::Event(eve::EventType::NET_PKG, nullptr);

  eve::EventChainBuilder builder;

  auto chain = builder.add_event_handler(&test_handler1)
                   .add_event_handler(&test_handler2)
                   .set_mutex(test_mutex)
                   .build();

  chain->handle_event(event);
  chain->trigger_events();

  BOOST_CHECK_EQUAL(event, test_handler1.received_event);
  BOOST_CHECK_EQUAL(event, test_handler2.received_event);
}

BOOST_AUTO_TEST_SUITE_END()