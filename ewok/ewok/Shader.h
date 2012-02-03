#ifndef SHADER_H_
#define SHADER_H_

#include <cstddef>
#include "OpenGLUtil.h"


namespace ewok {


  class Shader {
  public:
    enum Type {
      VERTEX_SHADER = GL_VERTEX_SHADER,
      FRAGMENT_SHADER = GL_FRAGMENT_SHADER
    };

    Shader();
    ~Shader();
  
    void init(Type type, size_t size, const char *source);

    unsigned  id();
  
  private:
    Type type_;
    unsigned  id_;
  };


} // namespace ewok
  

#endif  // SHADER_H_
