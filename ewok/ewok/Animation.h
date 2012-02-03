#ifndef ANIMATION_H_
#define ANIMATION_H_


#include <list>
#include "Event.h"



namespace ewok {


  // -----------------------------------------------------------------------------
  // IAnimation
  // -----------------------------------------------------------------------------


  class IAnimation {
  public:
    virtual bool update(float duration) = 0;
  };


  // -----------------------------------------------------------------------------
  // Animation
  // -----------------------------------------------------------------------------


  template<typename ValueT, typename T>
  class Animation : public IAnimation
  {
    typedef ValueT (T::*ValueGetter)();
    typedef void (T::*ValueSetter)(ValueT v);
  public:
    Animation(T *obj,
              ValueGetter getter,
              ValueSetter setter,
              ValueT endValue,
              float duration)
      : obj_(obj),
        getter_(getter),
        setter_(setter),
        endValue_(endValue),
        duration_(duration),
        time_(0),
        complete_(false)
    {
    }


    virtual bool update(float duration)
    {
      if (time_ == 0) {
        startValue_ = (obj_->*getter_)();
      }
      time_ += duration;
      if (time_ >= duration_) {
        time_ = duration_;
        complete_ = true;
      }

      float n = time_ / duration_;
      ValueT v = startValue_ + (endValue_ - startValue_) * n;
      (obj_->*setter_)(v);
    
      if (complete_) onComplete.dispatch();
      return !complete_;
    }


    Event onComplete;
  
  
  private:
    T *obj_;
    ValueGetter getter_;
    ValueSetter setter_;

    float duration_;
    float time_;
  
    ValueT startValue_;
    ValueT endValue_;

    bool complete_;
  };


  // -----------------------------------------------------------------------------
  // Animations
  // -----------------------------------------------------------------------------


  class Animations {
  public:

    void add(IAnimation *ani)
    {
      animations_.push_back(ani);
    }

    void update(float duration)
    {
      std::list<IAnimation*>::iterator it;
      for (it = animations_.begin(); it != animations_.end(); ++it) {
        if (!(*it)->update(duration)) {
          IAnimation *a = *it;
          animations_.erase(it--);
          delete a;
        }
      }
    }

  private:
    std::list<IAnimation*> animations_;
  };


} // namespace ewok


#endif // ANIMATION_H_
