#include "main_client.h"

#include "esp_log.h"

#include "./pkg/input_pkg.h"

namespace app {

void MainClient::init() {
  set_instance(this);
  BaseMain::init();

  while (!wifi->is_connected()) {
    vTaskDelay(10);
  }

  ESP_LOGI("Main", "Creating client");

  client.create_socket();

  while (true) {
    pkg::InputPkg test_pkg(true, 1, 2, 3, 4);
    auto pkg = test_pkg.gen_pkg();
    client.send_pkg(pkg.get());
  }
};

} // namespace app
