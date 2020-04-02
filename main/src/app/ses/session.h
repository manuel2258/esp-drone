#ifndef DRONE_SRC_APP_SES_SESSION
#define DRONE_SRC_APP_SES_SESSION

#include <functional>
#include <unordered_map>

#include "../pkg/input_pkg.h"

namespace ses {

class Session {
public:
  void on_new_input_pkg(pkg::InputPkg *pkg);
};

} // namespace ses

#endif