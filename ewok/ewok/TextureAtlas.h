#ifndef TEXTUREATLAS_H_
#define TEXTUREATLAS_H_


#include <vector>
#include <map>
#include "Vector.h"
#include "Texture.h"


namespace ewok {
  
  
  // ----------------------------------------------------------------------
  // TextureAtlas
  // ----------------------------------------------------------------------
  

  class TextureAtlas {
  public:
    TextureAtlas();
    
    void init(Texture tex, unsigned numTiles);

    void setTile(unsigned i, float x, float y, float w, float h);
    
    const Vector4 &getTile(unsigned i) const;

    void activate(unsigned texUnitNUm);

    void erase();

  private:
    std::vector<Vector4>tiles_;
    Texture texture_;
  };


  // ----------------------------------------------------------------------
  // TextureAtlasGroup
  // ----------------------------------------------------------------------


  class TextureAtlasGroup {
    typedef std::map<std::string, TextureAtlas> Map;
    typedef std::pair<std::string, TextureAtlas> MapItem;

  public:
    TextureAtlasGroup();

    TextureAtlas &makeAtlas(const std::string &name,
                            const Texture &tex,
                            unsigned numTiles);

    const TextureAtlas &getAtlas(const std::string &name);

  private:
    TextureAtlasGroup(const TextureAtlasGroup *other) {}
    TextureAtlasGroup &operator=(const TextureAtlasGroup *other) { return *this; }
    
    Map atlases_;
  };
  
  
} // namespace ewok


#endif // TEXTUREATLAS_H_
