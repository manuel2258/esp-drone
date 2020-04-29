#ifndef DRONE_SRC_SYS_CLIENT_MAIN
#define DRONE_SRC_SYS_CLIENT_MAIN

#include <unordered_map>

#include "./net/tcp_server.h"
#include "./net/wifi_ap.h"
#include "./pkg/base_pkg.h"
#include "./pkg/hello_pkg.h"
#include "./pkg/input_pkg.h"
#include "./ses/builder.h"
#include "./ses/session.h"
#include "base_main.h"

namespace app {

/**
 * @brief The Main Application used in the Dronecontroller / Server
 */
class MainServer : public BaseMain {
private:
  const char *LOG_TAG = "Main_Server";

  bool active_session;
  ses::Session *session;

private:
  net::TcpServer server;

  void on_new_pkg(uint8_t *buf);

public:
  MainServer();

  void init() override;

  void update() override;
};

} // namespace app

#endif