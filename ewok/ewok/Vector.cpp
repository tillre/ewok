#include "Vector.h"

#include <cmath>


namespace ewok {
    
    
  // -----------------------------------------------------------------------------
  // Vector2 - float
  // -----------------------------------------------------------------------------
    
    
  Vector2::Vector2() : x(0), y(0) {}
    
  Vector2::Vector2(float n) : x(n), y(n) {}
    
  Vector2::Vector2(float x, float y) : x(x), y(y) {}
    
  Vector2::Vector2(const Vector2 &a) : x(a.x), y(a.y) {}
    
    
  Vector2 &Vector2::operator=(const Vector2 &a) {
    x = a.x, y = a.y;
    return *this;
  }
    
    
  Vector2 Vector2::operator+(const Vector2 &a) const {
    return Vector2(x + a.x, y + a.y);
  }
    
    
  Vector2 Vector2::operator-(const Vector2 &a) const {
    return Vector2(x - a.x, y - a.y);
  }
    
    
  Vector2 Vector2::operator*(float s) const {
    return Vector2(s * x, s * y);
  }
    
    
  // dot product
  float Vector2::operator*(const Vector2 &a) {
    return x * a.x + y * a.y;
  }
    
    
  Vector2 &Vector2::operator+=(const Vector2 &a) {
    x += a.x; y += a.y;
    return *this;
  }
    
    
  Vector2 &Vector2::operator-=(const Vector2 &a) {
    x -= a.x; y -= a.y;
    return *this;
  }
    
    
  Vector2 &Vector2::operator*=(float s) {
    x *= s; y *= s;
    return *this;
  }

    
    
  bool Vector2::operator==(const Vector2 &a) const {
    return x == a.x && y == a.y;
  }
    
    
  bool Vector2::operator!=(const Vector2 &a) const {
    return x != a.x || y != a.y;
  }
    
  float Vector2::magnitude() {
    float l = x * x + y * y;
    if (l != 0.0f) {
      l = sqrtf(l);
    }
    return l;
  }
    
  float Vector2::squareMagnitude() {
    return x * x + y * y;
  }
    
  void Vector2::normalize() {
    float l = magnitude();
    if (l != 0.0f) {
      x /= l;
      y /= l;
    }
  }
    
  void Vector2::invert() {
    x = -x;
    y = -y;
  }

  void Vector2::clear() {
    x = 0;
    y = 0;
  }
    
  // -----------------------------------------------------------------------------
  // Vector3 - float
  // -----------------------------------------------------------------------------
    
    
  Vector3::Vector3() : x(0), y(0), z(0) {}
    
  Vector3::Vector3(float n) : x(n), y(n), z(n) {}
    
  Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
    
  Vector3::Vector3(const Vector3 &a) : x(a.x), y(a.y), z(a.z) {}
    
    
  Vector3 &Vector3::operator=(const Vector3 &a) {
    x = a.x, y = a.y, z = a.z;
    return *this;
  }
    
    
  Vector3 Vector3::operator+(const Vector3 &a) const {
    return Vector3(x + a.x, y + a.y, z + a.z);
  }
    
    
  Vector3 Vector3::operator-(const Vector3 &a) const {
    return Vector3(x - a.x, y - a.y, z - a.z);
  }
    
    
  Vector3 Vector3::operator*(float s) const {
    return Vector3(x * s, y * s, z * s);
  }
    
    

  float Vector3::operator*(const Vector3 &a) const {
    return x * a.x + y * a.y + z * a.z;
  }
    

  Vector3 Vector3::operator%(const Vector3 &a) const {
    return Vector3(y * a.z - z * a.y,
                   z * a.x - x * a.z,
                   x * a.y - y * a.x);
  }
    
    
  Vector3 &Vector3::operator+=(const Vector3 &a) {
    x += a.x; y += a.y; z += a.z;
    return *this;
  }
    
    
  Vector3 &Vector3::operator-=(const Vector3 &a) {
    x -= a.x; y -= a.y; z -= a.z;
    return *this;
  }
    
    
  Vector3 &Vector3::operator*=(float s) {
    x *= s; y *= s; z *= s;
    return *this;
  }
    
    
  bool Vector3::operator==(const Vector3 &a) const {
    return x == a.x && y == a.y && z == a.z;
  }
    
    
  bool Vector3::operator!=(const Vector3 &a) const {
    return x != a.x || x != a.y || x != a.z;
  }
    
    
  float Vector3::magnitude() {
    float l = x * x + y * y + z * z;
    if (l != 0.0f) {
      l = sqrtf(l);
    }
    return l;
  }
    
    
  float Vector3::squareMagnitude() {
    return x * x + y * y + z * z;
  }
    
    
  void Vector3::normalize() {
    float l = magnitude();
    if (l != 0.0f) {
      x /= l;
      y /= l;
      z /= l;
    }
  }
    
    
  void Vector3::invert() {
    x = -x;
    y = -y;
    z = -z;
  }
    

  void Vector3::clear() {
    x = 0;
    y = 0;
    z = 0;
  }

  
  // -----------------------------------------------------------------------------
  // Vector4 - float
  // -----------------------------------------------------------------------------
    
    
  Vector4::Vector4() : x(0), y(0), z(0), w(0) {}
    
  Vector4::Vector4(float n) : x(n), y(n), z(n), w(n) {}
    
  Vector4::Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
    
  Vector4::Vector4(const Vector4 &a) : x(a.x), y(a.y), z(a.z), w(a.w) {}
  
  Vector4::Vector4(const Vector3 &a) : x(a.x), y(a.y), z(a.z), w(1) {}
  
  Vector4 &Vector4::operator=(const Vector4 &a) {
    x = a.x, y = a.y, z = a.z; w = a.w;
    return *this;
  }
  
  Vector4 &Vector4::operator=(const Vector3 &a) {
    x = a.x, y = a.y, z = a.z; w = 1;
    return *this;
  }
  
  // -----------------------------------------------------------------------------
  // Vector2i - int
  // -----------------------------------------------------------------------------
    
    
  Vector2i::Vector2i() : x(0), y(0) {}
    
  Vector2i::Vector2i(int n) : x(n), y(n) {}
    
  Vector2i::Vector2i(int x, int y) : x(x), y(y) {}
    
  Vector2i::Vector2i(const Vector2i &a) : x(a.x), y(a.y) {}
    
    
  // -----------------------------------------------------------------------------
  // Vector3i - int
  // -----------------------------------------------------------------------------
    
  Vector3i::Vector3i() : x(0), y(0), z(0) {}
    
  Vector3i::Vector3i(int n) : x(n), y(n), z(n) {}
    
  Vector3i::Vector3i(int x, int y, int z) : x(x), y(y), z(z) {}
    
  Vector3i::Vector3i(const Vector3i &a) : x(a.x), y(a.y), z(a.z) {}
    
    
  // -----------------------------------------------------------------------------
  // Vector4i - int
  // -----------------------------------------------------------------------------
    
  Vector4i::Vector4i() : x(0), y(0), z(0), w(0) {}
    
  Vector4i::Vector4i(int n) : x(n), y(n), z(n), w(n) {}
    
  Vector4i::Vector4i(int x, int y, int z, int w) : x(x), y(y), z(z), w(w) {}
    
  Vector4i::Vector4i(const Vector4i &a) : x(a.x), y(a.y), z(a.z), w(a.w) {}
    
    
    
    
} // namespace ewok
