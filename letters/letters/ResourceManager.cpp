#include "ResourceManager.h"


namespace letters {
  
  const std::string ResourceManager::imageDir_ = "assets/images";
  const std::string ResourceManager::shaderDir_ = "assets/shaders";
  const std::string ResourceManager::scriptDir_ = "assets/scripts";
  

  ewok::Image *ResourceManager::loadImage(const std::string &name)
  {
    LogInfo << "Loading Image: " << name;
    return [ImageLoader loadImage: resourcePath(name, imageDir_)];
  }

  
  ewok::Texture ResourceManager::loadTexture(const std::string &name)
  {
    ewok::Image *img = loadImage(name);
    Assert(img, "Failure loading image");

    ewok::Texture t;
    t.init(*img, false);

    delete img;
    return t;
  }


  ewok::Shader ResourceManager::loadVertexShader(const std::string &name)
  {
    return loadShader(name, ewok::Shader::VERTEX_SHADER);
  }


  ewok::Shader ResourceManager::loadFragmentShader(const std::string &name)
  {
    return loadShader(name, ewok::Shader::FRAGMENT_SHADER);
  }

  
  ewok::Shader ResourceManager::loadShader(const std::string &name, ewok::Shader::Type shaderType)
  {
    LogInfo << "Loading Shader: " << name;
    NSData *shaderSource = [NSData dataWithContentsOfFile: resourcePath(name, shaderDir_)];
    ewok::Shader s;
    s.init(shaderType, [shaderSource length], (const char *)[shaderSource bytes]);
    return s;
  }


  ewok::LuaScript ResourceManager::loadScript(const std::string &name)
  {
    LogInfo << "Loading Script: " << name;
    NSData *data = [NSData dataWithContentsOfFile: resourcePath(name, scriptDir_)];

    size_t size = [data length];
    char *buffer = (char *)malloc(sizeof(char) * size);
    memcpy(buffer, [data bytes], size);

    ewok::FileData fd;
    fd.setData(name, buffer, size);

    ewok::LuaScript script;
    script.init(fd);
    fd.erase();
    
    return script;
  }


  std::string ResourceManager::scriptPath(const std::string &name)
  {
    LogInfo << "Getting path for name: " << name;
    NSString *path = resourcePath(name, scriptDir_);
    std::string str = [path UTF8String];
    LogInfo << "The path is: " << str;
    return str;
  }
  
  
  NSString *ResourceManager::resourcePath(const std::string &fname, const std::string &directory)
  {
    NSString *filename = [NSString stringWithUTF8String: fname.c_str()];
    NSString *extension = [filename pathExtension];
    NSString *name = [filename substringToIndex: [filename length] - ([extension length] + 1)];
    NSString *dir = [NSString stringWithUTF8String: directory.c_str()];
    
    NSString *path = [[NSBundle mainBundle] pathForResource: name ofType: extension inDirectory: dir];
    if (path == nil) {
      LogError << "Could not find: " << fname << " in directory: " << directory;
    }
    return path;
  }
  
} // namespace letters
