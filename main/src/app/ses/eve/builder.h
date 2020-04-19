#ifndef DRONE_SRC_APP_SES_EVE_BUILDER
#define DRONE_SRC_APP_SES_EVE_BUILDER

#include <memory>
#include <vector>

#include "event_chain.h"
#include "event_types.h"

namespace eve {

class EventChainBuilder {
private:
  std::vector<IEventHandler *> *handlers;
  std::vector<IEventProvider *> *providers;

  ses::IMutex *mutex;

public:
  EventChainBuilder();
  ~EventChainBuilder();

  std::unique_ptr<EventChain> build();

  EventChainBuilder &add_event_handler(IEventHandler *handler);

  EventChainBuilder &add_event_provider(IEventProvider *provider);

  EventChainBuilder &set_mutex(ses::IMutex *mutex);
};
} // namespace eve

#endif