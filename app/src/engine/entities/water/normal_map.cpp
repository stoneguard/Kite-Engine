#include "normal_map.h"
#include "shaders/normal_map_shader.h"
#include <cmath>
#include "GL/gl3w.h"

namespace kite
{
   NormalMap::NormalMap(int N_) : m_texNormalMap(N_, N_, (int)(std::log(N_) / std::log(2))), m_N(N_)
   {
      m_texNormalMap.bind();
      m_texNormalMap.trilinearFilter();
      m_texNormalMap.unbind();
   }
   
   NormalMap::~NormalMap()
   {
      
   }
   
   void NormalMap::SetHeightMapID(unsigned ID_)
   {
      m_heightMapTextureID = ID_;
   }
   
   void NormalMap::SetStrenght(float strenght_)
   {
      m_strenght = strenght_;
   }
   
   unsigned NormalMap::GetID() const
   {
      return m_texNormalMap.GetID();
   }
   
   const Texture& NormalMap::GetTexture() const
   {
      return m_texNormalMap;
   }
   
   void NormalMap::Render()
   {
      auto& shader = NormalMapShader::Instance();
      shader.Use();
   
      //привыз€ываемс€ к карте высот
      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, m_heightMapTextureID);
   
      shader.setInt("displacementmap", 0);
      shader.setInt("N", m_N);
      shader.setFloat("normalStrength", m_strenght);
      
      glBindImageTexture(0, m_texNormalMap.GetID(), 0, false, 0, GL_WRITE_ONLY, GL_RGBA32F);
      glDispatchCompute(m_N / 16, m_N / 16, 1);
      glFinish();
   
      m_texNormalMap.bind();
      m_texNormalMap.bilinearFilter();
      m_texNormalMap.unbind();
   }
   
   void NormalMap::Render(const Texture& tex_)
   {
      auto& shader = NormalMapShader::Instance();
      shader.Use();
   
      glActiveTexture(GL_TEXTURE0);
      tex_.bind();
      shader.setInt("displacementmap", 0);
      shader.setInt("N", m_N);
      shader.setFloat("normalStrength", m_strenght);
   
      glBindImageTexture(0, m_texNormalMap.GetID(), 0, false, 0, GL_WRITE_ONLY, GL_RGBA32F);
      glDispatchCompute(m_N / 16, m_N / 16, 1);
      glFinish();
      m_texNormalMap.bind();
      m_texNormalMap.trilinearFilter();
      m_texNormalMap.unbind();
   
      //m_texViewer.Draw(m_texNormalMap);
   }
}