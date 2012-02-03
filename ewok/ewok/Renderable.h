#ifndef RENDERABLE_H_
#define RENDERABLE_H_


namespace ewok {


  class IRenderable {
  public:
    // virtual void onAttach() = 0;
    // virtual void onDetach() = 0;
    virtual void render() = 0;
  };


} // namespace ewok


#endif  // RENDERRENDERABLE_H_
