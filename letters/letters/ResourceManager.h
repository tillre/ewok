#ifndef RESMANAGER_H_
#define RESMANAGER_H_

#import <UIKit/UIKit.h>
#import "ImageLoader.h"

#include "Resource.h"
#include "Image.h"
#include "Texture.h"
#include "Shader.h"
#include "LuaScript.h"


namespace letters {

  class ResourceManager : public ewok::IResourceManager {
  public:
    virtual ewok::Image *loadImage(const std::string &name);
    
    virtual ewok::Texture loadTexture(const std::string &name);

    virtual ewok::Shader loadVertexShader(const std::string &name);

    virtual ewok::Shader loadFragmentShader(const std::string &name);

    virtual ewok::LuaScript loadScript(const std::string &name);

    virtual std::string scriptPath(const std::string &name);

  private:
    virtual ewok::Shader loadShader(const std::string &name, ewok::Shader::Type shaderType);

    NSString *resourcePath(const std::string &name, const std::string &directory);

    static const std::string imageDir_;
    static const std::string shaderDir_;
    static const std::string scriptDir_;
  };

  
} // namespace letters


#endif // RESMANAGER_H_
