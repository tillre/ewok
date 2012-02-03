#include "OpenGLUtil.h"


#include <cstdlib>


namespace ewok {


  const char* GLErrorName(GLenum error) {
    switch(error) {
    case GL_INVALID_ENUM: return "GL_INVALID_ENUM"; 
    case GL_INVALID_VALUE: return "GL_INVALID_VALUE"; 
    case GL_INVALID_OPERATION: return "GL_INVALID_OPERATION"; 
      //  case GL_STACK_OVERFLOW: return "GL_STACK_OVERFLOW"; 
      //  case GL_STACK_UNDERFLOW: return "GL_STACK_UNDERFLOW"; 
    case GL_OUT_OF_MEMORY: return "GL_OUT_OF_MEMORY"; 
      //  case GL_TABLE_TOO_LARGE: return "GL_TABLE_TOO_LARGE"; 
    case GL_INVALID_FRAMEBUFFER_OPERATION: return "GL_INVALID_FRAMEBUFFER_OPERATION";
    default: return "UNKOWN_GL_ERROR";
    }
  }


  const char* GLFormatName(GLenum format) {
    switch(format) {
    case GL_RGB: return "GL_RGB";
    case GL_RGBA: return "GL_RGBA";
    case GL_BGRA: return "GL_BGRA";
    case GL_LUMINANCE_ALPHA: return "GL_LUMINANCE_ALPHA";
    case GL_LUMINANCE: return "GL_LUMINANCE";
    default: return "UNKOWN_GL_FORMAT";
    }
  }


  const char* GLTypename(GLenum type) {
    switch (type) {
    case GL_FLOAT: return "GL_FLOAT";
    case GL_FLOAT_VEC2: return "GL_FLOAT_VEC2";
    case GL_FLOAT_VEC3: return "GL_FLOAT_VEC3";
    case GL_FLOAT_VEC4: return "GL_FLOAT_VEC4";
    case GL_INT: return "GL_INT";
    case GL_INT_VEC2: return "GL_INT_VEC2";
    case GL_INT_VEC3: return "GL_INT_VEC3";
    case GL_INT_VEC4: return "GL_INT_VEC4";
    case GL_BOOL: return "GL_BOOL";
    case GL_BOOL_VEC2: return "GL_BOOL_VEC2";
    case GL_BOOL_VEC3: return "GL_BOOL_VEC3";
    case GL_BOOL_VEC4: return "GL_BOOL_VEC4";
    case GL_FLOAT_MAT2: return "GL_FLOAT_MAT2";
    case GL_FLOAT_MAT3: return "GL_FLOAT_MAT3";
    case GL_FLOAT_MAT4: return "GL_FLOAT_MAT4";
    case GL_SAMPLER_2D: return "GL_SAMPLER_2D";
    case GL_SAMPLER_CUBE : return "GL_SAMPLER_CUBE ";
    default: return "UNKNOWN_GL_TYPE";
    }
  }

  void LogOpenGLVars()
  {
    LogInfo << "GL_RENDERER   : " << (char *) glGetString(GL_RENDERER);
    LogInfo << "GL_VERSION    : " << (char *) glGetString(GL_VERSION);
    LogInfo << "GL_VENDOR     : " << (char *) glGetString(GL_VENDOR);
    LogInfo << "GL_EXTENSIONS : " << (char *) glGetString(GL_EXTENSIONS);
  
    GLint max_vertex_attribs = 0;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &max_vertex_attribs);
    LogInfo << "GL_MAX_VERTEX_ATTRIBS: " << max_vertex_attribs;

    //  GLint max_vertex_unis = 0;;
    //  glGetIntegerv(GL_MAX_VERTEX_UNIFORM_COMPONENTS, &max_vertex_unis);
    //  LogInfo("GL_MAX_VERTEX_UNIFORM_COMPONENTS: %d", max_vertex_unis);

    GLint max_tex_units = 0;
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &max_tex_units);
    LogInfo << "GL_MAX_TEXTURE_IMAGE_UNITS: " << max_tex_units;

    /* glGetIntegerv(GL_MAX_VERTEX_UNIFORM_BLOCKS, &value); */
    /* LogInfo("GL_MAX_VERTEX_UNIFORM_BLOCKS: %d", value); */
    /* glGetIntegerv(GL_MAX_GEOMETRY_UNIFORM_BLOCKS, &value); */
    /* LogInfo("GL_MAX_GEOMETRY_UNIFORM_BLOCKS: %d", value); */
    /* glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_BLOCKS, &value); */
    /* LogInfo("GL_MAX_FRAGMENT_UNIFORM_BLOCKS: %d", value); */
    /* glGetIntegerv(GL_MAX_UNIFORM_BLOCK_SIZE, &value); */
    /* LogInfo("GL_MAX_UNIFORM_BLOCK_SIZE: %d", value); */
  }

  void LogShaderVars(GLuint program)
  {
    GLint attached_shaders = 0;
    glGetProgramiv(program, GL_ATTACHED_SHADERS, &attached_shaders);
    LogInfo << "GL_ATTACHED_SHADERS: " << attached_shaders;
  
    GLint active_attributes = 0;
    GLint active_attributes_len = 0;
    glGetProgramiv(program, GL_ACTIVE_ATTRIBUTES, &active_attributes);
    glGetProgramiv(program, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &active_attributes_len);
    LogInfo << "GL_ACTIVE_ATTRIBUTES: " << active_attributes;

    GLint active_uniforms = 0;
    GLint active_uniforms_len = 0;
    glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &active_uniforms);
    glGetProgramiv(program, GL_ACTIVE_UNIFORM_MAX_LENGTH, &active_uniforms_len);
    LogInfo << "GL_ACTIVE_UNIFORMS: " << active_uniforms;
  
    GLint size;
    GLenum type;
    char name[(active_attributes_len > active_uniforms_len
               ? active_uniforms_len : active_uniforms_len) + 1];
    if (active_attributes_len > 0) {
      LogInfo << "ATTRIBUTES:";
      for (GLint i = 0; i < active_attributes; ++i) {
        glGetActiveAttrib(program, i, active_attributes_len, NULL, &size, &type, name);
        LogInfo << i << ": " << name << GLTypename(type);
      }
    }
    if (active_uniforms_len > 0) {
      LogInfo << "UNIFORMS:";
      for (GLint i = 0; i < active_uniforms; ++i) {
        glGetActiveUniform(program, i, active_uniforms_len, NULL, &size, &type, name);
        LogInfo << i << ": " << name << GLTypename(type);
      }
    }
  }

} // namespace ewok
