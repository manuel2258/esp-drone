#include "base_main.h"

#include "freertos/task.h"

namespace app {

BaseMain *BaseMain::instance;

BaseMain::BaseMain(net::BaseWifi *wifi) : wifi(wifi) {}

void BaseMain::init() {
  wifi->pre_init(&BaseMain::handle_wifi_events);
  xTaskCreate(BaseMain::update_task, "main_update", 16384, NULL, 5, NULL);
}

void BaseMain::handle_wifi_events(void *arg, esp_event_base_t event_base,
                                  int32_t event_id, void *event_data) {
  BaseMain::get_instance()->wifi->handle_event(arg, event_base, event_id,
                                               event_data);
}

void BaseMain::update_task(void *args) { BaseMain::get_instance()->update(); }
} // namespace app