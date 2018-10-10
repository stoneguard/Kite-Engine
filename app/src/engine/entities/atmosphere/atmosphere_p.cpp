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
      //scattering
      shader.setVec3("lightDir", glm::vec3(0.0f, 0.0f, 1.0f));//TODO
      shader.setFloat("fInnerRadius", INNER_RADIUS);
      shader.setFloat("fScaleOverScaleDepth", (1.0f / (OUTER_RADIUS - INNER_RADIUS)) / RAYLEIGHT_SCALE_DEPTH);
      shader.setFloat("fScale", 1.0f / (OUTER_RADIUS - INNER_RADIUS));
      shader.setFloat("fScaleDepth", RAYLEIGHT_SCALE_DEPTH);
      shader.setVec3("v3InvWavelength", glm::vec3(1 / RED_WAVE_LENGHT_POWERED, 1 / GREEN_WAVE_LENGHT_POWERED, 1 / BLUE_WAVE_LENGHT_POWERED));
      shader.setFloat("fKr4PI", K_R_4PI);
      shader.setFloat("fKm4PI", K_M_4PI);
      shader.setFloat("g", G);
      shader.setFloat("g2", G * G);

      //camera - static position
      shader.setVec3("cameraPosition", glm::vec3(0.0f, 1.0f, 0.0f));

      //matrices
      shader.setMat4("projection_matrix", Camera::Instance().GetProjMatrix());
      shader.setMat4("view_matrix", Camera::Instance().GetViewMatrix());
      shader.setMat4("model_matrix", m_sphere.GetWorldMatrix());

      glFrontFace(GL_CW);//inside only
      
      m_sphere.Draw();

      glFrontFace(GL_CCW);
   }
}