#ifndef TEXTURE_VIEWER_H
#define TEXTURE_VIEWER_H
#include "texture/texture.h"

namespace kite
{
   /*
      \brief Texture viewer is able to show textures(images) for debugging purpose
   */
   class TextureViewer
   {
   public:
      TextureViewer();
   
      void Draw(const Texture& tex_);
   private:
      unsigned m_VBO = 0;
      unsigned m_VAO = 0;
      unsigned m_EBO = 0;
   };
}
#endif//TEXTURE_VIEWER_H
