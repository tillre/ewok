#ifndef RENDERUNIFORMS_H_
#define RENDERUNIFORMS_H_


#include "OpenGLUtil.h"
#include "Matrix.h"


namespace ewok {


  class RenderProgram;


  class RenderUniform {
    friend class RenderUniforms;
  public:
    RenderUniform() : location_(-1) {}
    
    // float ------------------------------

    void set1f(float x)
    {
      Assert(location_ != -1, "Location no set");
      glUniform1f(location_, x);
      CheckGLError();      
    }
    void set2f(float x, float y)
    {
      Assert(location_ != -1, "Location no set");
      glUniform2f(location_, x, y);
      CheckGLError();      
    }
    void set3f(float x, float y, float z)
    {
      Assert(location_ != -1, "Location no set");
      glUniform3f(location_, x, y, z);
      CheckGLError();
    }
    void set4f(float x, float y, float z, float w)
    {
      Assert(location_ != -1, "Location no set");
      glUniform4f(location_, x, y, z, w);
      CheckGLError();
    }
    
    // int --------------------------------
    
    void set1i(int x)
    {
      Assert(location_ != -1, "Location no set");
      glUniform1i(location_, x);
      CheckGLError();      
    }
    void set2i(int x, int y)
    {
      Assert(location_ != -1, "Location no set");
      glUniform2i(location_, x, y);
      CheckGLError();      
    }
    void set3i(int x, int y, int z)
    {
      Assert(location_ != -1, "Location no set");
      glUniform3i(location_, x, y, z);
      CheckGLError();      
    }
    void set4i(int x, int y, int z, int w)
    {
      Assert(location_ != -1, "Location no set");
      glUniform4i(location_, x, y, z, w);
      CheckGLError();      
    }

    // matrix ------------------------------
 
    void setMat4f(const Matrix4 &mat)
    {
      Assert(location_ != -1, "Location no set");
      glUniformMatrix4fv(location_, 1, false, (const float *)&mat);
      CheckGLError();
    }      
    
  private:
    RenderUniform(int location)
      : location_(location)
    {}
    int location_;
  };

  

  
  class RenderUniforms {
    friend class RenderProgram;
  public:
    RenderUniform getUniform(const char *name);
  
  private:
    RenderUniforms(unsigned programId);
  
    int getUniformLocation(const char *name);

    unsigned programId_;
  };


} // namespace ewok


#endif  // RENDERUNIFORMS_H_
