#ifndef DRONE_SRC_SYS_CLIENT_MAIN
#define DRONE_SRC_SYS_CLIENT_MAIN

#include "./net/tcp_server.h"
#include "./net/wifi_ap.h"
#include "base_main.h"

namespace app {

/**
 * @brief The Main Application used in the Dronecontroller / Server
 */
class MainServer : public BaseMain {
private:
  const char *LOG_TAG = "Main_Server";

  net::TcpServer server;

public:
  MainServer();

  void init() override;
};

} // namespace app

#endif