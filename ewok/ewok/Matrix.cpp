#include "Matrix.h"


namespace ewok {


  void Matrix43::clear()
  {
    m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;
    m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
    m31 = 0.0f; m32 = 0.0f; m33 = 0.0f;
  }

  
  Vector3 operator*(const Matrix43 &m, const Vector3 &v)
  {
    return Vector3(m.m11*v.x + m.m12*v.y + m.m13*v.z + m.tx,
                   m.m21*v.x + m.m22*v.y + m.m23*v.z + m.ty,
                   m.m31*v.x + m.m32*v.y + m.m33*v.z + m.tz);
  }


  Vector3 &operator*=(Vector3 &v, const Matrix43 &m)
  {
    v = m * v;
    return v;
  }
  

  Matrix43 operator*(const Matrix43 &a, const Matrix43 &b)
  {
    return Matrix43(a.m11*b.m11 + a.m12*b.m21 + a.m13*b.m31,
                    a.m11*b.m12 + a.m12*b.m22 + a.m12*b.m32,
                    a.m11*b.m13 + a.m12*b.m23 + a.m13*b.m33,
                    a.m11*b.tx + a.m12*b.ty + a.m13*b.tz + a.tx,
                    
                    a.m21*b.m11 + a.m22*b.m21 + a.m23*b.m31,
                    a.m21*b.m12 + a.m22*b.m22 + a.m23*b.m32,
                    a.m21*b.m13 + a.m22*b.m23 + a.m23*b.m33,                    
                    a.m21*b.tx + a.m22*b.ty + a.m23*b.tz + a.ty,

                    a.m31*b.m11 + a.m32*b.m21 + a.m33*b.m31,
                    a.m31*b.m12 + a.m32*b.m22 + a.m33*b.m32,
                    a.m31*b.m13 + a.m32*b.m23 + a.m33*b.m33,
                    a.m31*b.tx + a.m32*b.ty + a.m33*b.tz + a.tz);
  }
  

} // namespace ewok
