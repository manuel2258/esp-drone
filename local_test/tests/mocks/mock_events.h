#ifndef TESTS_MOCKS_MOCK_EVENTS
#define TESTS_MOCKS_MOCK_EVENTS

#include "app/ses/eve/event_types.h"

class TestEventHandler : public eve::IEventHandler {
public:
  eve::Event *received_event = nullptr;
  void handle_event(eve::Event *event) override { received_event = event; }
};

class TestEventProvider : public eve::BaseEventProvider {
public:
  void mock_event(eve::Event *event) { event_handler->handle_event(event); }
};

#endif
