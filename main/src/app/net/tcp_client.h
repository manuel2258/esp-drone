#ifndef DRONE_SRC_NET_TCP_CLIENT
#define DRONE_SRC_NET_TCP_CLIENT

#include <array>
#include <inttypes.h>
#include <string>

namespace net {

/**
 * @brief Sends TCP packages
 */
class TcpClient {
private:
  const char *LOG_TAG = "TcpClient";

  std::string host;
  int port;

  int sock_handle;
  int con_handle;

public:
  /**
   * @brief Construct a new Tcp Client object
   * @param host The to send to host
   * @param port The to send to port
   */
  TcpClient(std::string host, int port) : host(host), port(port) {}

  /**
   * @brief Initializes the socket.
   * Requires a initializes connection.
   */
  void create_socket();

  /**
   * @brief Send the buffer to the host.
   * @param buf The to send buffer
   */
  void send_pkg(std::array<uint8_t, 10> *buf);
};

} // namespace net

#endif