#ifndef MATRIX_H_
#define MATRIX_H_

#include "RotMatrix.h"
#include "Vector.h"


namespace ewok {


  // ----------------------------------------------------------------------  
  // column order 4x3 matrix
  // ----------------------------------------------------------------------

  
  class Matrix43 {
  public:
    float m11, m12, m13, tx;
    float m21, m22, m23, ty;
    float m31, m32, m33, tz;

    Matrix43()
      : m11(1.0f), m12(0.0f), m13(0.0f), tx(0.0f),
	m21(0.0f), m22(1.0f), m23(0.0f), ty(0.0f),
	m31(0.0f), m32(0.0f), m33(1.0f), tz(0.0f)
    {
    }
  
    Matrix43(float m11, float m12, float m13, float tx,
	     float m21, float m22, float m23, float ty,
	     float m31, float m32, float m33, float tz)
      : m11(m11), m12(m12), m13(m13), tx(tx),
	m21(m21), m22(m22), m23(m23), ty(ty),
	m31(m31), m32(m32), m33(m33), tz(tz)
    {
    }

    Matrix43(const RotMatrix &orient, const Vector3 &pos)
      : m11(orient.m11), m12(orient.m12), m13(orient.m13), tx(pos.x),
	m21(orient.m21), m22(orient.m22), m23(orient.m23), ty(pos.y),
	m31(orient.m31), m32(orient.m32), m33(orient.m33), tz(pos.z)
    {
    }


    void clear();
  };

  Vector3 operator*(const Matrix43 &m, const Vector3 &v);
  Vector3 &operator*=(Vector3 &v, const Matrix43 &m);
  
  Matrix43 operator*(const Matrix43 &a, const Matrix43 &b);

 
  // ----------------------------------------------------------------------    
  // column order 4x4 matrix
  // ----------------------------------------------------------------------

  
  class Matrix4 {
  public:
    float m11, m12, m13, m14;
    float m21, m22, m23, m24;
    float m31, m32, m33, m34;
    float m41, m42, m43, m44;

    Matrix4()
      : m11(1.0f), m12(0.0f), m13(0.0f), m14(0.0f),
	m21(0.0f), m22(1.0f), m23(0.0f), m24(0.0f),
	m31(0.0f), m32(0.0f), m33(1.0f), m34(0.0f),
	m41(0.0f), m42(0.0f), m43(0.0f), m44(1.0f)
    {
    }


    Matrix4(float m11, float m12, float m13, float m14,
            float m21, float m22, float m23, float m24,
            float m31, float m32, float m33, float m34,
            float m41, float m42, float m43, float m44)
      : m11(m11), m12(m12), m13(m13), m14(m14),
	m21(m21), m22(m22), m23(m23), m24(m24),
	m31(m31), m32(m32), m33(m33), m34(m34),
	m41(m41), m42(m42), m43(m43), m44(m44)
    {
    }

    
    Matrix4(const Matrix43 &m)
    : m11(m.m11), m12(m.m12), m13(m.m13), m14(m.tx),
      m21(m.m21), m22(m.m22), m23(m.m23), m24(m.ty),
      m31(m.m31), m32(m.m32), m33(m.m33), m34(m.tz),
      m41(0.0f),  m42(0.0f),  m43(0.0f),  m44(1.0f)
    {
    }
    
  };
  
} // namespace ewok
  

#endif  // MATRIX_H_
