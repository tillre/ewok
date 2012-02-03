#include "Application.h"

#include "Log.h"
#include "Random.h"


namespace ewok {
  

  Application::Application()
    : delegate_(NULL)
  {
  }


  void Application::init(IAppDelegate &del, IResourceManager &res)
  {
    LogInfo << "Application::init";
    resManager_ = &res;
    
    Random::init();
    
    renderer_.init();

    delegate_ = &del;
    delegate_->init(*this);
  }


  void Application::deinit()
  {
    delegate_->deinit();
    renderer_.deinit();
  }

  
  void Application::pause()
  {
    delegate_->pause();
  }


  void Application::resume()
  {
    delegate_->resume();
  }


  void Application::update(float duration)
  {
    delegate_->update(duration);

    animations_.update(duration);
    physics_.update(duration);
  }
  
  
  void Application::render()
  {
    renderer_.render();
  }


  void Application::touchBegin(const Touch &t)
  {
    LogInfo << "App touch begin: " << t.x << " / " << t.y;
    delegate_->touchBegin(t);
  }


  void Application::touchEnd(const Touch &t)
  {
    LogInfo << "App touch end: " << t.x << " / " << t.y;
    delegate_->touchEnd(t);
  }


  Animations &Application::animations()
  {
    return animations_;
  }
  

  Physics &Application::physics()
  {
    return physics_;
  }


  Renderer &Application::renderer()
  {
    return renderer_;
  }


  IResourceManager &Application::resources()
  {
    return *resManager_;
  }

} // namespace ewok
