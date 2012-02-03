#ifndef SPRITERENDERER_H_
#define SPRITERENDERER_H_


#include "Renderable.h"
#include "RenderProgram.h"
#include "RenderUniforms.h"
#include "RenderBuffer.h"
#include "Shader.h"
#include "Vector.h"
#include "Matrix.h"
#include "Sprite.h"
#include "TextureAtlas.h"


namespace ewok {


  template<typename T>
  class SpriteRenderer : public ewok::IRenderable {
  public:
    SpriteRenderer(unsigned maxSprites);

    virtual void init(const Shader &vshader, const Shader &fshader,
                      const TextureAtlas &atlas);


    void update(const std::vector<T> &sprites);

    void render();

    void setProjection(const Matrix4 p);

  private:
    struct RenderSprite {
      struct Vertex {
        Vector3 position;
        Vector2 texCoord;
        float alpha;
        Vector3 colorTransform;
      } v1, v2, v3, v4, v5, v6;
    };

    std::vector<RenderSprite> renderSprites_;
    unsigned numActiveSprites_;

    RenderProgram program_;
    VertexBuffer vbuffer_;

    Matrix4 projection_;
    
    TextureAtlas texAtlas_;

    RenderUniform uniTexture_;
    RenderUniform uniMVP_;
  };


  // implementation ------------------------------------------------------------
  

  template<typename T>
  SpriteRenderer<T>::SpriteRenderer(unsigned maxSprites)
    : renderSprites_(maxSprites)
  {
  }


  template<typename T>  
  void SpriteRenderer<T>::init(const Shader &vshader,
                            const Shader &fshader,
                            const TextureAtlas &atlas)
  {
    texAtlas_ = atlas;
      
    RenderAttribs attribs(4);
    attribs.set(0, "a_position", RenderAttrib::FLOAT, 3);
    attribs.set(1, "a_texCoord", RenderAttrib::FLOAT, 2);
    attribs.set(2, "a_alpha", RenderAttrib::FLOAT, 1);
    attribs.set(3, "a_colorTransform", RenderAttrib::FLOAT, 3);
      
    program_.init(vshader, fshader, attribs);
    vbuffer_.init(VertexBuffer::TRIANGLES);

    RenderUniforms unis = program_.use();
    uniTexture_ = unis.getUniform("u_texture");
    uniMVP_ = unis.getUniform("u_mvp");
  }


  template<typename T>  
  void SpriteRenderer<T>::update(const std::vector<T> &sprites)
  {
    numActiveSprites_ = 0;
    unsigned numSprites = sprites.size();
    unsigned numRenderSprites = renderSprites_.size();

    for (unsigned i = 0; i < numSprites; ++i) {

      const T &s = sprites[i];
      if (!s.isUsed()) {
        continue;
      }
      Assert(numActiveSprites_ < numRenderSprites, "Limit of renderSprites_ reached");

      RenderSprite &rs = renderSprites_[numActiveSprites_];
      ++numActiveSprites_;
      
      const Quad verts = s.vertices();
      const float &alpha = s.alpha;
      const Vector3 &colorTransform = s.colorTransform;

      const Vector4 &tile = texAtlas_.getTile(s.tileId);
        
      // LogInfo << "texcoords: " << tile.x << "/" << tile.y << " - " << tile.z << "/" << tile.w;
      // LogInfo << "alpha    : " << alpha;
      // LogInfo << "verts: " << verts.v1.x << "/" << verts.v1.y << "/" << verts.v1.z << ", "
      //         << verts.v2.x << "/" << verts.v2.y << "/" << verts.v2.z << ", "
      //         << verts.v3.x << "/" << verts.v3.y << "/" << verts.v3.z << ", "
      //         << verts.v4.x << "/" << verts.v4.y << "/" << verts.v4.z;

      rs.v1.position = verts.v1;
      rs.v1.texCoord.x = tile.x; // 0
      rs.v1.texCoord.y = tile.w; // 1
      rs.v1.alpha = alpha;
      rs.v1.colorTransform = colorTransform;

      rs.v2.position = verts.v2;
      rs.v2.texCoord.x = tile.z; // 1
      rs.v2.texCoord.y = tile.w; // 1
      rs.v2.alpha = alpha;
      rs.v2.colorTransform = colorTransform;

      rs.v3.position = verts.v4;
      rs.v3.texCoord.x = tile.x; // 0
      rs.v3.texCoord.y = tile.y; // 0
      rs.v3.alpha = alpha;
      rs.v3.colorTransform = colorTransform;
      
      rs.v4.position = verts.v3;
      rs.v4.texCoord.x = tile.z; // 1
      rs.v4.texCoord.y = tile.y; // 0
      rs.v4.alpha = alpha;
      rs.v4.colorTransform = colorTransform;
      
      rs.v5 = rs.v3;
      rs.v6 = rs.v2;
    }
    vbuffer_.write(sizeof(RenderSprite) * numActiveSprites_,
                   (const unsigned char *)&renderSprites_[0]);

    // LogInfo << "Number of active sprites: " << numActiveSprites_;
  }

  
  template<typename T>
  void SpriteRenderer<T>::render()
  {
    texAtlas_.activate(0);

    uniTexture_.set1i(0);
    uniMVP_.setMat4f(projection_);

    program_.render(vbuffer_, 0, numActiveSprites_ * 6);
  }


  template<typename T>  
  void SpriteRenderer<T>::setProjection(const Matrix4 p)
  {
    projection_ = p;
  }


  
} // namespace ewok

#endif // SPRITERENDERER_H_
