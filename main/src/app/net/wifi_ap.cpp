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

#include "wifi_ap.h"

namespace net {

void WifiAp::handle_event(void *arg, esp_event_base_t event_base,
                          int32_t event_id, void *event_data) {
  if (event_id == WIFI_EVENT_AP_STACONNECTED) {
    wifi_event_ap_staconnected_t *event =
        (wifi_event_ap_staconnected_t *)event_data;
    ESP_LOGI(TAG, "station " MACSTR " join, AID=%d", MAC2STR(event->mac),
             event->aid);
    connected = true;
    ESP_LOGI(TAG, "Client connected from AP");
  } else if (event_id == WIFI_EVENT_AP_STADISCONNECTED) {
    wifi_event_ap_stadisconnected_t *event =
        (wifi_event_ap_stadisconnected_t *)event_data;
    ESP_LOGI(TAG, "station " MACSTR " leave, AID=%d", MAC2STR(event->mac),
             event->aid);
    connected = false;
    ESP_LOGI(TAG, "Client disconnected to AP");
  }
}

void WifiAp::init() {
  ESP_ERROR_CHECK(esp_netif_init());
  ESP_ERROR_CHECK(esp_event_loop_create_default());
  esp_netif_create_default_wifi_ap();

  wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
  ESP_ERROR_CHECK(esp_wifi_init(&cfg));

  ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));

  ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID,
                                             event_handler, NULL));

  wifi_country_t county_config = {
      {'D', 'E', 'O'}, 1, 11, 0, WIFI_COUNTRY_POLICY_MANUAL};

  ESP_ERROR_CHECK(esp_wifi_set_country(&county_config));
  ESP_ERROR_CHECK(esp_wifi_set_protocol(WIFI_IF_AP, WIFI_PROTOCOL_LR));

  wifi_config_t wifi_config;
  wifi_ap_config_t ap_config = {"DRONE_LR_WIFI",    "test12345", 13, 1,
                                WIFI_AUTH_WPA2_PSK, false,       1,  100};
  wifi_config.ap = ap_config;
  ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_AP, &wifi_config));

  ESP_ERROR_CHECK(esp_wifi_start());

  ESP_LOGI(TAG, "wifi_init_softap finished");
}

WifiAp::~WifiAp() {
  ESP_ERROR_CHECK(esp_event_handler_unregister(WIFI_EVENT, ESP_EVENT_ANY_ID,
                                               event_handler));
}

} // namespace net