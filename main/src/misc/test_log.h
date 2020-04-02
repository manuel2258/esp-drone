#ifndef DRONE_SRC_MISC_TEST_LOG
#define DRONE_SRC_MISC_TEST_LOG

#ifndef TEST_ENV

#include "esp_log.h"
#define LOGI(tag, format, ...) ESP_LOGI(tag, format, ##__VA_ARGS__)
#define LOGE(tag, format, ...) ESP_LOGI(tag, format, ##__VA_ARGS__)

#else

#define LOGI(tag, format, ...) printf(tag + format, ##__VA_ARGS__)
#define LOGE(tag, format, ...) printf(tag + format, ##__VA_ARGS__)

#endif

#endif
