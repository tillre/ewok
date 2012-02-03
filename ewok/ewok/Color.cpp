#include "color.h"

#include <cmath>
#include "vector.h"
#include "Log.h"


namespace ewok {
  

  Vector3 RGBtoHSV(const Vector3 &rgb)
  {
    float r = rgb.x;
    float g = rgb.y;
    float b = rgb.z;

    float max = r > g && r > b ? r
      : g > r && g > b ? g
      : b;
    
    float min = r < g && r < b ? r
      : g < r && g < b ? g
      : b;

    float v = max;
    float s = v > 0.0f ? (max - min) / max : 0.0f;
    float h = 0.0f;

    if (s > 0) {
      float h = r == max ?     (g - b) / (max - min)
              : g == max ? 2 + (b - r) / (max - min)
              :            4 + (r - g) / (max - min);
      h *= 60;
      if (h < 0) h += 360;
    }
    return Vector3(h, s, v);
  }

  
  Vector3 HSVtoRGB(const Vector3 &hsv)
  {
    float h = hsv.x;
    float s = hsv.y;
    float v = hsv.z;

    int hi = int(floor(h / 60.0f)) % 6;
    float f =  (h / 60.0f) - floor(h / 60.0f);
    float p = v * (1.0f - s);
    float q = v * (1.0f - (f*s));
    float t = v * (1.0f - ((1.0f - f) * s));

    switch(hi) {
    case 0: return Vector3(v, t, p);
    case 1: return Vector3(q, v, p);
    case 2: return Vector3(p, v, t);
    case 3: return Vector3(p, q, v);
    case 4: return Vector3(t, p, v);
    case 5: return Vector3(v, p, q);
    default:
      LogWarn << "HSV to RGB BUGBUG BUG BUG BUG";
      return Vector3(0, 0, 0);
    }
  }
  
  
} // namespace ewok
