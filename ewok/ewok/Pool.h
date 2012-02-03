#ifndef POOL_H_
#define POOL_H_


namespace ewok {
  
  
  // ----------------------------------------------------------------------
  // Pool
  // ----------------------------------------------------------------------


  template<typename T>
  class Pool {
  public:
    Pool(unsigned numItems)
      : items_(numItems),
        nextIndex_(0)
    {
    }
    

    T &request()
    {
      unsigned i, j;
      unsigned l = items_.size();
      
      for (i = 0; i < l; ++i) {
        j = (i + nextIndex_) % l;
        T &item = items_[j];
        if (!item.isUsed()) {
          item.setUsed(true);
          nextIndex_ = (j + 1) % l;
          return item;
        }
      }
      
      LogWarn << "All items in pool are in use, trying to grow!";
      items_.push_back(T());
      T &newItem = items_[l];
      newItem.setUsed(true);
      nextIndex_ = 0;
      return newItem;
    }
    

    void release(T& item)
    {
      item.setUsed(false);
    }


    std::vector<T> &items()
    {
      return items_;
    }

  private:
    std::vector<T> items_;
    unsigned nextIndex_;
  };
    
  
  
} // namespace ewok


#endif // POOL_H_
