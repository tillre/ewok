#include "RenderBuffer.h"



namespace ewok {


  /// TODO, use glMapBuffer, cause video and cpu ram are the same !!!


  // -----------------------------------------------------------------------------
  // RenderBuffer
  // -----------------------------------------------------------------------------


  RenderBuffer::RenderBuffer()
    : type_(VERTEX_BUFFER),
      usage_(STATIC_DRAW)
  {
  }


  RenderBuffer::~RenderBuffer()
  {
    release();
  }


  void RenderBuffer::init(Type type, Usage usage)
  {
    type_ = type;
    usage_ = usage;
  
    glGenBuffers(1, &id_);
    Assert(id_, "Buffer could not be generated");
    CheckGLError();
  }


  void RenderBuffer::bind() const
  {
    Assert(id_, "Buffer id invalid, not initialized?");
    glBindBuffer(type_, id_);
    CheckGLError();
  }


  void RenderBuffer::write(size_t size, const unsigned char *data)
  {
    Assert(id_, "Buffer id invalid, not initialized?");
    glBindBuffer(type_, id_);
    glBufferData(type_, size, data, usage_);
    CheckGLError();
  }


  void RenderBuffer::release()
  {
    if (id_) {
      glBufferData(type_, 0, NULL, usage_);
      glDeleteBuffers(1, &id_);
      CheckGLError();
    }
  }


  // -----------------------------------------------------------------------------
  // VertexBuffer
  // -----------------------------------------------------------------------------


  void VertexBuffer::init(ElementType type, RenderBuffer::Usage usage)
  {
    RenderBuffer::init(RenderBuffer::VERTEX_BUFFER, usage);
    elementType_ = type;
  }


  VertexBuffer::ElementType VertexBuffer::elementType() const
  {
    return elementType_;
  }


  // -----------------------------------------------------------------------------
  // IndexBuffer
  // -----------------------------------------------------------------------------


  void IndexBuffer::init(IndexType type, RenderBuffer::Usage usage)
  {
    RenderBuffer::init(RenderBuffer::INDEX_BUFFER, usage);
    indexType_ = type;
  }


  IndexBuffer::IndexType IndexBuffer::indexType() const
  {
    return indexType_;
  }


} // namespace ewok
