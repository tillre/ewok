#include "TextureAtlas.h"


namespace ewok {


  // ----------------------------------------------------------------------
  // TextureAtlas
  // ----------------------------------------------------------------------

  
  TextureAtlas::TextureAtlas()
    : tiles_(0)
  {
  }
    
    
  void TextureAtlas::init(Texture tex, unsigned numTiles)
  {
    texture_ = tex;
    tiles_.resize(numTiles);
  }


  void TextureAtlas::setTile(unsigned i, float x, float y, float w, float h) 
  {
    Assert(i < tiles_.size(), "Index out of bounds");
    // convert x, y, w, h in pixels to x1, y1, x2, y2 in texture coordinates
    Vector4 &coords = tiles_[i];
    coords.x = x / texture_.width();
    coords.y = y / texture_.height();
    coords.z = (x + w) / texture_.width();
    coords.w = (y + h) / texture_.height();
  }
    

  const Vector4 &TextureAtlas::getTile(unsigned i) const
  {
    Assert(i < tiles_.size(), "Index out of bounds");
    return tiles_[i];
  }


  void TextureAtlas::activate(unsigned texUnitNUm)
  {
    texture_.activate(texUnitNUm);
  }


  void TextureAtlas::erase()
  {
    texture_.erase();
  }


  // ----------------------------------------------------------------------
  // TextureAtlasGroup
  // ----------------------------------------------------------------------


  TextureAtlasGroup::TextureAtlasGroup()
  {
  }

  TextureAtlas &TextureAtlasGroup::makeAtlas(const std::string &name,
                          const Texture &tex,
                          unsigned numTiles)
  {
    Assert(atlases_.find(name) == atlases_.end(), "Atlas already exists");
    TextureAtlas &a = atlases_[name];
    a.init(tex, numTiles);
    return a;
  }

    
  const TextureAtlas &TextureAtlasGroup::getAtlas(const std::string &name)
  {
    Assert(atlases_.find(name) != atlases_.end(), "Atlas does not exist");
    return atlases_[name];
  }


  
} // namespace ewok
