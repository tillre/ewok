#ifndef RENDERBUFFER_H_
#define RENDERBUFFER_H_

#include <cstddef>
#include "OpenGLUtil.h"


namespace ewok {


  // -----------------------------------------------------------------------------
  // RenderBuffer
  // -----------------------------------------------------------------------------


  class RenderBuffer {
  public:
    enum Type {
      VERTEX_BUFFER = GL_ARRAY_BUFFER,
      INDEX_BUFFER = GL_ELEMENT_ARRAY_BUFFER
    };
    enum Usage {
      STATIC_DRAW = GL_STATIC_DRAW,
      DYNAMIC_DRAW = GL_DYNAMIC_DRAW,
      STREAM_DRAW = GL_STREAM_DRAW
    };

    RenderBuffer();
    ~RenderBuffer();

    void init(Type type, Usage usage);
  
    void bind() const;

    void write(size_t size, const unsigned char *data);

  private:
    RenderBuffer(const RenderBuffer &other) {}
    RenderBuffer &operator=(const RenderBuffer &other) { return *this; }

    void release();
  
    Type type_;
    Usage usage_;

    unsigned id_;
  };


  // -----------------------------------------------------------------------------
  // VertexBuffer
  // -----------------------------------------------------------------------------


  class VertexBuffer : public RenderBuffer {
  public:
    enum ElementType {
      POINTS = GL_POINTS,
      LINE_STRIP = GL_LINE_STRIP,
      LINE_LOOP = GL_LINE_LOOP,
      LINES = GL_LINES,
      TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
      TRIANGLE_FAN = GL_TRIANGLE_FAN,
      TRIANGLES = GL_TRIANGLES
    };

    void init(ElementType type, RenderBuffer::Usage usage=RenderBuffer::DYNAMIC_DRAW);

    ElementType elementType() const;

  private:
    ElementType elementType_;
  };


  // -----------------------------------------------------------------------------
  // IndexBuffer
  // -----------------------------------------------------------------------------


  class IndexBuffer : public RenderBuffer {
  public:
    enum IndexType {
      UBYTE = GL_UNSIGNED_BYTE,
      USHORT = GL_UNSIGNED_SHORT,
      UINT = GL_UNSIGNED_INT
    };

    void init(IndexType type, RenderBuffer::Usage usage=RenderBuffer::DYNAMIC_DRAW);

    IndexType indexType() const;
  
  private:
    IndexType indexType_;
  };


} // ewok


#endif  // RENDERBUFFER_H_
