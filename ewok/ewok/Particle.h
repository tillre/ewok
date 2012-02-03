#ifndef PARTICLE_H_
#define PARTICLE_H_


#include "Vector.h"
#include "Renderable.h"
#include "Texture.h"
#include "Physics.h"
#include "RenderAttribs.h"
#include "RenderProgram.h"
#include "RenderBuffer.h"
#include "Sprite.h"
#include "Pool.h"


namespace ewok {


  // ----------------------------------------------------------------------
  // Particle
  // ----------------------------------------------------------------------

  
  class Particle : public Sprite {
  public:
    Particle();

    virtual bool update(float duration);
    virtual void integrate(float duration);

    virtual void setMass(float m);
    
    virtual void setType(int type);
    virtual int type() const;
    
    virtual void setUsed(bool u); // overwrite

    Vector3 position;
    Vector3 velocity;
    Vector3 acceleration;
    Vector3 forces;
    
    Vector3 rotation;
    Vector3 rotVelocity;
    Vector3 rotAcceleration;
    Vector3 rotForces;

    float damping;
    
  protected:
    float inverseMass_;

    int type_;
  };


  // ----------------------------------------------------------------------
  // IParticleSystem
  // ----------------------------------------------------------------------

  
  template<typename ParticleT>
  class IParticleSystem : public IPhysicsSystem
  {
  public:
    virtual ParticleT &create(int ruleId) = 0;
  };


  // ----------------------------------------------------------------------
  // ParticleRule
  // ----------------------------------------------------------------------

  
  template<typename ParticleT>
  class ParticleRule
  {
  public:
    virtual void registerWithSystem(int id, IParticleSystem<ParticleT> &system);
    
    virtual void onParticleInit(ParticleT &particle);
    virtual void onParticleDeinit(ParticleT &particle);
    
  protected:  
    int id_;
    IParticleSystem<ParticleT> *system_;
  };

    
  template<typename ParticleT>
  void ParticleRule<ParticleT>::registerWithSystem(int id, IParticleSystem<ParticleT> &system)
  {
    id_ = id;
    system_ = &system;
  }

  
  template<typename ParticleT>  
  void ParticleRule<ParticleT>::onParticleInit(ParticleT &particle)
  {
  }

  
  template<typename ParticleT>  
  void ParticleRule<ParticleT>::onParticleDeinit(ParticleT &particle)
  {
  }


  // ----------------------------------------------------------------------
  // ParticleSystem
  // ----------------------------------------------------------------------


  template<typename ParticleT, typename RuleT>
  class ParticleSystem : public IParticleSystem<ParticleT>
  {
  public:
    ParticleSystem();
    
    void init(unsigned numRules, Pool<ParticleT> &particles);
  
    RuleT &getRule(int ruleId);
  
    ParticleT &create(int ruleId);

    void update(float duration);
  
  private:
    Pool<ParticleT> *particles_;
    std::vector<RuleT> rules_;
  };


  template<typename ParticleT, typename RuleT>
  ParticleSystem<ParticleT, RuleT>::ParticleSystem()
    : particles_(NULL),
      rules_(0)
  {
  }


  template<typename ParticleT, typename RuleT>
  void ParticleSystem<ParticleT, RuleT>::init(unsigned numRules, Pool<ParticleT> &particles)
  {
    rules_.resize(numRules);
    particles_ = &particles;
    
    typename std::vector<RuleT>::iterator it;
    int i = 0;
    for (it = rules_.begin(); it != rules_.end(); ++it) {
      it->registerWithSystem(i++, *this);
    }
  }


  template<typename ParticleT, typename RuleT>  
  RuleT &ParticleSystem<ParticleT, RuleT>::getRule(int ruleId)
  {
    Assert(ruleId < rules_.size(), "Index out of bounds");
    return rules_[ruleId];
  }


  template<typename ParticleT, typename RuleT>  
  ParticleT &ParticleSystem<ParticleT, RuleT>::create(int ruleId)
  {
    Assert(ruleId < rules_.size(), "Index out of bounds");
    Assert(particles_, "particles_ NULL, init not called?");

    ParticleT &particle = particles_->request();
    particle.setType(ruleId);
    
    RuleT &rule = rules_[ruleId];
    rule.onParticleInit(particle);

    return particle;
  }


  template<typename ParticleT, typename RuleT>  
  void ParticleSystem<ParticleT, RuleT>::update(float duration)
  {
    typename std::vector<ParticleT> &ps = particles_->items();
    unsigned len = ps.size();

    for (int i = 0; i < len; ++i) {
      ParticleT &p = ps[i];

      if (p.type() != -1) {
        if (!p.update(duration)) {

          RuleT &rule = rules_[p.type()];
          p.setType(-1);
          rule.onParticleDeinit(p);
          
          if (p.type() == -1) {
            particles_->release(p);
          }
        }
      }
    }
  }
  
} // namespace


#endif // PARTICLE_H_
