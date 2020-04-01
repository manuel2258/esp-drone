#ifndef DRONE_SRC_SYS_BASE_MAIN
#define DRONE_SRC_SYS_BASE_MAIN

#include <functional>
#include <vector>

#include "./net/base_wifi.h"
#include "esp_event.h"

namespace app {

/**
 * @brief Base class to easy bind the wifi event function
 */
class BaseMain {
public:
  net::BaseWifi *wifi;
  BaseMain(net::BaseWifi *wifi_ptr);
  ~BaseMain() { delete wifi; }

  /**
   * @brief Initializes the system.
   * Has to be called after the main_obj pointer was set.
   */
  virtual void init();
};

} // namespace app

#endif
