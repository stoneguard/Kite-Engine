#include "atmosphere_p.h"
#include "tools/resource_manager.h"
#include "atmospheric_constants.h"
#include "shaders/atmosphere/ScatteringShader.h"
#include "camera/camera.h"

namespace kite
{
   AtmosphereImpl::AtmosphereImpl() : m_sphere(_R("/models/default_sphere.obj"))
   {
      m_sphere.SetTranslation(glm::vec3(0.0f, 0.0f, 0.0f));
      m_sphere.SetScale(glm::vec3(SPHERE_RADIUS, SPHERE_RADIUS, SPHERE_RADIUS));
   }

   void AtmosphereImpl::Render()
   {
      auto& shader = ScatteringShader::Instance();
      shader.Use();

      //set uniform variables
      shader.setMat4("projection_matrix", Camera::Instance().GetProjMatrix());
      shader.setMat4("view_matrix", Camera::Instance().GetViewMatrix());
      shader.setMat4("model_matrix", m_sphere.GetWorldMatrix());

      glFrontFace(GL_CW);//inside only
      
      m_sphere.Draw();

      glFrontFace(GL_CCW);
   }
}