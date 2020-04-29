#include "main_server.h"

#include "esp_log.h"

#include "./pkg/pkg_factory.h"
#include "./ses/builder_factory.h"

namespace app {

MainServer::MainServer()
    : BaseMain(new net::WifiAp()),
      server(8080, [this](uint8_t *buf) { on_new_pkg(buf); }) {}

void MainServer::init() {
  set_instance(this);
  BaseMain::init();

  while (!wifi->is_connected()) {
    vTaskDelay(1);
  }

  server.create_socket();
  while (true) {
    server.recv_next_pkg();
  }
}

void MainServer::on_new_pkg(uint8_t *buf) {
  auto pkg = pkg::parse_pkg(buf);
  if (pkg->pkg_type == pkg::PkgType::Hello) {
    if (active_session) {
      ESP_LOGE(LOG_TAG, "Received Hello Package while in active Session ...");
      return;
    }
    session = ses::get_default_builder()->build().release();
    active_session = true;
  } else if (pkg->pkg_type == pkg::PkgType::Bye) {
    if (!active_session) {
      ESP_LOGE(LOG_TAG, "Received Bye Package while not in active Session ...");
      return;
    }
    // TODO: Handle Session Ending
    delete session;
    active_session = false;
  } else {
    if (!active_session) {
      ESP_LOGE(LOG_TAG,
               "Received Input Package while not in active Session ...");
      return;
    }
    session->on_new_pkg(pkg.release());
  }
  ESP_LOGI("MainServer", "Free Heap after pkg: %i", xPortGetFreeHeapSize());
}

void MainServer::update() {
  while (true) {
    if (active_session) {
      session->update();
    }
    vTaskDelay(10);
  }
}

} // namespace app
