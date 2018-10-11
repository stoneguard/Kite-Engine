#include "water_p.h"
#include "shaders/water/water_shader.h"

namespace kite
{
   WaterImpl::WaterImpl()
   {
      m_shader = &WaterShader::Instance();
   }

   void WaterImpl::Render()
   {
      m_shader->Use();
   }
}
