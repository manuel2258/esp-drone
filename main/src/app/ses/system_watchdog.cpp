#include "system_watchdog.h"
#include "esp_log.h"

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

void SystemWatchdog::reset() {
  ESP_ERROR_CHECK(esp_timer_stop(timer_handle));
  ESP_ERROR_CHECK(esp_timer_start_once(timer_handle, timeout_ms * 1000));
}

void SystemWatchdog::callback(void *args) {
  SystemWatchdog::get_instance()->trigger_callback();
}

SystemWatchdog::~SystemWatchdog() {
  ESP_ERROR_CHECK(esp_timer_stop(timer_handle));
  ESP_ERROR_CHECK(esp_timer_delete(timer_handle));
}

} // namespace ses