#include "fft.h"
#include "texture/texture.h"
#include <GL/gl3w.h>
#include <cmath>
#include <GLFW/glfw3.h>
#include "h0k.h"
#include "Hkt.h"
#include "twiddle_factors.h"
#include "shaders/water/butterflyshader.h"
#include "shaders/water/inversion_shader.h"

namespace kite
{
   FFT::FFT(int N, int L, float amplitude, const glm::vec2& direction, float intensity, float capillarSupressFactor, float t_delta, bool choopy) :
      m_texPingpong(N, N, 1),
      m_texDy(N, N, 1),
      m_texDx(N, N, 1),
      m_texDz(N, N, 1),
      m_choppy(choopy),
      m_t_delta(t_delta)
   {
      m_inversionShader = &InversionShader::Instance();
      m_butterFlyShader = &ButterFlyShader::Instance();

      m_N = N;
      m_log_2_N = (int)(std::log(N) / std::log(2));
      
      //create twiddle factor model. It creates a texture with suitable factors to use it in FFT algorith
      m_twiddleFactors = new TwiddleFactors(N);
      //initial equation
      m_h0k = new H0K(N, L, amplitude, direction, intensity, capillarSupressFactor);
      //time-depended equation
      m_hkt = new Hkt(N, L);

      m_systemTime = glfwGetTime() * 1000;//ms
   }
   
   FFT::~FFT()
   {
      if (m_twiddleFactors)
      {
         delete m_twiddleFactors;
         m_twiddleFactors = nullptr;
      }

      if (m_h0k)
      {
         delete m_h0k;
         m_h0k = nullptr;
      }

      if (m_hkt)
      {
         delete m_hkt;
         m_hkt = nullptr;
      }
   }
   
   void FFT::Init()
   {
      m_h0k->Render();
      m_twiddleFactors->Render();
      m_hkt->SetH0K(m_h0k->GetH0K());
      m_hkt->SetH0MinusK(m_h0k->GetH0MinusK());
   }
   
   const Texture& FFT::GetDy() const
   {
      return m_texDy;
   }
   
   const Texture& FFT::GetDx() const
   {
      return m_texDx;
   }
   
   const Texture& FFT::GetDz() const
   {
      return m_texDz;
   }
   
   void FFT::Render()
   {
      m_hkt->Render(m_time_accumulator);

      // Dy-FFT

      m_pingpong = 0;

      m_butterFlyShader->Use();

      glBindImageTexture(0, m_twiddleFactors->GetTexture().GetID(), 0, false, 0, GL_READ_WRITE, GL_RGBA32F);
      glBindImageTexture(1, m_hkt->GetImageDyCoeficcients().GetID(), 0, false, 0, GL_READ_WRITE, GL_RGBA32F);
      glBindImageTexture(2, m_texPingpong.GetID(), 0, false, 0, GL_READ_WRITE, GL_RGBA32F);

      // 1D FFT horizontal 
      for (int i = 0; i< m_log_2_N; i++)
      {
         m_butterFlyShader->setInt("pingpong", m_pingpong);
         m_butterFlyShader->setInt("direction", 0);
         m_butterFlyShader->setInt("stage", i);

         glDispatchCompute(m_N / 16, m_N / 16, 1);
         glFinish();
         m_pingpong++;
         m_pingpong %= 2;
      }

      //1D FFT vertical 
      for (int j = 0; j< m_log_2_N; j++)
      {
         m_butterFlyShader->setInt("pingpong", m_pingpong);
         m_butterFlyShader->setInt("direction", 1);
         m_butterFlyShader->setInt("stage", j);

         glDispatchCompute(m_N / 16, m_N / 16, 1);
         glFinish();
         m_pingpong++;
         m_pingpong %= 2;
      }

      m_inversionShader->Use();
      
      m_inversionShader->setInt("N", m_N);
      m_inversionShader->setInt("pingpong", m_pingpong);

      glBindImageTexture(0, m_texDy.GetID(), 0, false, 0, GL_READ_WRITE, GL_RGBA32F);
      glDispatchCompute(m_N / 16, m_N / 16, 1);
      glFinish();

      double time = glfwGetTime() * 1000;//ms

      //average difference between ticks = 16ms. with m_t_delta = 0.005 will get ~ 0.08 for each tick
      m_time_accumulator += static_cast<float>((time - m_systemTime) * m_t_delta);

      m_systemTime = glfwGetTime() * 1000;
   }
}