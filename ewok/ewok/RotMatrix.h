#ifndef ROTMATRIX_H_
#define ROTMATRIX_H_


namespace ewok {


  class Vector3;

  
  // column order matrix

  class RotMatrix {
  public:
    float m11, m12, m13;
    float m21, m22, m23;
    float m31, m32, m33;

    
    RotMatrix()
      : m11(1.0f), m12(0.0f), m13(0.0f),
	m21(0.0f), m22(1.0f), m23(0.0f),
	m31(0.0f), m32(0.0f), m33(1.0f) {}

    
    RotMatrix(float m11, float m12, float m13,
	      float m21, float m22, float m23,
	      float m31, float m32, float m33)
      : m11(m11), m12(m12), m13(m13),
	m21(m21), m22(m22), m23(m23),
	m31(m31), m32(m32), m33(m33) {}

    RotMatrix(const Vector3 &orient);

    void setOrientation(const Vector3 &orient);
  };


} // namespace
  

#endif  // ROTMATRIX_H_
