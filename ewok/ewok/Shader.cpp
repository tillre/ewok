#include "Shader.h"

#include "Log.h"


namespace ewok {


  Shader::Shader()
    : type_(VERTEX_SHADER),
      id_(0)
  {
  }


  Shader::~Shader()
  {
    if (id_ > 0) {
      glDeleteShader(id_);
      CheckGLError();
    }
  }


  void Shader::init(Type type, size_t size, const char *source)
  {
    type_ = type;
    id_ = glCreateShader(type_);
    if (id_ == 0) {
      LogError << "shader could not be created";
      return;
    }
    // convert size_t to int for api call
    int s = (int)size;
    glShaderSource(id_, 1, &source, &s);
    glCompileShader(id_);

    GLint success;
    glGetShaderiv(id_, GL_COMPILE_STATUS, &success);

    if (!success) {
      GLint infoLen = 0;
      glGetShaderiv(id_, GL_INFO_LOG_LENGTH, &infoLen);

      if (infoLen > 1) {
	char *infoLog = new char[infoLen];
	glGetShaderInfoLog(id_, infoLen, 0, infoLog);
	LogError << infoLog;
	delete[] infoLog;
      }
      glDeleteShader(id_);
      id_ = 0;
      return;
    }
    CheckGLError();
  }


  unsigned Shader::id()
  {
    return id_;
  }


} // namespace ewok
