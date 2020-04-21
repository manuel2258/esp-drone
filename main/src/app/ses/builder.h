#ifndef DRONE_SRC_APP_SES_BUILDER
#define DRONE_SRC_APP_SES_BUILDER

#include <memory>
#include <vector>

#include "eve/builder.h"
#include "pip/builder.h"
#include "session.h"
#include "session_types.h"

namespace ses {

class SessionBuilder {
private:
  pip::PipelineBuilder pip_builder;
  eve::EventChainBuilder eve_builder;
  std::vector<IComponent *> *components;
  std::vector<IOutputHandler *> *output_handlers;

public:
  SessionBuilder();
  ~SessionBuilder();

  static std::unique_ptr<SessionBuilder> get_default();

  std::unique_ptr<Session> build();

  /**
   * @brief Adds ptr as input processor
   */
  SessionBuilder &add_input_processor(pip::IInputProcessor *in);

  /**
   * @brief Adds ptr as output processor
   */
  SessionBuilder &add_output_processor(pip::IOutputProcessor *out);

  /**
   * @brief Sets ptr as converter
   */
  SessionBuilder &set_converter(pip::IConverter *conv);

  /**
   * @brief Adds ptr as input processor
   */
  SessionBuilder &add_event_handler(eve::IEventHandler *handler);

  SessionBuilder &add_event_provider(eve::IEventProvider *provider);

  /**
   * @brief Set the Mutex Object of the EventChain
   */
  SessionBuilder &set_mutex(IMutex *mutex);

  SessionBuilder &add_output_handler(IOutputHandler *output_handler);

  SessionBuilder &add_component(IComponent *component);
};
} // namespace ses

#endif