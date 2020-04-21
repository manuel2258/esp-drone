#ifndef DRONE_SRC_APP_SES_EVE_EVENT_TYPES
#define DRONE_SRC_APP_SES_EVE_EVENT_TYPES

#include <inttypes.h>

namespace eve {

enum class EventType : uint8_t { NET_PKG = 1, WATCHDOG_TIMEOUT = 2 };

struct Event {
  const EventType event_type;
  const void *data;

  Event(EventType event_type, void *data)
      : event_type(event_type), data(data) {}
};

class IEventHandler {
public:
  virtual ~IEventHandler() {}
  virtual void handle_event(Event *event) = 0;
};

class IEventProvider {
public:
  virtual ~IEventProvider() {}
  virtual void register_handler(IEventHandler *new_handler) = 0;
};

class BaseEventProvider : public IEventProvider {
protected:
  IEventHandler *event_handler;

public:
  virtual ~BaseEventProvider();
  void register_handler(IEventHandler *new_handler) override {
    event_handler = new_handler;
  }
};

} // namespace eve

#endif