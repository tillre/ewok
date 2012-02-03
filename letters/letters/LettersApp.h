#ifndef LETTERSAPP_H_
#define LETTERSAPP_H_


#include "Application.h"
#include "Scene.h"
#include "Touch.h"


namespace letters {


  class LettersApp : public ewok::IAppDelegate {
  public:

    virtual void init(ewok::Application &app);
    virtual void deinit();

    virtual void pause();
    virtual void resume();

    virtual void update(float duration);

    virtual void touchBegin(const ewok::Touch &t);
    virtual void touchEnd(const ewok::Touch &t);

    void nextScene();
    ewok::IScene *createScene(int id);
    
  private:
    ewok::IScene *currentScene_;
  };

} // namespace letters


#endif // LETTERSAPP_H_
