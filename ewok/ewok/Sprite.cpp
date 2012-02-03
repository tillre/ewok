#include "Sprite.h"


namespace ewok {

  Sprite::Sprite()
    : alpha(1),
      colorTransform(1.0f, 1.0f, 1.0f),
      tileId(0),
      isUsed_(false)
  {
  }

    
  void Sprite::setUsed(bool u)
  {
    isUsed_ = u;
    if (!u) {
      pivot.clear();
      size.clear();
      transform.clear();
      alpha = 1;
      colorTransform = Vector3(1.0f, 1.0f, 1.0f);
      tileId = 0;
    }
  }

    
  bool Sprite::isUsed() const
  {
    return isUsed_;
  }

    
  Quad Sprite::vertices() const
  {
    Quad verts;
    
    verts.v1.x = -pivot.x;
    verts.v1.y = -pivot.y;
    verts.v1.z = -pivot.z;
      
    verts.v2.x = size.x - pivot.x;
    verts.v2.y = -pivot.y;
    verts.v2.z = -pivot.z;
      
    verts.v3.x = size.x - pivot.x;
    verts.v3.y = size.y - pivot.y;
    verts.v3.z = -pivot.z;
      
    verts.v4.x = -pivot.x;
    verts.v4.y = size.y - pivot.y;
    verts.v4.z = -pivot.z;

    verts.v1 *= transform;
    verts.v2 *= transform;
    verts.v3 *= transform;
    verts.v4 *= transform;
    
    return verts;
  }

} // namespace ewok
