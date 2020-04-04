#ifndef DRONE_SRC_APP_SES_BASE_WATCHDOG
#define DRONE_SRC_APP_SES_BASE_WATCHDOG

#include <functional>

namespace ses {

/**
 * @brief Base class to detect timeouts.
 */
class BaseWatchdog {
private:
  /**
   * @brief The to call function on a timeout
   */
  std::function<void(void)> callback;

protected:
  void trigger_callback() { callback(); }

public:
  void register_callback(std::function<void(void)> timeout_callback) {
    callback = timeout_callback;
  }

  virtual void reset() = 0;
};

} // namespace ses

#endif