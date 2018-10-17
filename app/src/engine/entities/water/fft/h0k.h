#ifndef H0K_H
#define H0K_H
#include <glm/glm.hpp>
#include "texture/texture.h"

namespace kite
{
   class H0KShader;
   
   /*
      \brief Evaluate two parts of initial equation H0(K) + H0(-K) and provide the result as a textures
   */
   class H0K
   {
   public:
      H0K(int N, int L, float amplitude, glm::vec2 direction, float intensity, float capillarSupressFactor);
      ~H0K();
   
      void Render();
   
      //Since K is vector of direction of the wave

      //Get texture, which is the result of fourier amplitude
      const Texture& GetH0K() const;
   
      //same, but opposite direction
      const Texture& GetH0MinusK() const;
   
   private:
      int         m_N = 0;                         //
      int         m_L = 0;                         //horizontal dimension of the patch
      glm::vec2   m_direction;                     //wave direction
      float       m_intensity = 0.f;               //
      float       m_amplitude = 0.f;               //amplitude of oscillation
      float       m_capillarSupressFactor = 0.f;   //
   
      //storing initial spectrum
      Texture     m_texImageH0k;       
      Texture     m_texImageH0minusK;  

      //noise textures, which is used for calculating texture above. The following textures are loaded from hdd
      Texture     m_texNoise0;         
      Texture     m_texNoise1;
      Texture     m_texNoise2;
      Texture     m_texNoise3;
   
      H0KShader*  m_shader = nullptr;
   };
}

#endif//H0K_H
