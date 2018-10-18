#ifndef TWIDDLE_FACTORS_H
#define TWIDDLE_FACTORS_H
#include "texture/texture.h"
#include <vector>

namespace kite
{
   class TwiddleFactorShader;
   
   /*
      \brief Model for computing twiddle factors. It is used as input data for FFT equation. 
   */
   class TwiddleFactors
   {
   public:
      TwiddleFactors(int N);
      ~TwiddleFactors();
   
      //Provide calculated factors as texture
      const Texture& GetTexture() const;

      void Render();

   private:
      //need to start from reversed bit order, in order to get original sequence of fT
      std::vector<int> initBitReversedIndices();
   private:
      int                     m_N = 0;
      int                     m_log_2_N = 0;
      Texture                 m_t_factors;
      TwiddleFactorShader*    m_shader = nullptr;
      //TODO shader storage buffer 
   };
}
#endif//TWIDDLE_FACTORS_H