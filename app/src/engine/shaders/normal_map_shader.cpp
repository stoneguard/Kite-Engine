#include "shaders/normal_map_shader.h"
#include "tools/resource_manager.h"
#include <string>

namespace kite
{
   NormalMapShader& NormalMapShader::Instance()
   {
      static NormalMapShader inst;
      return inst;
   }
   
   NormalMapShader::NormalMapShader()
   {
      Init();
   }
   
   void NormalMapShader::Init()
   {
      AttachComputeShader(_P("/shaders/normal_map.glsl"));
      Link();
   }
}