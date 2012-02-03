#ifndef MATHUTIL_H_
#define MATHUTIL_H_

#include "math.h"

namespace ewok {

  const float kPi = 3.14159265f;
  const float k2Pi = kPi * 2.0f;
  const float kPiOver2 = kPi / 2.0f;
  const float k1OverPi = 1.0f / kPi;
  const float k1Over2Pi = 1.0f / k2Pi;

  // wrap between -pi...pi

  extern float WrapPi(float theta);

  // save inverse acos

  extern float SafeAcos(float x);

} // namespace ewok

#endif  // MATHUTIL_H_
