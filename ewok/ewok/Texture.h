#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <map>
#include "Log.h"


namespace ewok {

  class Image;


  // ----------------------------------------------------------------------
  // Texture
  // ----------------------------------------------------------------------

  
  class Texture {
  public:
    Texture();

    void init(const Image &img, bool createMipmaps);
    void erase();

    void activate(unsigned texUnitNum);

    int width();
    int height();
    
  private:
    int width_;
    int height_;
    unsigned id_;
  };


  // ----------------------------------------------------------------------
  // TextureGroup
  // ----------------------------------------------------------------------


  class TextureGroup {
    typedef std::map<std::string, Texture> Map;
    typedef std::pair<std::string, Texture> MapItem;

  public:
    TextureGroup()
    {
    }

    ~TextureGroup()
    {
      Map::iterator it;
      for (it = textures_.begin(); it != textures_.end(); ++it) {
        it->second.erase();
      }
    }

    void addTexture(const std::string &name, const Texture &tex)
    {
      Assert(textures_.find(name) == textures_.end(), "Texture already exists");
      textures_[name] = tex;
    }

    const Texture &getTexture(const std::string &name)
    {
      Assert(textures_.find(name) != textures_.end(), "Texture does not exist");
      return textures_[name];
    }

  private:
    TextureGroup(const TextureGroup &other) {}
    TextureGroup &operator=(const TextureGroup &other) { return *this; }

    Map textures_;
  };



} // namespace ewok


#endif  // TEXTURE_H_
