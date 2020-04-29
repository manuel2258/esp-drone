#ifndef DRONE_SRC_SYS_CLIENT_MAIN
#define DRONE_SRC_SYS_CLIENT_MAIN

#include "./net/tcp_client.h"
#include "./net/wifi_sta.h"
#include "base_main.h"

namespace app {

/**
 * @brief The Main Application used in the Remotecontroller / Client
 */
class MainClient : public BaseMain {
private:
  const char *LOG_TAG = "Main_Client";

  net::TcpClient client;
  net::WifiSta wifi_sta;

public:
  MainClient() : BaseMain(new net::WifiSta()), client("192.168.4.1", 8080) {}

  void init() override;

  void update() override;
};

} // namespace app

#endif