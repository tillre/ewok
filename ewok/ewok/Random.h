#ifndef RANDOM_H_
#define RANDOM_H_


#include "Vector.h"


namespace ewok {
  
  class Random {
  public:
    
    static void init()
    {
      srand(time(NULL));
    }
    
    
    static float randf()
    {
      return (float)rand() / (float)RAND_MAX;
    }
    
    
    static float randf(float min, float max)
    {
      return min + randf() * (max - min);
    }
    
    
    static int randi()
    {
      return rand() % INT_MAX;
    }
    
    
    static int randi(int min, int max)
    {
      return min + randi() % (max - min);
    }
    
    
    static Vector3 randv3(float min, float max)
    {
      return Vector3(randf(min, max), randf(min, max), randf(min, max));
    }


    static Vector3 randv3(const Vector3 &a, const Vector3 &b)
    {
      return Vector3(randf(a.x, b.x), randf(a.y, b.y), randf(a.z, b.z));
    }

  };
  
} // namespace ewok


#endif // RANDOM_H_
