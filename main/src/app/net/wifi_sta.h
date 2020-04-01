#ifndef DRONE_SRC_NET_WIFI_AP
#define DRONE_SRC_NET_WIFI_AP

#include "base_wifi.h"

namespace net {

class WifiSta : public BaseWifi {
private:
  const char *TAG = "Wifi_STA";

  uint8_t con_retry_amount;

protected:
  void init() override;

public:
  ~WifiSta() override;

  void handle_event(void *arg, esp_event_base_t event_base, int32_t event_id,
                    void *event_data) override;
};

} // namespace net

#endif