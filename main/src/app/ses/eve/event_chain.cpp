#include "event_chain.h"

namespace eve {

EventChain::EventChain(std::vector<IEventHandler *> *handlers,
                       std::vector<IEventProvider *> *providers,
                       ses::IMutex *mutex)
    : handlers(handlers), providers(providers), mutex(mutex) {
  for (auto provider : *providers) {
    provider->register_handler(this);
  }
}

EventChain::~EventChain() {
  delete handlers;
  delete providers;
  delete mutex;
}

void EventChain::handle_event(Event *event) {
  mutex->lock();
  events.push(event);
  mutex->free();
}

void EventChain::trigger_events() {
  mutex->lock();
  auto event = events.front();
  events.pop();
  mutex->free();

  for (auto handler : *handlers) {
    handler->handle_event(event);
  }
  delete event;
}

} // namespace eve
