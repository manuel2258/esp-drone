#ifndef DRONE_SRC_APP_SES_SYSTEM_MUTEX
#define DRONE_SRC_APP_SES_SYSTEM_MUTEX

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

#include "session_types.h"

namespace ses {

class SystemMutex : public IMutex {
private:
  SemaphoreHandle_t semaphore_handle = NULL;

public:
  SystemMutex();
  void lock() override;
  void free() override;
};

} // namespace ses

#endif