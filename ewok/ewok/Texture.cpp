#include "Texture.h"

#include "OpenGLUtil.h"
#include "Image.h"


namespace ewok {

  static const unsigned kTextureNumUnits = 16;
  static const unsigned kTextureUnitNums[] = {
    GL_TEXTURE0, GL_TEXTURE1, GL_TEXTURE2, GL_TEXTURE3,
    GL_TEXTURE4, GL_TEXTURE5, GL_TEXTURE6, GL_TEXTURE7,
    GL_TEXTURE8, GL_TEXTURE9, GL_TEXTURE10, GL_TEXTURE11,
    GL_TEXTURE12, GL_TEXTURE13, GL_TEXTURE14, GL_TEXTURE15
  };


  Texture::Texture()
    : width_(0),
      height_(0),
      id_(0)
  {
  }

  
  void Texture::init(const Image &img, bool createMipmaps)
  {
    Assert(!id_, "Id already set, init called a second time?");
    
    width_ = img.width();
    height_ = img.height();

    glGenTextures(1, &id_);
    glBindTexture(GL_TEXTURE_2D, id_);

    CheckGLError();
    
    Image::Format internalFormat = img.format();
    if (internalFormat == Image::BGRA) {
      internalFormat = Image::RGBA;
    }
    
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat,
		 img.width(), img.height(), 0,
		 img.format(), GL_UNSIGNED_BYTE,
		 img.pixels());

    CheckGLError();
  
    if (createMipmaps) {
      glGenerateMipmap(GL_TEXTURE_2D);
    }
    // required 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    CheckGLError();
  }


  void Texture::erase()
  {
    if (id_) {
      glDeleteTextures(1, &id_);
    }
    id_ = 0;
  }


  void Texture::activate(unsigned texUnitNum)
  {
    Assert(texUnitNum < kTextureNumUnits, "Textureunit number too big");
    glActiveTexture(kTextureUnitNums[texUnitNum]);
    glBindTexture(GL_TEXTURE_2D, id_);
  }


  int Texture::width()
  {
    return width_;
  }


  int Texture::height()
  {
    return height_;
  }


} // namespace ewok
