#ifndef RENDERPROGRAM_H_
#define RENDERPROGRAM_H_

#include "RenderAttribs.h"
#include "RenderUniforms.h"
#include "Shader.h"


namespace ewok {

  class VertexBuffer;
  class IndexBuffer;


  class RenderProgram {
  public:
    RenderProgram();
    ~RenderProgram();

    void init(const Shader &vshader, const Shader &fshader,
              const RenderAttribs &attribs);
    
    RenderUniforms use(); // has to be called before rendering

    void render(const VertexBuffer &vertBuffer, const IndexBuffer &indexBuffer,
		unsigned int numIndices);
  
    void render(const VertexBuffer &vertBuffer,
		unsigned start, unsigned num);
  
    unsigned id() const;
  
  private:
    RenderProgram(const RenderProgram &other) : attribs_(0) {}
    RenderProgram &operator=(const RenderProgram &other) { return *this; }
    
    void link();

    unsigned id_;

    Shader vshader_;
    Shader fshader_;
    
    RenderAttribs attribs_;
  };


} // namespace ewok




#endif  // RENDERPROGRAM_H_
