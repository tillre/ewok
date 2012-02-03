#include "Resource.h"


namespace ewok {

  
  void ResourceGroup::init(IResourceManager &res)
  {
    resMan_ = &res;
  }


  std::string ResourceGroup::scriptPath(std::string name)
  {
    return resMan_->scriptPath(name);
  }

    
  void ResourceGroup::loadTexture(std::string name)
  {
    Texture tex = resMan_->loadTexture(name);
    textures_.addTexture(name, tex);
  }


  TextureAtlas *ResourceGroup::makeTextureAtlas(std::string name, std::string texName,
                                 unsigned numTiles)
  {
    const Texture &tex = textures_.getTexture(texName);
    TextureAtlas &atlas = atlases_.makeAtlas(name, tex, numTiles);
    return &atlas;
  }

    
  FrameAnimation *ResourceGroup::makeFrameAnimation(std::string name, unsigned numFrames)
  {
    FrameAnimation &ani = animations_.makeAnimation(name, numFrames);
    return &ani;
  }

    
  const TextureAtlas &ResourceGroup::getAtlas(const std::string &name)
  {
    return atlases_.getAtlas(name);
  }

  
  const FrameAnimation &ResourceGroup::getFrameAnimation(const std::string &name)
  {
    return animations_.getAnimation(name);
  }

  
} // namespace ewok
