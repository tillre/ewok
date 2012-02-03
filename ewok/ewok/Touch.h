#ifndef TOUCH_H_
#define TOUCH_H_


namespace ewok {


  class Touch {
  public:
    float x;
    float y;
    
    Touch(float x, float y) : x(x), y(y) {}
  };
  
  
} // namespace ewok


#endif // TOUCH_H_
