#ifndef DRONE_SRC_APP_SES_SESSION
#define DRONE_SRC_APP_SES_SESSION

#include <functional>
#include <unordered_map>

#include "../pkg/input_pkg.h"
#include "base_watchdog.h"

namespace ses {

class Session {
private:
  BaseWatchdog *watchdog;

public:
  Session(BaseWatchdog *watchdog);
  void on_new_input_pkg(pkg::InputPkg *pkg);
  void on_watchdog_timeout();
};

} // namespace ses

#endif