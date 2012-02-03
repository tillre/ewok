#ifndef SPRITE_H_
#define SPRITE_H_

#include "Geom.h"
#include "Matrix.h"


namespace ewok {


  class Sprite {
  public:
    Sprite();

    virtual Quad vertices() const;

    virtual void setUsed(bool f);    
    virtual bool isUsed() const;
    
    Vector2 size;
    Vector3 pivot;
    
    float alpha;
    Vector3 colorTransform;
    Matrix43 transform;

    unsigned tileId;

  private:
    bool isUsed_;
  };
  
  
} // namespace ewok


#endif // SPRITE_H_
