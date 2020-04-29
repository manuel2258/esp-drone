#ifndef DRONE_SRC_APP_SES_BUILDER_FACTORY
#define DRONE_SRC_APP_SES_BUILDER_FACTORY

#include "builder.h"
#include "pip/processors.h"
#include "session_types.h"
#include "system_mutex.h"
#include "system_output_logger.h"

namespace ses {

std::unique_ptr<SessionBuilder> get_default_builder() {
  auto mutex = new ses::SystemMutex();
  auto output_logger = new ses::SystemOutputLogger();
  auto converter = new pip::CurveConverter();
  auto shifter = new pip::InputShifter();

  auto builder = new ses::SessionBuilder();
  builder->set_mutex(mutex)
      .set_converter(converter)
      .add_input_processor(shifter)
      .add_event_handler(shifter)
      .add_event_handler(converter)
      .add_output_handler(output_logger)
      .add_component(converter)
      .add_component(shifter)
      .add_component(output_logger);

  return std::unique_ptr<SessionBuilder>(builder);
}

} // namespace ses

#endif