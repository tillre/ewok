#include "Frameanimation.h"



namespace ewok {
  
  
  // ----------------------------------------------------------------------
  // FrameAnimation
  // ----------------------------------------------------------------------

  
  FrameAnimation::FrameAnimation()
    : frames_(0)
  {
  }

    
  void FrameAnimation::init(unsigned numFrames)
  {
    frames_.resize(numFrames);
  }


  void FrameAnimation::setFrame(unsigned index, unsigned id, float duration)
  {
    Assert(index < frames_.size(), "Index out of bounds");
    Frame &f = frames_[index];
    f.id = id;
    f.duration = duration;
  }
    
    
  const Frame &FrameAnimation::getFrame(unsigned index) const
  {
    Assert(index < frames_.size(), "Index out of bounds");
    return frames_[index];
  }


  unsigned FrameAnimation::numFrames() const
  {
    return frames_.size();
  }

  
  // ----------------------------------------------------------------------
  // FrameAnimationPlayer
  // ----------------------------------------------------------------------
  

  FrameAnimationPlayer::FrameAnimationPlayer()
    : ani_(NULL),
      frameNumber_(0),
      frameTime_(0),
      loop_(false),
      running_(false)
  {
  }
        

  void FrameAnimationPlayer::play(const FrameAnimation &ani, bool loop)
  {
    if (ani.numFrames() == 0) {
      LogWarn << "Animation has 0 frames, will not try to play it";
      return;
    }
    ani_ = &ani;
    loop_ = loop;
    frameNumber_ = 0;
    frameTime_ = 0;
    running_ = true;
  }

    
  bool FrameAnimationPlayer::update(float duration, Sprite *sprite)
  {
    if (running_) {
      const Frame &f = ani_->getFrame(frameNumber_);
      sprite->tileId = f.id;

      frameTime_ += duration;
      if (frameTime_ >= f.duration) {
        frameTime_ = 0;

        if (++frameNumber_ >= ani_->numFrames()) {
          frameTime_ = 0;
          frameNumber_ = 0;

          if (!loop_) {
            running_ = false;
            return false;
          }
        }
      }
      return true;
    }
    else {
      return false;
    }
  }

  
  // ----------------------------------------------------------------------
  // FrameAnimationGroup
  // ----------------------------------------------------------------------


  FrameAnimationGroup::FrameAnimationGroup()
  {
  }


  FrameAnimation &FrameAnimationGroup::makeAnimation(const std::string &name, unsigned numTiles)
  {
    Assert(animations_.find(name) == animations_.end(), "Animation already in group");
    FrameAnimation &ani = animations_[name];
    ani.init(numTiles);
    return ani;
  }
    

  const FrameAnimation &FrameAnimationGroup::getAnimation(const std::string &name)
  {
    Assert(animations_.find(name) != animations_.end(), "Animation is not in group");
    return animations_[name];
  }
  
  
} // namespace ewok
