#include "water_p.h"
#include "shaders/water/water_shader.h"
#include "tools/mesh_generator.h"
#include "tools/resource_manager.h"

namespace kite
{
   WaterImpl::WaterImpl()
   {
      m_shader = &WaterShader::Instance();
      m_patch.allocate(MeshGenerator::GenerateWaterPatch(32), 16);

      m_waterCfg.Load(_P("/cfg/water_config.xml"));
   }

   void WaterImpl::Render()
   {
      m_shader->Use();

      m_patch.draw();
   }
}
