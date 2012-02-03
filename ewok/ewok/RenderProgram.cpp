#include "RenderProgram.h"

#include "OpenGLUtil.h"
#include "RenderBuffer.h"


namespace ewok {


  RenderProgram::RenderProgram()
    : attribs_(0)
  {
  }


  RenderProgram::~RenderProgram()
  {
    glDetachShader(id_, vshader_.id());
    glDetachShader(id_, fshader_.id());
    glDeleteProgram(id_);
    CheckGLError();
  }


  void RenderProgram::init(const Shader &vshader, const Shader &fshader,
                           const RenderAttribs &attribs)
  {
    vshader_ = vshader;
    fshader_ = fshader;
    attribs_ = attribs;
    link();
  }
  

  void RenderProgram::link()
  {
    id_ = glCreateProgram();
    if (!id_) {
      LogError << "cannot create program";
      return;
    }

    attribs_.bindLocations(id_);
  
    glAttachShader(id_, vshader_.id());
    glAttachShader(id_, fshader_.id());

    glLinkProgram(id_);

    GLint success = 0;
    glGetProgramiv(id_, GL_LINK_STATUS, &success);
    if (!success) {
      GLint infoLen = 0;
      glGetProgramiv(id_, GL_INFO_LOG_LENGTH, &infoLen);

      if (infoLen > 1) {
	char *infoLog = new char[infoLen];
	glGetProgramInfoLog(id_, infoLen, 0, infoLog);
	LogError << infoLog;
	delete []infoLog;
      }
      glDeleteProgram(id_);
      return;
    }
    CheckGLError();
    LogShaderVars(id_);
  }



  RenderUniforms RenderProgram::use()
  {
    glUseProgram(id_);
    CheckGLError();
    return RenderUniforms(id_);
  }


  void RenderProgram::render(const VertexBuffer &vertexBuffer,
			     const IndexBuffer &indexBuffer,
			     unsigned numIndices)
  {
    vertexBuffer.bind();
    indexBuffer.bind();

    attribs_.enable();

    glDrawElements(vertexBuffer.elementType(), numIndices, indexBuffer.indexType(), NULL);
    CheckGLError();
  
    attribs_.disable();
  }


  void RenderProgram::render(const VertexBuffer &vertexBuffer,
			     unsigned start, unsigned num)
  {
    vertexBuffer.bind();
  
    attribs_.enable();

    glDrawArrays(vertexBuffer.elementType(), start, num);
    CheckGLError();

    attribs_.disable();
  }


} // namespace ewok
