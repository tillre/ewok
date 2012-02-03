#ifndef NODE_H_
#define NODE_H_

#include <vector>
#include "Matrix.h"


namespace ewok {


  class Node {
  public:
    Node()
      : childs(0)
    {
    }
    
    Vector3 position;
    Vector3 rotation;
    std::vector<Node*> childs;


    virtual void updateTransform()
    {
      Matrix43 m;
      updateTransform(m);
    }
    
    
    virtual void updateTransform(const Matrix43 &parent)
    {
      RotMatrix rot(rotation);
      Matrix43 transform(rot, position);

      // LogInfo << "node position: " << position.x << "/" << position.y << "/" << position.z;
      
      transform = parent * transform;
      updateLocal(transform);

      std::vector<Node*>::iterator it;
      for (it = childs.begin(); it != childs.end(); ++it) {
        (*it)->updateTransform(transform);
      }
    }


    virtual void updateLocal(const Matrix43 &transform)
    {
    }
  };


} // namespace ewok
  

#endif  // NODE_H_
