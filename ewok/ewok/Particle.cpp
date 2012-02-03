#include "Particle.h"



namespace ewok {



  // ----------------------------------------------------------------------
  // Particle
  // ----------------------------------------------------------------------
  
  
  Particle::Particle()
    : damping(0.995f),
      inverseMass_(1.0f),
      type_(-1)
  {
  }
  

  bool Particle::update(float duration)
  {
    integrate(duration);
    // Sprite::setTransform(position);

    RotMatrix rot(rotation);
    Matrix43 mat(rot, position);
    transform = mat;
    
    return true;
  }


  void Particle::integrate(float duration)
  {
    // update linear position
    position += velocity * duration;

    // LogInfo << "t: " << duration
    //         << "\tpos: "  << position_.x << " / " << position_.y << " / " << position_.z
    //         << "\tvel: " << velocity_.x << " / " << velocity_.y;

    // work out the new acceleration from the force
    Vector3 newAcc = acceleration;
    newAcc += forces * inverseMass_;

    velocity += newAcc * duration;

    // impose drag
    // velocity *= powf(damping, duration);

    // rotation --------------------
    
    rotation += rotVelocity * duration;

    Vector3 newRotAcc = rotAcceleration;
    newRotAcc += forces * inverseMass_;

    rotVelocity += newRotAcc * duration;

    // rotVelocity *= powf(damping, duration);
  }


  void Particle::setType(int t)
  {
    type_ = t;
  }
  

  int Particle::type() const
  {
    return type_;
  }
  
  
  void Particle::setMass(float m)
  {
    Assert(m != 0, "Mass cannot be 0");
    inverseMass_ = 1 / m;
  }


  void Particle::setUsed(bool u)
  {
    Sprite::setUsed(u);
    if (!u) {
      position.clear();
      velocity.clear();
      acceleration.clear();
      forces.clear();

      damping = 0.995f;
      inverseMass_ = 1.0f;
      type_ = -1;
    }
  }
} // namespace ewok
