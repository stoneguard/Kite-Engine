#include "shaders/water/inversion_shader.h"
#include "tools/resource_manager.h"

namespace kite
{
   InversionShader& InversionShader::Instance()
   {
      static InversionShader inst;
      return inst;
   }
   
   InversionShader::InversionShader()
   {
      Init();
   }
   
   void InversionShader::Init()
   {
      AttachComputeShader(_P("/shaders/water/fft/inversion.comp"));
      Link();
   }  
}