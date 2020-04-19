#include "builder.h"

namespace eve {

EventChainBuilder::EventChainBuilder() {
  handlers = new std::vector<IEventHandler *>;
  providers = new std::vector<IEventProvider *>;
}

EventChainBuilder::~EventChainBuilder() {
  if (handlers != nullptr) {
    delete handlers;
  }
  if (providers != nullptr) {
    delete handlers;
  }
  if (mutex != nullptr) {
    delete mutex;
  }
}

std::unique_ptr<EventChain> EventChainBuilder::build() {
  auto chain = std::make_unique<EventChain>(handlers, providers, mutex);
  handlers = nullptr;
  providers = nullptr;
  mutex = nullptr;
  return chain;
}

EventChainBuilder &
EventChainBuilder::add_event_handler(IEventHandler *handler) {
  handlers->push_back(handler);
  return *this;
}

EventChainBuilder &
EventChainBuilder::add_event_provider(IEventProvider *provider) {
  providers->push_back(provider);
  return *this;
}

EventChainBuilder &EventChainBuilder::set_mutex(ses::IMutex *mut) {
  mutex = mut;
  return *this;
}

} // namespace eve