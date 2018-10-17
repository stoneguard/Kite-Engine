#include "h0k.h"
#include "shaders/water/h0k_shader.h"
#include "texture/texture.h"
#include "tools/resource_manager.h"
#include <GL/gl3w.h>
#include <string>

namespace kite
{

   H0K::H0K(int N, int L, float amplitude, glm::vec2 direction, float intensity, float capillarSupressFactor) :
      m_N(N), m_L(L), m_amplitude(amplitude), m_direction(direction), m_intensity(intensity), m_capillarSupressFactor(capillarSupressFactor),
      m_texImageH0k(N, N, 1),
      m_texImageH0minusK(N, N, 1),
      m_texNoise0(_R("/textures/Noise256_0.jpg")),
      m_texNoise1(_R("/textures/Noise256_1.jpg")),
      m_texNoise2(_R("/textures/Noise256_2.jpg")),
      m_texNoise3(_R("/textures/Noise256_3.jpg"))
   {
      m_shader = &H0KShader::Instance();
   }
   
   H0K::~H0K()
   {
      
   }
   
   const Texture& H0K::GetH0K() const
   {
      return m_texImageH0k;
   }
   
   const Texture& H0K::GetH0MinusK() const
   {
      return m_texImageH0minusK;
   }
   
   void H0K::Render()
   {
      m_shader->Use();
      m_shader->setInt("N", m_N);
      m_shader->setInt("L", m_L);
      m_shader->setFloat("amplitude", m_amplitude);
      m_shader->setFloat("intensity", m_intensity);
      m_shader->setVec2("direction", m_direction);
      m_shader->setFloat("capillarSupressFactor", m_capillarSupressFactor);
   
      glActiveTexture(GL_TEXTURE0);
      m_texNoise0.bind();
   
      glActiveTexture(GL_TEXTURE1);
      m_texNoise1.bind();
   
      glActiveTexture(GL_TEXTURE2);
      m_texNoise2.bind();
   
      glActiveTexture(GL_TEXTURE3);
      m_texNoise3.bind();
   
      m_shader->setInt("noise_r0", 0);
      m_shader->setInt("noise_i0", 1);
      m_shader->setInt("noise_r1", 2);
      m_shader->setInt("noise_i1", 3);
   
      glBindImageTexture(0, m_texImageH0k.GetID(), 0, false, 0, GL_WRITE_ONLY, GL_RGBA32F);
   
      glBindImageTexture(1, m_texImageH0minusK.GetID(), 0, false, 0, GL_WRITE_ONLY, GL_RGBA32F);
   
      glDispatchCompute(m_N / 16, m_N / 16, 1);
   }
}