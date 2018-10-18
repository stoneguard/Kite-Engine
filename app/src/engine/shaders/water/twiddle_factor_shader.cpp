#include "shaders/water/twiddle_factor_shader.h"
#include "tools/resource_manager.h"

namespace kite
{
   TwiddleFactorShader& TwiddleFactorShader::Instance()
   {
      static TwiddleFactorShader inst;
      return inst;
   }
   
   TwiddleFactorShader::TwiddleFactorShader()
   {
      Init();
   }
   
   void TwiddleFactorShader::Init()
   {
      AttachComputeShader(_P("/shaders/water/fft/twiddleFactors.comp"));
      Link();
   }  
}