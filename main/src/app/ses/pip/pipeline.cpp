#include "pipeline.h"

namespace pip {

Pipeline::Pipeline(std::vector<IInputProcessor *> *in, IConverter *conv,
                   std::vector<IOutputProcessor *> *out)
    : inputs(in), converter(conv), outputs(out) {}

Pipeline::~Pipeline() {
  delete inputs;
  delete outputs;
}

void Pipeline::handle_event(eve::BaseEvent *event) {
  if (event->event_type != eve::EventType::NET_PKG) {
    return;
  }
  auto net_event = (eve::NetEvent *)event;
  if (net_event->pkg->pkg_type != pkg::PkgType::Input) {
    return;
  }
  auto input_pkg = (pkg::InputPkg *)net_event->pkg;
  Input input(*input_pkg);

  auto output = process(input);
  output_handler->handle_output(output);
  delete output;
}

Output *Pipeline::process(Input &in) {
  for (auto input = inputs->begin();
       input != inputs->end() && !(*input)->process(in); ++input) {
  }

  auto out = new Output();
  converter->convert(in, *out);

  for (auto output = outputs->begin();
       output != outputs->end() && !(*output)->process(*out); ++output) {
  }
  return out;
}

void Pipeline::set_output_handler(ses::IOutputHandler *handler) {
  output_handler = handler;
}

} // namespace pip