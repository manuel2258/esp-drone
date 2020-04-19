#ifndef DRONE_SRC_APP_SES_SYSTEM_WATCHDOG
#define DRONE_SRC_APP_SES_SYSTEM_WATCHDOG

#include <functional>

#include "esp_timer.h"

#include "eve/event_types.h"
#include "session_types.h"

namespace ses {

/**
 * @brief A watchdog that uses a system timer
 * Note: Only one can exist at one time as a static callback function is needed
 */
class SystemWatchdog : public eve::BaseEventProvider,
                       public eve::IEventHandler,
                       public ses::IComponent {
private:
  static SystemWatchdog *instance;

  int timeout_ms;

  esp_timer_handle_t timer_handle;

public:
  SystemWatchdog(int timeout_ms);
  ~SystemWatchdog();

  static SystemWatchdog *get_instance() { return instance; }

  static void callback(void *args);

  void handle_event(eve::Event *event);
};

} // namespace ses
#endif