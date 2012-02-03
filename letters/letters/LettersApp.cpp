#include "LettersApp.h"
#include "LettersScene.h"


namespace letters {


  void LettersApp::init(ewok::Application &app)
  {
    currentScene_ = new LettersScene();
    currentScene_->init(app);
    currentScene_->attach();
  }


  void LettersApp::deinit() {
    currentScene_->detach();
  }


  void LettersApp::update(float duration)
  {
    currentScene_->update(duration);
  }

  
  void LettersApp::pause()
  {
  }


  void LettersApp::resume()
  {
  }

  
  void LettersApp::touchBegin(const Touch &t)
  {
    currentScene_->touchBegin(t);
  }


  void LettersApp::touchEnd(const Touch &t)
  {
    currentScene_->touchEnd(t);
  }


} // namespace letters
