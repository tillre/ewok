#ifndef IMAGE_H_
#define IMAGE_H_

#include <cstddef>
#include "OpenGLUtil.h"


namespace ewok {


  class Image {
  public:
    enum Format {
      RGBA = GL_RGBA,
      BGRA = GL_BGRA,
      RGB = GL_RGB,
      LUMINANCE_ALPHA = GL_LUMINANCE_ALPHA,
      LUMINANCE = GL_LUMINANCE
    };
    
    Image();
    virtual ~Image();

    void init(unsigned width, unsigned height,
              unsigned char *pixels, size_t size_,
              Format format);
  
    unsigned width() const;
    unsigned height() const;
    Format format() const;
  
    unsigned size() const;
    unsigned char *pixels() const;

  private:
    Image(const Image &other) {}
    Image &operator=(const Image &other) { return *this; }
    
    int width_;
    int height_;
    Format format_;
  
    size_t size_;
    unsigned char *pixels_;
  };


} // namespace ewok

#endif  // IMAGE_H_
