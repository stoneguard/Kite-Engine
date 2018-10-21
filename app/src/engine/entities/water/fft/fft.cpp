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

   }
}