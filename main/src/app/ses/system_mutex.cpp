#include "system_mutex.h"

#include "freertos/portmacro.h"

namespace ses {
SystemMutex::SystemMutex() { semaphore_handle = xSemaphoreCreateBinary(); }

void SystemMutex::lock() { xSemaphoreTake(semaphore_handle, portMAX_DELAY); }

void SystemMutex::free() { xSemaphoreGive(semaphore_handle); }

} // namespace ses