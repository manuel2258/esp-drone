#ifndef DRONE_SRC_APP_SES_PIP_INPUT_PROCESSORS
#define DRONE_SRC_APP_SES_PIP_INPUT_PROCESSORS

#include <climits>

#include "../eve/event_types.h"
#include "../session_types.h"
#include "pipeline_types.h"

namespace pip {

class InputShifter : public IInputProcessor,
                     public ses::IComponent,
                     public eve::IEventHandler {
private:
  int16_t rotation_x_shift = 0;
  int16_t rotation_y_shift = 0;
  int16_t rotation_z_shift = 0;

  void add_short(int16_t *target, int16_t *val);

public:
  ~InputShifter() {}
  bool process(Input &in) override;

  void handle_event(eve::Event *event) override;

  void set_shifts(int16_t x, int16_t y, int16_t z);
};

class CurveConverter : public IConverter,
                       public ses::IComponent,
                       public eve::IEventHandler {
private:
  float input_multi = 1;
  float rotation_multi = 1;
  int16_t throttle_threshold = 0;

  uint16_t curve_convert(int16_t input, float exponent, uint16_t threshold);

public:
  ~CurveConverter() {}
  static const uint16_t HOVER_THRESHOLD = SHRT_MAX;
  void convert(Input &in, Output &out) override;

  void handle_event(eve::Event *event) override;

  void set_values(float input_multi, float rotation_multi,
                  int16_t throttle_threshold);
};

} // namespace pip

#endif