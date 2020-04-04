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
private:
  static BaseMain *instance;

protected:
  static void set_instance(BaseMain *new_instance) { instance = new_instance; }

public:
  net::BaseWifi *wifi;
  BaseMain(net::BaseWifi *wifi_ptr);
  ~BaseMain() { delete wifi; }

  static BaseMain *get_instance() { return instance; }

  static void handle_wifi_events(void *arg, esp_event_base_t event_base,
                                 int32_t event_id, void *event_data);

  /**
   * @brief Initializes the system.
   * Has to be called after the main_obj pointer was set.
   */
  virtual void init();
};

} // namespace app

#endif
