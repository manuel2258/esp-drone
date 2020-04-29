#include "main_client.h"

#include "esp_log.h"

#include "./pkg/pkg_factory.h"

namespace app {

void MainClient::init() {
  set_instance(this);
  BaseMain::init();

  while (!wifi->is_connected()) {
    vTaskDelay(10);
  }

  ESP_LOGI("MainClient", "Creating client");

  client.create_socket();
};

void MainClient::update() {
  while(!wifi->is_connected()) {
    vTaskDelay(100);
  }

  auto hello_pkg = pkg::gen_pkg<pkg::HelloPkg>();
  client.send_pkg(hello_pkg.get());

  while (true) {
    auto pkg = pkg::gen_pkg<pkg::InputPkg>(1, 2, 3, 4);
    client.send_pkg(pkg.get());
    vTaskDelay(100);
    ESP_LOGI("MainClient", "Sending pkg!");
  }
}

} // namespace app
