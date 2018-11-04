#include "shaders/water/water_wireframe_shader.h"
#include "tools/resource_manager.h"

namespace kite
{
   WaterWireFrameShader& WaterWireFrameShader::Instance()
   {
      static WaterWireFrameShader inst;
      return inst;
   }
   
   WaterWireFrameShader::WaterWireFrameShader()
   {
      Init();
   }
   
   void WaterWireFrameShader::Init()
   {
      AttachVertexShader(_P("/shaders/water/wireframe/vertex.glsl"));
      AttachTessellationControlShader(_P("/shaders/water/wireframe/tc.glsl"));
      AttachTessellationEvaluationShader(_P("/shaders/water/wireframe/te.glsl"));
      AttachGeometryShader(_P("/shaders/water/wireframe/geometry.glsl"));
      AttachFragmentShader(_P("/shaders/water/wireframe/fragment.glsl"));
   
      Link();
   }
}