#include "main_server.h"

#include "esp_log.h"

#include "./pkg/input_pkg.h"

namespace app {

MainServer::MainServer()
    : BaseMain(new net::WifiAp()),
      server(8080, [this](std::array<uint8_t, 10> &buf) {
        pkg::InputPkg pkg(buf);
        ESP_LOGI(LOG_TAG, "Received pkg: %s, %hi, %hi, %hi, %hi",
                 pkg.motors_on ? "t" : "f", pkg.throttle, pkg.rotation_y,
                 pkg.rotation_z, pkg.rotation_x);
      }) {}

void MainServer::init() {
  BaseMain::init();

  while (!wifi->is_connected()) {
    vTaskDelay(1);
  }

  server.create_socket();
  while (true) {
    server.recv_next_pkg();
  }
}

} // namespace app
