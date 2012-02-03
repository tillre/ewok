#ifndef PHYSICS_H_
#define PHYSICS_H_


#include <vector>
#include <algorithm>
#include "Log.h"


namespace ewok {

  class IPhysicsSystem {
  public:
    virtual void update(float duration) = 0;
  };
  
  
  class Physics {
  public:
    Physics() {}
    
    ~Physics()
    {
      std::vector<IPhysicsSystem*>::iterator it;
      for (it = systems_.begin(); it != systems_.end(); ++it) {
	delete (*it);
      }
    }
    

    void addSystem(IPhysicsSystem &s)
    {
      systems_.push_back(&s);
    }


    void removeSystem(IPhysicsSystem &s)
    {
      systems_.erase(std::remove(systems_.begin(), systems_.end(), &s),
                     systems_.end());
    }
    

    void update(float duration)
    {
      if (duration == 0.0)
        duration = 0.000001f;
      
      std::vector<IPhysicsSystem*>::iterator it;
      for (it = systems_.begin(); it != systems_.end(); ++it) {
        (*it)->update(duration);
      }
    }
  
  private:
    Physics(Physics &copy) {}
    Physics &operator=(const Physics &other) { return *this; }
    
    std::vector<IPhysicsSystem*> systems_;
  };

  
} // namespace ewok


#endif // PHYSICS_H_
