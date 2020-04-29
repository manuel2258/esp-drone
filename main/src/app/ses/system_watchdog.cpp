#include "system_watchdog.h"

#include "esp_log.h"

#include "../pkg/input_pkg.h"

namespace ses {

SystemWatchdog::SystemWatchdog(int timeout_ms) : timeout_ms(timeout_ms) {
  if (instance != nullptr) {
    ESP_LOGE("SystemWatchdog",
             "Someone tried to allocate multiple SystemWatchdogs ...");
    return;
  }

  instance = this;
  esp_timer_create_args_t timer_args = {};
  timer_args.callback = &SystemWatchdog::callback;
  timer_args.name = "SystemWatchdog";

  ESP_ERROR_CHECK(esp_timer_create(&timer_args, &timer_handle));

  ESP_ERROR_CHECK(esp_timer_start_once(timer_handle, timeout_ms * 1000));
}

void SystemWatchdog::handle_event(eve::BaseEvent *event) {
  // Watch for NetPkg
  if (event->event_type != eve::EventType::NET_PKG) {
    return;
  }

  // Check if type is input
  auto net_event = (eve::NetEvent *)event;
  if (net_event->pkg->pkg_type != pkg::PkgType::Input) {
    return;
  }

  // If so reset watchdog
  ESP_ERROR_CHECK(esp_timer_stop(timer_handle));
  ESP_ERROR_CHECK(esp_timer_start_once(timer_handle, timeout_ms * 1000));
}

void SystemWatchdog::callback(void *args) {
  auto event = new eve::BaseEvent(eve::EventType::WATCHDOG_TIMEOUT);
  get_instance()->event_handler->handle_event(event);
}

SystemWatchdog::~SystemWatchdog() {
  ESP_ERROR_CHECK(esp_timer_stop(timer_handle));
  ESP_ERROR_CHECK(esp_timer_delete(timer_handle));
}

} // namespace ses