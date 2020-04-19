#include "tcp_server.h"

#include <array>

#include "esp_err.h"
#include "esp_log.h"

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include <lwip/netdb.h>

namespace net {

void TcpServer::create_socket() {
  int ip_protocol = IPPROTO_IP;

  struct sockaddr_in dest_addr;
  dest_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  dest_addr.sin_family = AF_INET;
  dest_addr.sin_port = htons(port);

  sock_handle = socket(AF_INET, SOCK_STREAM, ip_protocol);
  if (sock_handle < 0) {
    ESP_LOGE(LOG_TAG, "Unable to create socket: errno %d", errno);
    return;
  }

  ESP_LOGI(LOG_TAG, "Socket created");
  int err = bind(sock_handle, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
  if (err != 0) {
    ESP_LOGE(LOG_TAG, "Socket unable to bind: errno %d", errno);
    return;
  }
  ESP_LOGI(LOG_TAG, "Socket bound, port %d", port);

  ESP_ERROR_CHECK(listen(sock_handle, 1));

  ESP_LOGI(LOG_TAG, "Socket listening, waiting for connection");

  struct sockaddr_in source_addr;
  uint addr_len = sizeof(source_addr);
  con_handle = accept(sock_handle, (struct sockaddr *)&source_addr, &addr_len);
  if (sock_handle < 0) {
    ESP_LOGE(LOG_TAG, "Unable to accept connection: errno %d", errno);
    return;
  }
}

void TcpServer::recv_next_pkg() {
  uint8_t buf[pkg::MAX_TOTAL_SIZE];
  int recv_len = recv(con_handle, buf, pkg::MAX_TOTAL_SIZE, 0);
  if (recv_len < 0) {
    ESP_LOGE(LOG_TAG, "Error occurred during receiving: errno %d", errno);
  } else if (recv_len == 0) {
    ESP_LOGW(LOG_TAG, "Connection closed");
  } else {
    callback(buf);
  }
}

} // namespace net