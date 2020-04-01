#include "tcp_client.h"

#include "esp_err.h"
#include "esp_log.h"
#include "esp_timer.h"

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include <lwip/netdb.h>

namespace net {

void TcpClient::create_socket() {
  struct sockaddr_in dest_addr;
  dest_addr.sin_addr.s_addr = inet_addr(host.c_str());
  dest_addr.sin_family = AF_INET;
  dest_addr.sin_port = htons(port);

  sock_handle = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
  if (sock_handle < 0) {
    ESP_LOGE(LOG_TAG, "Unable to create socket: errno %d", errno);
    return;
  }

  ESP_LOGI(LOG_TAG, "Socket created");
  int err =
      connect(sock_handle, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
  if (err != 0) {
    ESP_LOGE(LOG_TAG, "Socket unable to bind: errno %d", errno);
    return;
  }
  ESP_LOGI(LOG_TAG, "Successfully connected");
}

void TcpClient::send_pkg(std::array<uint8_t, 10> *buf) {
  int err = send(sock_handle, buf, 10, 0);
  if (err < 0) {
    ESP_LOGE(LOG_TAG, "Error occurred during sending: errno %d", errno);
  }
}

} // namespace net