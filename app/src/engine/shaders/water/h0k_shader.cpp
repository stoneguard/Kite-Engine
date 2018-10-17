#include "h0k_shader.h"
#include "tools/resource_manager.h"

namespace kite
{
   H0KShader& H0KShader::Instance()
   {
      static H0KShader inst;
      return inst;
   }
   
   H0KShader::H0KShader()
   {
      Init();
   }
   
   void H0KShader::Init()
   {
      AttachComputeShader(_P("/shaders/water/fft/h0k.comp"));
      Link();
   }  
}