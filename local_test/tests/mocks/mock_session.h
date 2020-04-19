#ifndef TESTS_MOCKS_MOCK_SESSION
#define TESTS_MOCKS_MOCK_SESSION

#include "app/ses/pip/pipeline_types.h"
#include "app/ses/session_types.h"

class TestMutex : public ses::IMutex {
public:
  void lock() override {}
  void free() override {}
};

class TestOutputHandler : public ses::IOutputHandler, public ses::IComponent {
public:
  pip::Output received_output;
  void handle_output(pip::Output *output) { received_output = *output; }

  ~TestOutputHandler() {}
};

#endif
