#include "base_main.h"

extern app::BaseMain *main_obj;

namespace app {

static void handle_wifi_events(void *arg, esp_event_base_t event_base,
                               int32_t event_id, void *event_data) {
  main_obj->wifi->handle_event(arg, event_base, event_id, event_data);
}

BaseMain::BaseMain(net::BaseWifi *wifi) : wifi(wifi) {}

void BaseMain::init() { wifi->pre_init(&handle_wifi_events); }

} // namespace app