#include "Hkt.h"
#include "shaders/water/hkt_shader.h"
#include <GL/gl3w.h>

namespace kite
{
   Hkt::Hkt(int N, int L) : m_N(N), m_L(L), 
   m_imageDyCoefficients(N, N, 1),
   m_imageDxCoefficients(N, N, 1),
   m_imageDzCoefficients(N, N, 1)
   {
      m_shader = &HktShader::Instance();
   }
   
   Hkt::~Hkt()
   {
   }
   
   void Hkt::SetH0K(const Texture& tex_)
   {
      m_imageH0k = tex_;
   }
   
   void Hkt::SetH0MinusK(const Texture& tex_)
   {
      m_imageH0minusK = tex_;
   }
   
   const Texture& Hkt::GetImageDyCoeficcients() const
   {
      return m_imageDyCoefficients;
   }
   
   const Texture& Hkt::GetImageDxCoeficcients() const
   {
      return m_imageDxCoefficients;
   }
   
   const Texture& Hkt::GetImageDzCoeficcients() const
   {
      return m_imageDzCoefficients;
   }
   
   void Hkt::Render(float t)
   {
      m_shader->Use();
      m_shader->setInt("L", m_L);
      m_shader->setInt("N", m_N);
      m_shader->setFloat("t", t);
   
      glBindImageTexture(0, m_imageDyCoefficients.GetID(), 0, false, 0, GL_READ_WRITE, GL_RGBA32F);
      glBindImageTexture(1, m_imageDxCoefficients.GetID(), 0, false, 0, GL_READ_WRITE, GL_RGBA32F);
      glBindImageTexture(2, m_imageDzCoefficients.GetID(), 0, false, 0, GL_READ_WRITE, GL_RGBA32F);
      glBindImageTexture(3, m_imageH0k.GetID(), 0, false, 0, GL_READ_ONLY, GL_RGBA32F);
      glBindImageTexture(4, m_imageH0minusK.GetID(), 0, false, 0, GL_READ_ONLY, GL_RGBA32F);
      glDispatchCompute(m_N / 16, m_N / 16, 1);
      glFinish();
   }
}