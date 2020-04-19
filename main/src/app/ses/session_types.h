#ifndef DRONE_SRC_APP_SES_SESSION_TYPES
#define DRONE_SRC_APP_SES_SESSION_TYPES

#include "pip/pipeline_types.h"

namespace ses {

class IComponent {
public:
  virtual ~IComponent() {}
};

class IMutex {
public:
  virtual void lock() = 0;
  virtual void free() = 0;
};

class IOutputHandler {
public:
  virtual void handle_output(pip::Output *output) = 0;
};

} // namespace ses

#endif
