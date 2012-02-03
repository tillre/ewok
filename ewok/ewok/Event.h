#ifndef EVENT_H_
#define EVENT_H_


namespace ewok {
  

  class Event;

  
  // -----------------------------------------------------------------------------
  // IEventDelegate
  // -----------------------------------------------------------------------------

  class IEventDelegate {
    friend class Event;
  private:
    virtual void operator()() = 0;
    virtual void attach(Event *e) = 0;
    virtual void detach(Event *e) = 0;
  };


  // -----------------------------------------------------------------------------
  // Event
  // -----------------------------------------------------------------------------

  class Event {
  public:
    Event()
      : delegate_(NULL)
    {
    }

  
    ~Event()
    {
      if (delegate_) {
        delegate_->detach(this);
      }
    }
  

    void set(IEventDelegate *del)
    {
      Assert(delegate_ == NULL, "Delegate has already been set");
      delegate_ = del;
      delegate_->attach(this);
    }

  
    void dispatch()
    {
      if (delegate_) (*delegate_)();
    }
  

  private:
    IEventDelegate *delegate_;
  };



  // -----------------------------------------------------------------------------
  // EventDelegate
  // -----------------------------------------------------------------------------


  template<typename T>
  class EventDelegate : public IEventDelegate
  {
    typedef void (T::*Func)();
  public:
    EventDelegate(T *obj, Func c)
      : obj_(obj), func_(c), event_(NULL)
    {
    }

    ~EventDelegate()
    {
      if (event_) {
        event_->set(NULL);
      }
    }
  
  private:
    virtual void attach(Event *event)
    {
      Assert(event_ == NULL, "Already an Event attached");
      event_ = event;
    }


    virtual void detach(Event *event)
    {
      event_ = NULL;
    }
  
  
    virtual void operator()()
    {
      if (obj_) {
        (obj_->*func_)();
      }
    }

    EventDelegate(const EventDelegate<T> &other) {}
    EventDelegate<T> &operator=(const EventDelegate<T> other) { return *this; }
  
    T *obj_;
    Func func_;
    Event* event_;
  };

  
} // namespace ewok


#endif // EVENT_H_
