#include "Renderer.h"

#include "OpenGLUtil.h"
#include "Renderable.h"
#include <algorithm>


namespace ewok {


  Renderer::Renderer()
    : clearEnabled_(true)
  {
  }


  Renderer::~Renderer()
  {
    std::vector<IRenderable*>::iterator it;
    for (it = renderables_.begin(); it != renderables_.end(); it++) {
      delete *it;
    }
    renderables_.clear();
  }


  void Renderer::init()
  {
    LogOpenGLVars();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glDepthRangef(0.0f, 1.0f);
    // glDepthFunc(GL_ALWAYS);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    CheckGLError();
  }


  void Renderer::deinit()
  {
  }


  void Renderer::addRenderable(IRenderable &r)
  {
    renderables_.push_back(&r);
  }


  void Renderer::removeRenderable(IRenderable &r)
  {
    renderables_.erase(std::remove(renderables_.begin(), renderables_.end(), &r),
                       renderables_.end());
  }
  

  void Renderer::render()
  {
    if (clearEnabled_) glClear(GL_COLOR_BUFFER_BIT);

    std::vector<IRenderable*>::iterator it;
    for (it = renderables_.begin(); it != renderables_.end(); it++) {
      (*it)->render();
    }
  }


  void Renderer::enableCulling(bool b)
  {
    b ? glEnable(GL_CULL_FACE)
      : glDisable(GL_CULL_FACE);
  }

  void Renderer::enableClearing(bool b)
  {
    clearEnabled_ = b;
  }

} // namespace ewok
