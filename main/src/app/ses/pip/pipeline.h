#ifndef DRONE_SRC_APP_SES_PIP_PIPELINE
#define DRONE_SRC_APP_SES_PIP_PIPELINE

#include <functional>
#include <memory>
#include <vector>

#include "../eve/event_types.h"
#include "../session_types.h"
#include "pipeline_types.h"

namespace pip {

/**
 * @brief Processes a InputPkg into direct motor values.
 * Uses a series of proccessors to change input / output values.
 */
class Pipeline : eve::IEventHandler {
private:
  std::vector<IInputProcessor *> *inputs;
  IConverter *converter;
  std::vector<IOutputProcessor *> *outputs;

  ses::IOutputHandler *output_handler;

public:
  Pipeline(std::vector<IInputProcessor *> *in, IConverter *conv,
           std::vector<IOutputProcessor *> *out);

  ~Pipeline();

  void set_output_handler(ses::IOutputHandler *output_handler);

  void handle_event(eve::Event *event);

  Output *process(Input &in);
};

} // namespace pip

#endif
