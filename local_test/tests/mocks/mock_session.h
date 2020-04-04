#ifndef DRONE_TESTS_MOCKS_MOCK_SESSION
#define DRONE_TESTS_MOCKS_MOCK_SESSION

#include "app/ses/base_watchdog.h"

namespace ses {

class MockWatchdog : public BaseWatchdog {
public:
  void reset() override {}

  void mock_trigger_callback() { trigger_callback(); }
};

} // namespace ses

#endif