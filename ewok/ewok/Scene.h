#ifndef SCENE_H_
#define SCENE_H_

#include "Application.h"


namespace ewok {


  class IScene {
  public:
    virtual void init(Application &app) = 0;
    
    virtual void attach() = 0;
    virtual void detach() = 0;
    virtual void update(float duration) = 0;
    
    virtual void touchBegin(const Touch &t) = 0;
    virtual void touchEnd(const Touch &t) = 0;

  };


} // namespace ewok

#endif  // SCENE_H_
