#include "RotMatrix.h"

#include <cmath>
#include "Vector.h"


namespace ewok {


  RotMatrix::RotMatrix(const Vector3 &orient)
  {
    setOrientation(orient);
  }


  void RotMatrix::setOrientation(const Vector3 &orient)
  {
    float sx = sin(orient.x); float cx = cos(orient.x);
    float sy = sin(orient.y); float cy = cos(orient.y);
    float sz = sin(orient.z); float cz = cos(orient.z);

    m11 = cy*cz;
    m12 = -cx*sz + sx*sy*cz;
    m13 = sx*sz + cx*sy*cz;

    m21 = cy*sz;
    m22 = cx*cz + sx*sy*sz;
    m23 = -sx*cz + cx*sy*sz;

    m31 = -sy;
    m32 = sx*cy;
    m33 = cx*cy;
  }


} // namespace ewok
