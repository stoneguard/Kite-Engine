#ifndef NORMAL_MAP_H
#define NORMAL_MAP_H
#include "texture/texture.h"
#include "texture/texture_viewer.h"

namespace kite
{
   /*
      \brief Normal map provides normal vectors, which makes possible to calculate lighting
   */
   class NormalMap
   {
   public:
      NormalMap(int N_);
      ~NormalMap();
   
      void SetHeightMapID(unsigned ID_);
      void SetStrenght(float strenght_);
      unsigned GetID() const;
   
      const Texture& GetTexture() const;
   
      void Render();
   
      void Render(const Texture& tex_);
   
   private:
      Texture        m_texNormalMap;         //resulting texture of normals
      float          m_strenght = 0.f;
      int            m_N = 0;
      unsigned       m_heightMapTextureID = 0;
   
      //DEBUG
      TextureViewer  m_texViewer;
   };
}

#endif//NORMAL_MAP_H
