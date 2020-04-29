#include "esp_event.h"

#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs_flash.h"
#include <stdio.h>

//#define BUILD_CLIENT

#ifdef BUILD_CLIENT
#include "app/main_client.h"
#else
#include "app/main_server.h"
#endif

extern "C" void app_main(void) {
  esp_err_t ret = nvs_flash_init();
  if (ret == ESP_ERR_NVS_NO_FREE_PAGES ||
      ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
    ESP_ERROR_CHECK(nvs_flash_erase());
    ret = nvs_flash_init();
  }
  ESP_ERROR_CHECK(ret);

  app::BaseMain *main_obj;

#ifdef BUILD_CLIENT
  main_obj = new app::MainClient();
#else
  main_obj = new app::MainServer();
#endif

  main_obj->init();
}