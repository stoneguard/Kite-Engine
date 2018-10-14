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
      AttachVertexShader(_P("/shaders/water/vertex.glsl"));
      AttachTessellationControlShader(_P("/shaders/water/tc.glsl"));
      AttachTessellationEvaluationShader(_P("/shaders/water/te.glsl"));
      AttachGeometryShader(_P("/shaders/water/geometry.glsl"));
      AttachFragmentShader(_P("/shaders/water/fragment.glsl"));
   
      BaseShader::Link();
   }
}