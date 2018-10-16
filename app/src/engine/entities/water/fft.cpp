#include "fft.h"
#include "texture/texture.h"
#include <GL/gl3w.h>
#include <cmath>
#include <GLFW/glfw3.h>

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
      m_N = N;
      m_log_2_N = (int)(std::log(N) / std::log(2));
      
      m_systemTime = glfwGetTime() * 1000;//ms
   }
   
   FFT::~FFT()
   {
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