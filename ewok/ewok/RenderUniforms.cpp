#include "RenderUniforms.h"

#include "RenderProgram.h"


namespace ewok {


  RenderUniforms::RenderUniforms(unsigned programId)
    : programId_(programId)
  {
  }


  int RenderUniforms::getUniformLocation(const char *name)
  {
    Assert(programId_, "Program id invalid");
    int location = glGetUniformLocation(programId_, name);
    if (location == -1) {
      // uniform no present or optimized away
      LogWarn << "glGetUniformLocation does not find: " << name;
    }
    return location;
  }


  RenderUniform RenderUniforms::getUniform(const char *name)
  {
    return RenderUniform(getUniformLocation(name));
  }


} // namespace ewok

