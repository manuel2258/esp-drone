#ifndef DRONE_SRC_APP_SES_SYSTEM_OUTPUT_LOGGER
#define DRONE_SRC_APP_SES_SYSTEM_OUTPUT_LOGGER

#include "session_types.h"

#include "esp_log.h"

namespace ses {

class SystemOutputLogger : public IOutputHandler, public IComponent {
public:
  void handle_output(pip::Output *output) override {
    ESP_LOGI("SytemOutputLogger", "Received Output: %hu | %hu | %hu | %hu",
             output->fl_motor, output->fr_motor, output->bl_motor,
             output->br_motor);
  }
};

} // namespace ses

#endif