#include "builder.h"

#include "./pip/processors.h"

namespace ses {

SessionBuilder::SessionBuilder() {
  components = new std::vector<IComponent *>;
  output_handlers = new std::vector<IOutputHandler *>;
}

SessionBuilder::~SessionBuilder() {
  if (components != nullptr) {
    delete components;
  }
  if (output_handlers != nullptr) {
    delete output_handlers;
  }
}

std::unique_ptr<Session> SessionBuilder::build() {
  auto pipe = pip_builder.build();
  eve_builder.add_event_handler((eve::IEventHandler *)pipe.get());
  auto event = eve_builder.build();
  auto session = std::make_unique<Session>(pipe.release(), event.release(),
                                           components, output_handlers);
  components = nullptr;
  output_handlers = nullptr;
  return session;
}

SessionBuilder &SessionBuilder::add_input_processor(pip::IInputProcessor *in) {
  pip_builder.add_input_processor(in);
  return *this;
}

SessionBuilder &
SessionBuilder::add_output_processor(pip::IOutputProcessor *out) {
  pip_builder.add_output_processor(out);
  return *this;
}

SessionBuilder &SessionBuilder::set_converter(pip::IConverter *conv) {
  pip_builder.set_converter(conv);
  return *this;
}

SessionBuilder &SessionBuilder::add_event_handler(eve::IEventHandler *handler) {
  eve_builder.add_event_handler(handler);
  return *this;
}

SessionBuilder &
SessionBuilder::add_event_provider(eve::IEventProvider *provider) {
  eve_builder.add_event_provider(provider);
  return *this;
}

SessionBuilder &SessionBuilder::set_mutex(IMutex *mutex) {
  eve_builder.set_mutex(mutex);
  return *this;
}

SessionBuilder &SessionBuilder::add_output_handler(IOutputHandler *handler) {
  output_handlers->push_back(handler);
  return *this;
}

SessionBuilder &SessionBuilder::add_component(IComponent *component) {
  components->push_back(component);
  return *this;
}

} // namespace ses
