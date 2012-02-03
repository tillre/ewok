#ifndef APPLICATION_H_
#define APPLICATION_H_


#include "Physics.h"
#include "Renderer.h"
#include "Resource.h"
#include "Animation.h"
#include "Touch.h"


namespace ewok {

  class Application;
  
  // ----------------------------------------------------------------------
  // IAppDelegate 
  // ----------------------------------------------------------------------

  class IAppDelegate {
  public:
    virtual void init(Application &app) = 0;
    virtual void deinit() = 0;

    virtual void pause() = 0;
    virtual void resume() = 0;

    virtual void update(float duration) = 0;

    virtual void touchBegin(const Touch &t) = 0;
    virtual void touchEnd(const Touch &t) = 0;
  };

  // ----------------------------------------------------------------------
  // Application
  // ----------------------------------------------------------------------

  class Application {
  public:
    Application();
    
    void init(IAppDelegate &delegate, IResourceManager &resManager);
    void deinit();

    void pause();
    void resume();
    
    void update(float duration);
    void render();

    void touchBegin(const Touch &t);
    void touchEnd(const Touch &t);

    Animations &animations();
    Physics &physics();
    Renderer &renderer();

    IResourceManager &resources();
    
  private:
    IAppDelegate *delegate_;
    IResourceManager *resManager_;

    Animations animations_;
    Physics physics_;
    Renderer renderer_;
  };
  
} // namespace ewok

#endif  // APPLICATION_H_
