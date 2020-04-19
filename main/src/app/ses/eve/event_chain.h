#ifndef DRONE_SRC_APP_SES_EVE_EVENT_CHAIN
#define DRONE_SRC_APP_SES_EVE_EVENT_CHAIN

#include <queue>
#include <vector>

#include "../session_types.h"
#include "event_types.h"

namespace eve {

/**
 * @brief Contains several handlers that responed to given events based on
 * bitmasks.
 */
class EventChain : public IEventHandler {
private:
  std::vector<IEventHandler *> *handlers;
  std::vector<IEventProvider *> *providers;

  ses::IMutex *mutex;

  std::queue<Event *> events;

public:
  EventChain(std::vector<IEventHandler *> *handlers,
             std::vector<IEventProvider *> *providers, ses::IMutex *mutex);
  ~EventChain();

  void set_mutex(ses::IMutex *mutex);

  void handle_event(Event *event) override;

  void trigger_events();
};

} // namespace eve

#endif