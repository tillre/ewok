#ifndef VERTEX_H_
#define VERTEX_H_


#include "Vector.h"
#include "Log.h"


namespace ewok {


  struct ColorVertex {
    Vector3 position;
    Vector4 color;

    ColorVertex() {}
    ColorVertex(float x, float y, float z, float r, float g, float b, float a)
      : position(x, y, z), color(r, g, b, a) {}
  };


  struct TexVertex {
    Vector3 position;
    Vector2 texCoords;

    TexVertex() {}
    TexVertex(float x, float y, float z, float u, float v)
      : position(x, y, z), texCoords(u, v) {}
  };


} // namespace ewok


#endif  // VERTEX_H_
