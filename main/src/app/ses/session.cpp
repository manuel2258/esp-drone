#include "session.h"

namespace ses {

Session::Session(BaseWatchdog *watchdog) : watchdog(watchdog) {
  watchdog->register_callback([this]() { on_watchdog_timeout(); });
}

void Session::on_new_input_pkg(pkg::InputPkg *pkg) { watchdog->reset(); }

void Session::on_watchdog_timeout() {}

} // namespace ses