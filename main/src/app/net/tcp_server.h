#ifndef DRONE_SRC_NET_TCP_SERVER
#define DRONE_SRC_NET_TCP_SERVER

#include <array>
#include <functional>
#include <memory>

#include "../pkg/base_pkg.h"

namespace net {

/**
 * @brief Receives TCP Packages.
 */
class TcpServer {
private:
  const char *LOG_TAG = "TcpServer";

  int port;
  std::function<void(uint8_t *)> callback;

  int sock_handle;
  int con_handle;

public:
  /**
   * @brief Construct a new Tcp Server object.
   *
   * @param port The to listen at port.
   * @param callback The to call function on receiving a package.
   */
  TcpServer(int port, std::function<void(uint8_t *)> callback)
      : port(port), callback(callback) {}

  /**
   * @brief Initializes the socket.
   * Requires a initializes connection.
   */
  void create_socket();

  /**
   * @brief Recieves the next package.
   * Blocks until incoming package. Calls callback when receiving.
   */
  void recv_next_pkg();
};

} // namespace net

#endif
