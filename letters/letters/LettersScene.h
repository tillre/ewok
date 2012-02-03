#ifndef LETTERSSCENE_H_
#define LETTERSSCENE_H_


#include <map>
#include <string>
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "TextureAtlas.h"
#include "FrameAnimation.h"
#include "Pool.h"
#include "Particle.h"
#include "Random.h"
#include "Color.h"


namespace letters {

  using namespace ewok;

  
  // ----------------------------------------------------------------------
  // LetterParticle
  // ----------------------------------------------------------------------
  
  
  class LetterParticle : public Particle {
  public:

    virtual bool update(float duration)
    {
      Particle::update(duration);
      
      age_ -= duration;
      alpha = hasAlpha_ ? age_ / startAge_ : 1.0;
      return age_ > 0;
    }

    
    void setAge(float a) {
      age_ = a;
      startAge_ = a;
    }

    
    float age() const {
      return age_;
    }

    
    void setHasAlpha(bool b) {
      hasAlpha_ = b;
    }
    

  private:
    float age_;
    float startAge_;
    bool hasAlpha_;
  };


  // ----------------------------------------------------------------------
  // LetterRule
  // ----------------------------------------------------------------------

  
  class LetterRule : public ParticleRule<LetterParticle> {
  public:
    LetterRule()
      : payloadCount_(0),
        payloadType_(0),
        nextTileId_(0)
    {
    }

    
    void init(float minAge, float maxAge,
              const Vector3 &minVelocity, const Vector3 &maxVelocity,
              unsigned payloadCount, unsigned payloadType)
    {
      minAge_ = minAge;
      maxAge_ = maxAge;
      minVelocity_ = minVelocity;
      maxVelocity_ = maxVelocity;
      payloadCount_ = payloadCount;
      payloadType_ = payloadType;

      hsv_.x = 0.0f;
      hsv_.y = 1.0f;
      hsv_.z = 1.0f;
    }

    
    virtual void onParticleInit(LetterParticle &particle) 
    {
      particle.size = Vector2(64, 64);
      particle.pivot = Vector3(32, 32, 0);
      
      particle.position = Vector3(0, -300, 0);
      particle.velocity = Random::randv3(minVelocity_, maxVelocity_);
      particle.acceleration = Vector3(0, -15, 0);

      float xrot = Random::randf(-1.5f, 1.5f);
      float yrot = Random::randf(-1.5f, 1.5f);
      float zrot = Random::randf(-3.0f, 3.0f)
        * (particle.velocity.x > 0 ? -1.0f : 1.0f);
      
      particle.rotation = Vector3(0, 0, 0);
      particle.rotVelocity = Vector3(xrot, yrot, zrot);
      particle.rotAcceleration = Vector3(0, 0, -0.05f);
      
      particle.setAge(Random::randf(minAge_, maxAge_));
      particle.setHasAlpha(id_ != 0);
      particle.setMass(1);

      if (particle.type() == 0) {
        particle.tileId = nextTileId_;
        nextTileId_ = (nextTileId_ + 1) % 26;

        hsv_.x = std::fmod(hsv_.x + 0.5f, 360.0f);
        particle.colorTransform = HSVtoRGB(hsv_);
      }
    }


    virtual void onParticleDeinit(LetterParticle &particle)
    {
      for (unsigned i = 0; i < payloadCount_; ++i) {
        Particle &p = system_->create(payloadType_);
        p.position = particle.position;
        p.rotation = particle.rotation;
        p.velocity += particle.velocity;
        p.tileId = particle.tileId;
        p.colorTransform = particle.colorTransform;
        
        // hack to overcome that render will be called before the
        // update method of this newly created particle is called
        p.update(0.0001f);
      }
    }
    
  private:
    float minAge_;
    float maxAge_;

    Vector3 minVelocity_;
    Vector3 maxVelocity_;

    Vector3 hsv_;

    unsigned payloadCount_;
    int payloadType_;

    unsigned nextTileId_;
  };

  
  // ----------------------------------------------------------------------
  // LetterScene
  // ----------------------------------------------------------------------
  
  
  class LettersScene : public IScene {
  public:
    LettersScene()
      : app_(NULL),
        letterPool_(512),
        renderer_(512),
        emitTime_(0)
    {}


    virtual void init(Application &app)
    {
      LogInfo << "LettersScene init";
      app_ = &app;
      resources_.init(app_->resources());

      LuaScript script = app.resources().loadScript("letters.lua");

      script.registerMemberFunction<LettersScene, LuaPointer<ResourceGroup>,
                                    &LettersScene::resources>("scene_getResourceManager");
      
      script.registerMemberFunction<ResourceGroup, LuaString, LuaString,
                                    &ResourceGroup::scriptPath>("resman_getScriptPath");

      script.registerMemberFunction<ResourceGroup, LuaString,
                                    &ResourceGroup::loadTexture>("resman_loadTexture");

      script.registerMemberFunction<ResourceGroup, LuaPointer<TextureAtlas>, LuaString, LuaString, LuaUInt,
                                    &ResourceGroup::makeTextureAtlas>("resman_makeTextureAtlas");

      script.registerMemberFunction<TextureAtlas, LuaUInt, LuaFloat, LuaFloat, LuaFloat, LuaFloat,
                                    &TextureAtlas::setTile>("texatlas_setTile");

      script.registerMemberFunction<ResourceGroup, LuaPointer<FrameAnimation>, LuaString, LuaUInt,
                                    &ResourceGroup::makeFrameAnimation>("resman_makeFrameAnimation");
      
      script.registerMemberFunction<FrameAnimation, LuaUInt, LuaUInt, LuaFloat,
                                    &FrameAnimation::setFrame>("frameani_setFrame");

      script.call<LuaPointer<LettersScene> >("init", this);
      
      
      Shader vsh = app.resources().loadVertexShader("letters.vsh");
      Shader fsh = app.resources().loadFragmentShader("letters.fsh");

      const TextureAtlas &lettersAtlas = resources_.getAtlas("letters");
      renderer_.init(vsh, fsh, lettersAtlas);
      
      
      const float width  = 320.0f;
      const float height = 480.0f;
      const float depth  = (width + height) / 2.0f;

      // normalized device coordinates
      const float m11 = 2.0f / width;
      const float m22 = 2.0f / height;
      const float m33 = 2.0f / depth;

      // projection
      const float m34 = 2.0f / depth;
      
      Matrix4 mvp(m11,  0.0f, 0.0f,  0.0f,
                  0.0f, m22,  0.0f,  0.0f,
                  0.0f, 0.0f, m33,   m34,
                  0.0f, 0.0f, 0.0f,  1.0f);
      renderer_.setProjection(mvp);

      bg_ = &letterPool_.request();
      bg_->size = Vector2(width, height);
      bg_->pivot = Vector3(width / 2, height / 2, 0);
      bg_->tileId = 63;
      bg_->alpha = 0.2f;
      bg_->colorTransform = Vector3(0.0f, 0.0f, 0.0f);
      
      psys_.init(2, letterPool_);

      LetterRule &rule1 = psys_.getRule(0);
      rule1.init(2.0, 4.0,
                 Vector3(-50, 100, -20),
                 Vector3(50, 150, 20),
                 3, 1
                 );
      
      
      LetterRule &rule2 = psys_.getRule(1);
      rule2.init(1.0, 2.0,
                 Vector3(-50, -100, -100),
                 Vector3(50, 20, 100),
                 0, 0
                 );
    }


    virtual void attach()
    {
      LogInfo << "LettersScene attach";

      app_->physics().addSystem(psys_);      
      app_->renderer().addRenderable(renderer_);
      app_->renderer().enableCulling(false);
      app_->renderer().enableClearing(false);
    }

    
    virtual void detach()
    {
      LogInfo << "LettersScene detach";

      app_->physics().removeSystem(psys_);
      app_->renderer().removeRenderable(renderer_);
    }


    virtual void update(float duration)
    {
      // emitTime_ += duration;
      // if (emitTime_ > 0.1f) {
      //   psys_.create(0);
      //   emitTime_ = 0.0f;
      // }

      psys_.create(0);
      psys_.update(duration);
      
      renderer_.update(letterPool_.items());
    }

    
    virtual void touchBegin(const Touch &t)
    {
    }

    
    virtual void touchEnd(const Touch &t)
    {
    }
    

    ResourceGroup *resources()
    {
      return &resources_;
    }
    
    
  private:
    ResourceGroup resources_;

    Application *app_;

    Pool<LetterParticle> letterPool_;
    LetterParticle *bg_;
    
    SpriteRenderer<LetterParticle> renderer_;

    ParticleSystem<LetterParticle, LetterRule> psys_;
    float emitTime_;
  };
  
  
} // namespace letters


#endif // LETTERSSCENE_H_
