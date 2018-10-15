#include "water_p.h"
#include "entities/ifc/i3dentity.h"
#include "shaders/water/water_shader.h"
#include "tools/mesh_generator.h"
#include "tools/resource_manager.h"
#include "tools/constants.h"
#include "camera/camera.h"

namespace kite
{
   WaterImpl::WaterImpl(I3DEntity* parent_) : m_parent(parent_)
   {
      m_shader = &WaterShader::Instance();
      m_patch.allocate(MeshGenerator::GenerateWaterPatch(32), 16);

      m_waterCfg.Load(_P("/cfg/water_config.xml"));

      m_parent->GetWorldTransform().SetScaling(glm::vec3(ZFAR, 1, ZFAR));
      m_parent->GetWorldTransform().SetTranslation(glm::vec3(-ZFAR / 2, -40, -ZFAR / 2));
   }

   void WaterImpl::Render()
   {
      m_shader->Use();

      //vertex
      m_shader->setMat4("worldMatrix", m_parent->GetWorldTransform().GetWorldMatrix());
      //tc
      m_shader->setVec3("eyePosition", Camera::Instance().GetPosition());
      m_shader->setInt("tessFactor", m_waterCfg.GetTessellationFactor());
      m_shader->setFloat("tessSlope", m_waterCfg.GetTessellationSlope());
      m_shader->setFloat("tessShift", m_waterCfg.GetTessellationShift());
      //te
      m_shader->setInt("texDetail", m_waterCfg.GetUvScale());
      //gs
      m_shader->setMat4("viewProjectionMatrix", Camera::Instance().GetProjMatrix() *  Camera::Instance().GetViewMatrix());
      m_shader->setFloat("displacementScale", m_waterCfg.GetDisplacementScale());
      m_shader->setInt("largeDetailRange", m_waterCfg.GetHighDetailRange());
      m_shader->setFloat("choppiness", m_waterCfg.GetChoppiness());

      m_patch.draw();
   }
}
