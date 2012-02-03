#ifndef OPENGLUTIL_H_
#define OPENGLUTIL_H_


// #include "OpenGL/OpenGL.h"
// #include "OpenGL/gl.h"
// #include "OpenGL/glu.h"
// #include "OpenGL/glext.h"
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>


#include "Log.h"


#define CheckGLError()

// #define CheckGLError()                                     \
//   {                                                        \
//     GLint err = glGetError();                              \
//     if (err) {                                             \
//       ewok::Log().get(ewok::LOG_ERROR) << "OpenGL Error: " << GLErrorName(err) \
//                                            <<  " on line: " << __LINE__ << " in file: " << __FILE__; \
//       assert(false);                                       \
//     }                                                      \
//   }



namespace ewok {


  const char* GLErrorName(GLenum error);
  const char* GLTypename(GLenum type);
  const char* GLFormatName(GLenum format);

  void LogShaderVars(GLuint program);
  void LogOpenGLVars();


} // namespace ewok


#endif  // OPENGLUTIL_H_
