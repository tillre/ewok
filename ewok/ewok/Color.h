#ifndef COLOR_H_
#define COLOR_H_



namespace ewok {
  
  class Vector3;
  

  Vector3 RGBtoHSV(const Vector3 &rgb);

  Vector3 HSVtoRGB(const Vector3 &hsv);
  
  
} // namespace ewok


#endif // COLOR_H_
