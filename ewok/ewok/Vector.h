#ifndef VECTOR_H_
#define VECTOR_H_


#include "Log.h"


namespace ewok {

  // column vectors
    
  // -----------------------------------------------------------------------------
  // Vector2 - float
  // -----------------------------------------------------------------------------
    
    
  class Vector2 {
  public:
    float x, y;
        
    Vector2();
    Vector2(float n);
    Vector2(float x, float y);
    Vector2(const Vector2 &a);
        
    Vector2 &operator=(const Vector2 &a);
        
    Vector2 operator+(const Vector2 &a) const;
    Vector2 operator-(const Vector2 &a) const;
    Vector2 operator*(float s) const;
    float operator*(const Vector2 &a);
        
    Vector2 &operator+=(const Vector2 &a);
    Vector2 &operator-=(const Vector2 &a);
    Vector2 &operator*=(float s);
        
    bool operator==(const Vector2 &a) const;
    bool operator!=(const Vector2 &a) const;
        
    float magnitude();
    float squareMagnitude();
    void normalize();
    void invert();
    void clear();
  };
    
    
    
  // -----------------------------------------------------------------------------
  // Vector3 - float
  // -----------------------------------------------------------------------------
    
    
  class Vector3 {
  public:
    float x, y, z;
        
    Vector3();
    Vector3(float n);
    Vector3(float x, float y, float z);
    Vector3(const Vector3 &a);
        
    Vector3 &operator=(const Vector3 &a);
        
    Vector3 operator+(const Vector3 &a) const;
    Vector3 operator-(const Vector3 &a) const;
    Vector3 operator*(float s) const;
    float operator*(const Vector3 &a) const;    // dot product
    Vector3 operator%(const Vector3 &a)const;   // cross product
        
    Vector3 &operator+=(const Vector3 &a);
    Vector3 &operator-=(const Vector3 &a);
    Vector3 &operator*=(float s);
        
    bool operator==(const Vector3 &a) const;
    bool operator!=(const Vector3 &a) const;
        
    float magnitude();
    float squareMagnitude();
    void normalize();
    void invert();
    void clear();
  };
    
    
  // -----------------------------------------------------------------------------
  // Vector4 - float
  // -----------------------------------------------------------------------------
    
    
  class Vector4 {
  public:
    float x, y, z, w;
        
    Vector4();
    Vector4(float n);
    Vector4(float x, float y, float z, float w);
    Vector4(const Vector4 &a);
    Vector4(const Vector3 &a); // w will be 1
    
    Vector4 &operator=(const Vector4 &a);
    Vector4 &operator=(const Vector3 &a); // w will be 1
  };
    
    
  // -----------------------------------------------------------------------------
  // Vector2i - int
  // -----------------------------------------------------------------------------
    
    
  class Vector2i {
  public:
    int x, y;
        
    Vector2i();
    Vector2i(int n);
    Vector2i(int x, int y);
    Vector2i(const Vector2i &a);
  };
    
    
  // -----------------------------------------------------------------------------
  // Vector3i - int
  // -----------------------------------------------------------------------------
    
    
  class Vector3i {
  public:
    int x, y, z;
        
    Vector3i();
    Vector3i(int n);
    Vector3i(int x, int y, int z);
    Vector3i(const Vector3i &a);
  };
    
    
  // -----------------------------------------------------------------------------
  // Vector4i - int
  // -----------------------------------------------------------------------------
    
    
  class Vector4i {
  public:
    int x, y, z, w;
        
    Vector4i();
    Vector4i(int n);
    Vector4i(int x, int y, int z, int w);
    Vector4i(const Vector4i &a);
  };

    
} // namespace ewok


#endif  // VECTOR_H_
