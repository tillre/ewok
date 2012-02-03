#ifndef RENDERATTRIBS_H_
#define RENDERATTRIBS_H_

#include <vector>
#include "OpenGLUtil.h"


namespace ewok {


  class RenderAttribs;


  // -----------------------------------------------------------------------------
  // RenderAttrib
  // -----------------------------------------------------------------------------


  class RenderAttrib {
    friend class RenderAttribs;
  
  public:
    enum Type {
      BYTE = GL_BYTE,
      UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
      SHORT = GL_SHORT,
      UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
      INT = GL_INT,
      UNSIGNED_INT = GL_UNSIGNED_INT,
      FLOAT = GL_FLOAT
    };

    RenderAttrib();

    void set(const char *name, Type compType, unsigned numComps);
    
  private:
    const char *name_;
    Type compType_;
    unsigned numComps_;
    unsigned compSize_;
    unsigned index_;
  };


  // -----------------------------------------------------------------------------
  // RenderAttribs
  // -----------------------------------------------------------------------------


  class RenderAttribs {
  public:
    RenderAttribs(unsigned numAttribs);
    
    void set(unsigned index, const char *name,
             RenderAttrib::Type compType, unsigned numComps);

    void bindLocations(unsigned programId);
    void enable();
    void disable();
  
  private:
    unsigned nextIndex_;
    unsigned stride_;
    std::vector<RenderAttrib> attribs_;
  };


} // namespace ewok


#endif  // RENDERATTRIBS_H_
