#include "twiddle_factors.h"
#include "shaders/water/twiddle_factor_shader.h"
#include <GL/gl3w.h>
#include <cmath>
#include "texture/texture.h"

namespace kite
{
   static inline uint32_t rotl32(uint32_t n, unsigned int c)
   {
      const unsigned int mask = (CHAR_BIT * sizeof(n) - 1);  // assumes width is a power of 2.
   
      c &= mask;
      //TODO
      return (n << c) | (n >> ((-c)&mask));
   }
   
   static inline uint32_t rotr32(uint32_t n, unsigned int c)
   {
      const unsigned int mask = (CHAR_BIT * sizeof(n) - 1);
   
      c &= mask;
      //TODO
      return (n >> c) | (n << ((-c)&mask));
   }
   
   uint32_t reverse32(uint32_t x)
   {
      x = ((x >> 1) & 0x55555555u) | ((x & 0x55555555u) << 1);
      x = ((x >> 2) & 0x33333333u) | ((x & 0x33333333u) << 2);
      x = ((x >> 4) & 0x0f0f0f0fu) | ((x & 0x0f0f0f0fu) << 4);
      x = ((x >> 8) & 0x00ff00ffu) | ((x & 0x00ff00ffu) << 8);
      x = ((x >> 16) & 0xffffu) | ((x & 0xffffu) << 16);
      return x;
   }
   
   TwiddleFactors::TwiddleFactors(int N) : m_N(N), m_log_2_N((int)(std::log(N) / std::log(2))), m_t_factors(m_log_2_N, m_N, 1)
   {
      m_shader = &TwiddleFactorShader::Instance();
   
      m_bitReversedSSBO.addData(initBitReversedIndices());
   }
   
   TwiddleFactors::~TwiddleFactors()
   {
     
   }
   
   const Texture& TwiddleFactors::GetTexture() const
   {
      return m_t_factors;
   }
   
   std::vector<int> TwiddleFactors::initBitReversedIndices()
   {
      std::vector<int> bitReversedIndices;
      bitReversedIndices.resize(m_N);
      int bits = (int)(std::log(m_N) / std::log(2));
   
      for (int i = 0; i<m_N; i++)
      {
         int x = reverse32(i);
         x = rotl32(x, bits);
   
         bitReversedIndices[i] = x;
      }
   
      return bitReversedIndices;
   }
   
   void TwiddleFactors::Render()
   {
      m_shader->Use();
   
      m_bitReversedSSBO.bindBufferBase(1);

      m_shader->setInt("N", m_N);
   
      glBindImageTexture(0, m_t_factors.GetID(), 0, false, 0, GL_WRITE_ONLY, GL_RGBA32F);
      glDispatchCompute(m_log_2_N, m_N / 16, 1);
   }
}