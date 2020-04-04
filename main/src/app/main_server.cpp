#include "main_server.h"

#include "../misc/test_log.h"
#include "./pkg/pkg_factory.h"

namespace app {

MainServer::MainServer()
    : BaseMain(new net::WifiAp()),
      server(8080, [this](std::array<uint8_t, pkg::MAX_PKG_SIZE> &buf) {
        on_new_pkg(buf);
      }) {}

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

void MainServer::on_new_pkg(std::array<uint8_t, pkg::MAX_PKG_SIZE> &buf) {
  auto pkg = pkg::parse_pkg(buf);
  if (pkg->pkg_type == pkg::PkgType::Hello) {
    if (active_session) {
      ESP_LOGE(LOG_TAG, "Received Hello Package while in active Session ...");
      return;
    }
    session = new ses::Session();
    active_session = true;
  } else if (pkg->pkg_type == pkg::PkgType::Bye) {
    if (!active_session) {
      ESP_LOGE(LOG_TAG, "Received Bye Package while not in active Session ...");
      return;
    }
    // TODO: Handle Session Ending
    delete session;
    active_session = false;
  } else if (pkg->pkg_type == pkg::PkgType::Input) {
    if (!active_session) {
      ESP_LOGE(LOG_TAG,
               "Received Input Package while not in active Session ...");
      return;
    }
    session->on_new_input_pkg((pkg::InputPkg *)pkg.get());
  }
}

} // namespace app
