#ifndef DRONE_SRC_NET_WIFI
#define DRONE_SRC_NET_WIFI

#include "esp_event.h"

namespace net {

/**
 * @brief A base class for AP / STA Wifi.
 */
class BaseWifi {
protected:
  bool connected;
  esp_event_handler_t event_handler;

  /**
   * @brief Initializes the wifi interface.
   * Note: Derived class has to implement this function.
   */
  virtual void init() = 0;

public:
  virtual ~BaseWifi() {}

  /**
   * @brief Whether the AP / STA is connected to the counter part.
   */
  bool is_connected() { return connected; }

  /**
   * @brief To be called in order to initialize the derived wifi interface.
   * @param wifi_event_handler The wrapper function that calls handle_event.
   */
  void pre_init(esp_event_handler_t wifi_event_handler) {
    event_handler = wifi_event_handler;
    init();
  }

  /**
   * @brief Handles incoming wifi events.
   * Note: Derived class has to implement this function.
   */
  virtual void handle_event(void *arg, esp_event_base_t event_base,
                            int32_t event_id, void *event_data) = 0;
};

} // namespace net

#endif