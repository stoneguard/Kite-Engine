#include "butterflyshader.h"
#include "tools/resource_manager.h"

namespace kite
{
   ButterFlyShader& ButterFlyShader::Instance()
   {
      static ButterFlyShader inst;
      return inst;
   }

   ButterFlyShader::ButterFlyShader()
   {
      Init();
   }

   void ButterFlyShader::Init()
   {
      AttachComputeShader(_P("/shaders/water/fft/butterfly.comp"));
      Link();
   }
}