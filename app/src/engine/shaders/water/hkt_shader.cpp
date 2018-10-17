#include "hkt_shader.h"
#include "tools/resource_manager.h"

namespace kite
{
   HktShader& HktShader::Instance()
   {
      static HktShader inst;
      return inst;
   }
   
   HktShader::HktShader()
   {
      Init();
   }
   
   void HktShader::Init()
   {
      AttachComputeShader(_P("/shaders/water/fft/hkt.comp"));
      Link();
   }  
}