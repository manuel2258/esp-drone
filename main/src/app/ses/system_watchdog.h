#ifndef DRONE_SRC_APP_SES_SYSTEM_WATCHDOG
#define DRONE_SRC_APP_SES_SYSTEM_WATCHDOG

#include "base_watchdog.h"

#include <functional>

#include "esp_timer.h"

namespace ses {

/**
 * @brief A watchdog that uses a system timer
 * Note: As a static callback function is needed
 */
class SystemWatchdog : public BaseWatchdog {
private:
  static SystemWatchdog *instance;

  int timeout_ms;

  esp_timer_handle_t timer_handle;

public:
  SystemWatchdog(int timeout_ms);
  ~SystemWatchdog();

  static SystemWatchdog *get_instance() { return instance; }

  static void callback(void *args);

  void reset() override;
};

} // namespace ses
#endif