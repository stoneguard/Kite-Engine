#ifndef FFT_H
#define FFT_H
#include <glm/glm.hpp>
#include "texture/texture.h"
#include "texture/texture_viewer.h" //for debug purpose

namespace kite
{
   class H0K;
   class Hkt;
   class TwiddleFactors;
   /*
      \brief Fast fourier transform model, which makes move pixels within textures like an ocean wave.
   */
   class FFT 
   {
   public:
      FFT(int N, int L, float amplitude, const glm::vec2& direction, float intensity, float capillarSupressFactor, float t_delta, bool choopy);
      ~FFT();
   
      //Initialize initial state of textures, which is start point of calculations
      void Init();
   
      //Makes move "waves" within textures at each frame (according specific delta time)
      void Render();
    
      //With a help of these methods we can get actual heightmaps for mesh, since its "waving" at each frame according FFT.
      //Get dY texture, affect on a vertical(y) translation of waves
      const Texture& GetDy() const;

      //Get dX texture, affect on a horizontal(x) translation of waves
      const Texture& GetDx() const;

      //Get dZ texture, affect on a horizontal(z) translation of waves
      const Texture& GetDz() const;
   
   private:
      Texture           m_texPingpong;             //[input/output] for butterfly calculation. It is playing a role of input at some moment and then it turns out as an output for another data.
      
      // Following textures are destinations of all calculations of computer shaders
      Texture           m_texDy;                   //[output] resulting texture for Y displacement. 
      Texture           m_texDx;                   //[output] resulting texture for X displacement. 
      Texture           m_texDz;                   //[output] resulting texture for Z displacement. 
   
      bool              m_choppy = false;          //in order to make waves more sharper we need to calculate dx and dz displacement
      int               m_log_2_N = 0;             //count of butterfly operations
      int               m_pingpong = 0;            //some kind of switcher. 0 - write to m_texPingpong, 1 - read from m_texPingpong
      int               m_N = 0;                   //determine space for output texture divided by 16 (size of patch value)
      float             m_time_accumulator = 0.f;  //accumulate time as with a step determined by m_t_delta
      double            m_systemTime = 0.0;        //start point time. need to get difference between time points
      float             m_t_delta = 0.f;           //constant time factor. How fast mesh will waving
      
      //TODO
      /*
         -butterfly
         -twiddle
         -inversion
      */
      H0K*              m_h0k = nullptr;
      Hkt*              m_hkt = nullptr;
      TwiddleFactors*   m_twiddleFactors = nullptr;
   
      //for debug purpose
      TextureViewer m_texViewer;
   };
}
#endif//FFT_H
