#ifndef RESOURCES_H_
#define RESOURCES_H_

#include <string>
#include "Texture.h"
#include "Shader.h"
#include "FileData.h"
#include "LuaScript.h"
#include "TextureAtlas.h"
#include "FrameAnimation.h"


namespace ewok {

  class Image;
  
  
  class IResourceManager {
  public:
    virtual Image *loadImage(const std::string &name) = 0;
    virtual Texture loadTexture(const std::string &name) = 0;
    virtual Shader loadVertexShader(const std::string &name) = 0;
    virtual Shader loadFragmentShader(const std::string &name) = 0;
    virtual LuaScript loadScript(const std::string &name) = 0;
    virtual std::string scriptPath(const std::string &name) = 0;
  };


  class ResourceGroup {
  public:
    void init(IResourceManager &res);

    std::string scriptPath(std::string name);

    void loadTexture(std::string name);

    TextureAtlas *makeTextureAtlas(std::string name, std::string texName, unsigned numTiles);

    FrameAnimation *makeFrameAnimation(std::string name, unsigned numFrames);

    const TextureAtlas &getAtlas(const std::string &name);

    const FrameAnimation &getFrameAnimation(const std::string &name);
    
  private:
    IResourceManager *resMan_;
    
    TextureGroup textures_;
    TextureAtlasGroup atlases_;
    FrameAnimationGroup animations_;
  };

  
} // namespace ewok



#endif // RESOURCES_H_
