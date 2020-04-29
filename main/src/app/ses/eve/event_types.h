#ifndef DRONE_SRC_APP_SES_EVE_EVENT_TYPES
#define DRONE_SRC_APP_SES_EVE_EVENT_TYPES

#include <inttypes.h>
#include "../../pkg/base_pkg.h"

namespace eve {

enum class EventType : uint8_t { NET_PKG = 1, WATCHDOG_TIMEOUT = 2 };

class BaseEvent {
public:
  const EventType event_type;

  BaseEvent(EventType event_type)
      : event_type(event_type) {}

  virtual ~BaseEvent() {};
};

class NetEvent : public BaseEvent {
public:
  const pkg::BasePkg *pkg;
  NetEvent(pkg::BasePkg *pkg) : BaseEvent(EventType::NET_PKG), pkg(pkg) {}
  ~NetEvent() {
    delete pkg;
  }
};

class IEventHandler {
public:
  virtual ~IEventHandler() {}
  virtual void handle_event(BaseEvent *event) = 0;
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