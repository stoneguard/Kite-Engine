#include "shaders/atmosphere/ScatteringShader.h"
#include "tools/resource_manager.h"
#include <string>

namespace kite
{
   ScatteringShader& ScatteringShader::Instance()
   {
      static ScatteringShader inst;
      return inst;
   }
   
   ScatteringShader::ScatteringShader()
   {
      Init();
   }
   
   void ScatteringShader::Init()
   {
      AttachVertexShader(_P("/shaders/atmosphere/vertex.glsl"));
      AttachFragmentShader(_P("/shaders/atmosphere/fragment.glsl")); 
   
      Link();
   }
}