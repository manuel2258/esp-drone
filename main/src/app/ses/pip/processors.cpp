#include "processors.h"

//#include <iostream>

#include <climits>
#include <math.h>

#include "../../pkg/adjust_pkg.h"

namespace pip {

const uint16_t CurveConverter::HOVER_THRESHOLD;

uint16_t CurveConverter::curve_convert(int16_t input, float exponent,
                                       uint16_t threshold) {
  if (input >= 0) {
    auto a = USHRT_MAX - threshold;
    auto b = float(input) / SHRT_MAX;
    auto c = pow(b, exponent);
    auto sol = uint16_t(a * c + threshold);
    /*printf("i: %hi, e: %f, t: %hu | %i | %f | %f -> %hu\n", input, exponent,
           threshold, a, b, c, sol);*/
    return sol;
  } else {
    // Fixes underflow issue
    input += 1;
    auto b = float(-input) / SHRT_MAX;
    auto c = pow(b, exponent);
    auto sol = (uint16_t)(threshold - (c * threshold));
    /*printf("i: %hi, e: %f, t: %hu | %f | %f -> %hu\n", input, exponent,
           threshold, b, c, sol);*/
    return sol;
  }
}

void CurveConverter::convert(Input &in, Output &out) {
  uint16_t base_speed = curve_convert(in.throttle, input_multi,
                                      HOVER_THRESHOLD + throttle_threshold);
  out.fl_motor = base_speed;
  out.fr_motor = base_speed;
  out.bl_motor = base_speed;
  out.br_motor = base_speed;

  int16_t rot_y = in.rotation_y * rotation_multi;
  int16_t rot_x = in.rotation_x * rotation_multi;
  int16_t rot_z = in.rotation_z * rotation_multi;

  out.bl_motor += rot_y;
  out.fl_motor += rot_y;
  out.br_motor -= rot_y;
  out.fr_motor -= rot_y;

  out.fr_motor += rot_x;
  out.fl_motor += rot_x;
  out.br_motor -= rot_x;
  out.bl_motor -= rot_x;

  out.fr_motor += rot_z;
  out.bl_motor += rot_z;
  out.br_motor -= rot_z;
  out.fl_motor -= rot_z;
}

void CurveConverter::handle_event(eve::BaseEvent *event) {
  if (event->event_type != eve::EventType::NET_PKG) {
    return;
  }
  auto net_event = (eve::NetEvent *)event;
  if (net_event->pkg->pkg_type == pkg::PkgType::Multiplier) {
    auto multi_pkg = (pkg::MultiplierPkg *)net_event->pkg;
    input_multi = 0.1 * multi_pkg->input_multi;
    rotation_multi = 0.1 * multi_pkg->rotation_multi;
  } else if (net_event->pkg->pkg_type == pkg::PkgType::ThresholdShift) {
    auto threshold_pkg = (pkg::ThresholdShiftPkg *)net_event->pkg;
    throttle_threshold = threshold_pkg->throttle_threshold;
  }
}

void CurveConverter::set_values(float input, float rotation, int16_t throttle) {
  input_multi = input;
  rotation_multi = rotation;
  throttle_threshold = throttle;
}

void InputShifter::add_short(int16_t *target, int16_t *val) {
  int32_t temp = *target + *val;
  if (temp >= SHRT_MAX) {
    *target = SHRT_MAX;
  } else if (temp <= SHRT_MIN) {
    *target = SHRT_MIN;
  } else {
    *target = temp;
  }
}

bool InputShifter::process(Input &in) {
  add_short(&in.rotation_x, &rotation_x_shift);
  add_short(&in.rotation_y, &rotation_y_shift);
  add_short(&in.rotation_z, &rotation_z_shift);
  return false;
}

void InputShifter::handle_event(eve::BaseEvent *event) {
  if (event->event_type != eve::EventType::NET_PKG) {
    return;
  }
  auto net_event = (eve::NetEvent *)event;
  if (net_event->pkg->pkg_type != pkg::PkgType::RotationShift) {
    return;
  }
  auto shift_pkg = (pkg::RotationShiftPkg *)net_event->pkg;
  rotation_x_shift = shift_pkg->rotation_x_shift;
  rotation_y_shift = shift_pkg->rotation_y_shift;
  rotation_z_shift = shift_pkg->rotation_z_shift;
}

void InputShifter::set_shifts(int16_t x, int16_t y, int16_t z) {
  rotation_x_shift = x;
  rotation_y_shift = y;
  rotation_z_shift = z;
}

} // namespace pip