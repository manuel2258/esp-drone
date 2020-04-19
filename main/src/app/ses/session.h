#ifndef DRONE_SRC_APP_SES_SESSION
#define DRONE_SRC_APP_SES_SESSION

#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>

#include "../pkg/input_pkg.h"
#include "eve/event_chain.h"
#include "pip/pipeline.h"
#include "session_types.h"

namespace ses {

class Session : public IOutputHandler {
private:
  pip::Pipeline *pipeline;
  eve::EventChain *event_chain;

  std::vector<IComponent *> *components;

  std::vector<IOutputHandler *> *output_handlers;

public:
  Session(pip::Pipeline *pipeline, eve::EventChain *event_chain,
          std::vector<IComponent *> *components,
          std::vector<IOutputHandler *> *output_handlers);
  ~Session();

  void on_new_pkg(pkg::BasePkg *pkg);

  void handle_output(pip::Output *output) override;

  void update();
};

} // namespace ses

#endif