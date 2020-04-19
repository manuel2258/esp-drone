#include "session.h"

namespace ses {

Session::Session(pip::Pipeline *pipeline, eve::EventChain *event_chain,
                 std::vector<IComponent *> *components,
                 std::vector<IOutputHandler *> *output_handlers)
    : pipeline(pipeline), event_chain(event_chain), components(components),
      output_handlers(output_handlers) {
  pipeline->set_output_handler(this);
}

Session::~Session() {
  delete pipeline;
  delete event_chain;

  for (auto component : *components) {
    delete component;
  }
  delete components;

  delete output_handlers;
}

void Session::on_new_pkg(pkg::BasePkg *pkg) {
  auto net_pkg_event = new eve::Event(eve::EventType::NET_PKG, pkg);
  event_chain->handle_event(net_pkg_event);
}

void Session::handle_output(pip::Output *output) {
  for (auto handler : *output_handlers) {
    handler->handle_output(output);
  }
}

void Session::update() { event_chain->trigger_events(); }

} // namespace ses