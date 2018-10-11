#include "shaders/water/water_shader.h"
#include "tools/resource_manager.h"

namespace kite
{
   WaterShader& WaterShader::Instance()
   {
      static WaterShader inst;
      return inst;
   }
   
   WaterShader::WaterShader()
   {
      Init();
   }
   
   void WaterShader::Init()
   {
      //TODO
      //vertex shader
      //fragment shader
   
      BaseShader::Link();
   }
}