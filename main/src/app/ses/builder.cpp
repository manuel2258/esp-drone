#include "builder.h"

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

SessionBuilder &SessionBuilder::add_input_processor(pip::IInputProcessor *in,
                                                    bool as_component) {
  pip_builder.add_input_processor(in);
  if (as_component) {
    components->push_back((IComponent *)in);
  }
  return *this;
}

SessionBuilder &SessionBuilder::add_output_processor(pip::IOutputProcessor *out,
                                                     bool as_component) {
  pip_builder.add_output_processor(out);
  if (as_component) {
    components->push_back((IComponent *)out);
  }
  return *this;
}

SessionBuilder &SessionBuilder::set_converter(pip::IConverter *conv,
                                              bool as_component) {
  pip_builder.set_converter(conv);
  if (as_component) {
    components->push_back((IComponent *)conv);
  }
  return *this;
}

SessionBuilder &SessionBuilder::add_event_handler(eve::IEventHandler *handler,
                                                  bool as_component) {
  eve_builder.add_event_handler(handler);
  if (as_component) {
    components->push_back((IComponent *)handler);
  }
  return *this;
}

SessionBuilder &
SessionBuilder::add_event_provider(eve::IEventProvider *provider,
                                   bool as_component) {
  eve_builder.add_event_provider(provider);
  if (as_component) {
    components->push_back((IComponent *)provider);
  }
  return *this;
}

SessionBuilder &SessionBuilder::set_mutex(IMutex *mutex) {
  eve_builder.set_mutex(mutex);
  return *this;
}

SessionBuilder &SessionBuilder::add_output_handler(IOutputHandler *handler,
                                                   bool as_component) {
  output_handlers->push_back(handler);
  if (as_component) {
    components->push_back((IComponent *)handler);
  }
  return *this;
}

} // namespace ses
