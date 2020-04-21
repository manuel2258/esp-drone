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

  ESP_LOGI("Main", "Creating client");

  client.create_socket();

  auto hello_pkg = pkg::gen_pkg<pkg::HelloPkg>(pkg::PkgType::Hello);
  client.send_pkg(hello_pkg.get());

  /*while (true) {
    auto pkg = pkg::gen_pkg<pkg::InputPkg>(pkg::PkgType::Input, 1, 2, 3, 4);
    client.send_pkg(pkg.get());
    vTaskDelay(100);
  }*/
};

} // namespace app
