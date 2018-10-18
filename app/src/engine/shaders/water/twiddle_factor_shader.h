#ifndef TWIDDLE_FACTOR_SHADER_H
#define TWIDDLE_FACTOR_SHADER_H
#include "shaders/base_shader.h"

namespace kite
{
   /*
      \brief Compute shader for twiddle factors. Provide input data to FFT equation.
   */
   class TwiddleFactorShader final : public BaseShader
   {
   private:
      TwiddleFactorShader();
   
      TwiddleFactorShader(TwiddleFactorShader const&) = delete;
      TwiddleFactorShader& operator= (TwiddleFactorShader const&) = delete;
   
   public:
      static TwiddleFactorShader& Instance();
   
      void Init() override final;
   };
}
#endif//TWIDDLE_FACTOR_SHADER_H