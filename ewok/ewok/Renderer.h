#ifndef RENDERER_H_
#define RENDERER_H_


#include <vector>


namespace ewok {


  class IRenderable;


  class Renderer {
  public:
    Renderer();
    ~Renderer();

    void init();
    void deinit();

    void addRenderable(IRenderable &r);
    void removeRenderable(IRenderable &r);
  
    void render();

    void enableCulling(bool b);
    void enableClearing(bool b);

  private:
    Renderer(const Renderer &other) {}
    Renderer &operator=(const Renderer &other) { return *this; }
    
    std::vector<IRenderable*> renderables_;

    bool clearEnabled_;
  };


} // namespace ewok


#endif  // RENDERER_H_
