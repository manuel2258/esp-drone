#include "base_main.h"

namespace app {

BaseMain::BaseMain(net::BaseWifi *wifi) : wifi(wifi) {}

void BaseMain::init() { wifi->pre_init(&BaseMain::handle_wifi_events); }

void BaseMain::handle_wifi_events(void *arg, esp_event_base_t event_base,
                                  int32_t event_id, void *event_data) {
  BaseMain::get_instance()->wifi->handle_event(arg, event_base, event_id,
                                               event_data);
}

} // namespace app