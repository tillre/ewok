#ifndef FRAMEANIMATION_H_
#define FRAMEANIMATION_H_

#include <vector>
#include <map>
#include "Sprite.h"


namespace ewok {


  class Frame {
  public:
    unsigned id;
    float duration;
  };
  
  
  // ----------------------------------------------------------------------
  // FrameAnimation
  // ----------------------------------------------------------------------


  class FrameAnimation {
  public:
    FrameAnimation();
    
    void init(unsigned numFrames);

    void setFrame(unsigned index, unsigned id, float duration);
    
    const Frame &getFrame(unsigned index) const;

    unsigned numFrames() const;
    
  private:
    std::vector<Frame> frames_;
  };


  // ----------------------------------------------------------------------
  // FrameAnimationPlayer
  // ----------------------------------------------------------------------
  

  class FrameAnimationPlayer {
  public:

    FrameAnimationPlayer();
        
    void play(const FrameAnimation &ani, bool loop);

    bool update(float duration, Sprite *sprite);

  private:
    const FrameAnimation *ani_;
    unsigned frameNumber_;
    float frameTime_;
    bool loop_;
    bool running_;
  };
  

  // ----------------------------------------------------------------------
  // FrameAnimationGroup
  // ----------------------------------------------------------------------


  class FrameAnimationGroup {
    typedef std::map<std::string, FrameAnimation> Map;
    typedef std::pair<std::string, FrameAnimation> MapItem;
    
  public:
    FrameAnimationGroup();

    FrameAnimation &makeAnimation(const std::string &name, unsigned numTiles);

    const FrameAnimation &getAnimation(const std::string &name);
    
  private:
    Map animations_;
  };
  
  
} // namespace ewok


#endif // FRAMEANIMATION_H_
