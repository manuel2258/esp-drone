#include "esp_event.h"
#include "esp_log.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs_flash.h"
#include <string.h>

#include "lwip/err.h"
#include "lwip/sys.h"

#include "wifi_sta.h"

namespace net {

void WifiSta::handle_event(void *arg, esp_event_base_t event_base,
                           int32_t event_id, void *event_data) {
  if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
    esp_wifi_connect();
  } else if (event_base == WIFI_EVENT &&
             event_id == WIFI_EVENT_STA_DISCONNECTED) {
    connected = false;
    if (con_retry_amount < 5) {
      esp_wifi_connect();
      con_retry_amount++;

      ESP_LOGI(TAG, "Retry to connect to the AP");
    }
    ESP_LOGI(TAG, "Connect to the AP fail");
  } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
    ip_event_got_ip_t *event = (ip_event_got_ip_t *)event_data;
    ESP_LOGI(TAG, "got ip:" IPSTR, IP2STR(&event->ip_info.ip));
    con_retry_amount = 0;
    connected = true;
    ESP_LOGI(TAG, "Connect to the AP successfull");
  }
}

void WifiSta::init() {
  ESP_ERROR_CHECK(esp_netif_init());
  ESP_ERROR_CHECK(esp_event_loop_create_default());
  esp_netif_create_default_wifi_sta();

  wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
  ESP_ERROR_CHECK(esp_wifi_init(&cfg));

  ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));

  ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID,
                                             event_handler, NULL));
  ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP,
                                             event_handler, NULL));

  wifi_country_t county_config = {
      {'D', 'E', 'O'}, 1, 11, 0, WIFI_COUNTRY_POLICY_MANUAL};

  ESP_ERROR_CHECK(esp_wifi_set_country(&county_config));
  ESP_ERROR_CHECK(esp_wifi_set_protocol(WIFI_IF_STA, WIFI_PROTOCOL_LR));

  wifi_scan_threshold_t sta_threshhold = {0, wifi_auth_mode_t::WIFI_AUTH_OPEN};
  wifi_pmf_config_t sta_pmf = {true, false};

  wifi_sta_config_t sta_config = {"DRONE_LR_WIFI",
                                  "test12345",
                                  wifi_scan_method_t::WIFI_ALL_CHANNEL_SCAN,
                                  0,
                                  {0},
                                  0,
                                  0,
                                  wifi_sort_method_t::WIFI_CONNECT_AP_BY_SIGNAL,
                                  sta_threshhold,
                                  sta_pmf};

  wifi_config_t wifi_config;
  wifi_config.sta = sta_config;

  ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config));

  ESP_ERROR_CHECK(esp_wifi_start());

  ESP_LOGI(TAG, "wifi_init_station finished");
}

WifiSta::~WifiSta() {
  ESP_ERROR_CHECK(esp_event_handler_unregister(IP_EVENT, IP_EVENT_STA_GOT_IP,
                                               event_handler));
  ESP_ERROR_CHECK(esp_event_handler_unregister(WIFI_EVENT, ESP_EVENT_ANY_ID,
                                               event_handler));
}

} // namespace net