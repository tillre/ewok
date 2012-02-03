#include "Image.h"

#include "Log.h"


namespace ewok {


  Image::Image()
  : width_(0),
    height_(0),
    format_(Image::RGBA),
    size_(0),
    pixels_(NULL)
  {
  }


  Image::~Image()
  {
    if (size_ > 0) {
      delete[] pixels_;
    }
    pixels_ = NULL;
  }


  void Image::init(unsigned width, unsigned height,
                   unsigned char *pixels, size_t size,
                   Format format)
  {
    width_ = width;
    height_ = height;
    pixels_ = pixels;
    size_ = size;
    format_ = format;
  }


  unsigned Image::width() const
  {
    return width_;
  }

  unsigned Image::height() const
  {
    return height_;
  }

  Image::Format Image::format() const
  {
    return format_;
  }

  unsigned Image::size() const
  {
    return size_;
  }

  unsigned char *Image::pixels() const
  {
    return pixels_;
  }


} // namespace ewok
