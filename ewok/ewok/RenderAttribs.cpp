#include "RenderAttribs.h"



namespace ewok {


  // -----------------------------------------------------------------------------
  // RenderAttrib
  // -----------------------------------------------------------------------------


  RenderAttrib::RenderAttrib()
    : name_(NULL),
      compType_(RenderAttrib::FLOAT),
      numComps_(0),
      compSize_(0),
      index_(0)
  {
  }


  void RenderAttrib::set(const char *name, Type compType, unsigned numComps)
  {
    name_ = name;
    compType_ = compType;
    numComps_ = numComps;
    
    switch (compType_) {
    case BYTE:
    case UNSIGNED_BYTE: compSize_ = sizeof(char); break;

    case SHORT:
    case UNSIGNED_SHORT: compSize_ = sizeof(short); break;

    case INT:
    case UNSIGNED_INT: compSize_ = sizeof(int); break;

    case FLOAT:  compSize_ = sizeof(float); break;

    default: LogError << "RenderAttrib::RenderAttrib unkown compType";
    }
  }

  
  // -----------------------------------------------------------------------------
  // RenderAttribs
  // -----------------------------------------------------------------------------


  RenderAttribs::RenderAttribs(unsigned numAttribs)
    : stride_(0),
      attribs_(numAttribs)
  {
    std::vector<RenderAttrib>::iterator it;
    unsigned i = 0;
    for (it = attribs_.begin(); it != attribs_.end(); ++it) {
      it->index_ = i++;
    }
  }


  void RenderAttribs::set(unsigned index, const char *name,
                          RenderAttrib::Type compType, unsigned numComps)
  {
    Assert(index < attribs_.size(), "Index out of bounds");
    attribs_[index].set(name, compType, numComps);
  }
  

  void RenderAttribs::bindLocations(unsigned programId)
  {
    Assert(stride_ == 0, "Locations already bound");

    std::vector<RenderAttrib>::iterator it;
  
    for(it = attribs_.begin(); it != attribs_.end(); it++) {
      Assert(it->name_, "Attribute name is undefined");
      glBindAttribLocation(programId, it->index_, it->name_);
      stride_ += it->compSize_ * it->numComps_;
    }
    CheckGLError();
  }


  void RenderAttribs::enable()
  {
    std::vector<RenderAttrib>::iterator it;

    for(it = attribs_.begin(); it != attribs_.end(); it++) {
      glEnableVertexAttribArray(it->index_);
    }

    int offset = 0;
  
    for(it = attribs_.begin(); it != attribs_.end(); it++) {
      glVertexAttribPointer(it->index_, it->numComps_, it->compType_,
			    GL_FALSE, stride_, (const void *)offset);
      offset += it->numComps_ * it->compSize_;
    }
    CheckGLError();
  }


  void RenderAttribs::disable()
  {
    std::vector<RenderAttrib>::iterator it;
    for(it = attribs_.begin(); it != attribs_.end(); it++) {
      glEnableVertexAttribArray(it->index_);
    }
  
    CheckGLError();
  }


} // namespace ewok
