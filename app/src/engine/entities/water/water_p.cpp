#include "water_p.h"
#include "entities/ifc/i3dentity.h"
#include "shaders/water/water_shader.h"
#include "shaders/water/water_wireframe_shader.h"
#include "tools/mesh_generator.h"
#include "tools/resource_manager.h"
#include "tools/constants.h"
#include "camera/camera.h"
#include "entities/normal_map.h"
#include "entities/water/fft/fft.h"

namespace kite
{
   WaterImpl::WaterImpl(I3DEntity* parent_) : m_parent(parent_), m_reflection(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), m_texDudv(_R("/textures/water/dudv1.jpg")), m_texCaustics(_R("/textures/water/caustics.jpg"))
   {
      m_texDudv.bind();
      m_texDudv.trilinearFilter();
      m_texDudv.unbind();

      m_texCaustics.bind();
      m_texCaustics.trilinearFilter();
      m_texCaustics.unbind();

      m_shader = &WaterShader::Instance();
      m_patch.allocate(MeshGenerator::GenerateWaterPatch(32), 16);

      m_waterCfg.Load(_P("/cfg/water_config.xml"));

      //setting up normal map
      m_normalMap = new NormalMap(m_waterCfg.GetN());
      m_normalMap->SetStrenght(m_waterCfg.GetNormalStrenght());

      m_fft = new FFT(m_waterCfg.GetN(), m_waterCfg.GetL(), m_waterCfg.GetAmplitude(), m_waterCfg.GetWindDirection(),
         m_waterCfg.GetWindSpeed(), m_waterCfg.GetCappilarWavesSuppresion(), m_waterCfg.GetDelta(), m_waterCfg.IsChoppy());

      m_fft->Init();

      m_parent->GetWorldTransform().SetScaling(glm::vec3(ZFAR, 1, ZFAR));
      m_parent->GetWorldTransform().SetTranslation(glm::vec3(-ZFAR / 2, -800, -ZFAR / 2));
   }

   WaterImpl::~WaterImpl()
   {
      if (m_fft)
      {
         delete m_fft;
         m_fft = nullptr;
      }

      if (m_normalMap)
      {
         delete m_normalMap;
         m_normalMap = nullptr;
      }
   }

   void WaterImpl::Render()
   {
      m_distortion += m_waterCfg.GetDistortion();
      m_motion += m_waterCfg.GetMotion();

      m_fft->Render();
      m_normalMap->Render(m_fft->GetDy());

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

      //Y displacement
      glActiveTexture(GL_TEXTURE0);
      m_fft->GetDy().bind();
      m_shader->setInt("Dy", 0);

      //X displacement
      glActiveTexture(GL_TEXTURE1);
      m_fft->GetDx().bind();
      m_shader->setInt("Dx", 1);

      //Z displacement
      glActiveTexture(GL_TEXTURE2);
      m_fft->GetDz().bind();
      m_shader->setInt("Dz", 2);

      //FS
	  //light
      m_shader->setVec3("directional_light.direction", glm::vec3(0.0f, 0.0f, -1.0f));
	  //shader->setVec3("directional_light.direction", glm::vec3(0.f, 1000.f, -2000.0f));
      m_shader->setFloat("directional_light.intensity", 1.0f);
      m_shader->setVec3("directional_light.ambient", glm::vec3(0.38f, 0.28f, 0.28f));
      m_shader->setVec3("directional_light.color", glm::vec3(1.0f, 0.85f, 0.77f));
	  
	  glActiveTexture(GL_TEXTURE3);
	  m_reflection.GetTexture().bind();
     m_shader->setInt("waterReflection", 3);
	  
	  //so far without refraction
	  //GL_TEXTURE4
	  
	  glActiveTexture(GL_TEXTURE5);
	  m_texDudv.bind();
     m_shader->setInt("dudvRefracReflec", 5);
	  
     m_shader->setFloat("distortionRefracReflec", m_distortion);
	  
	  //UnderWater
	  glActiveTexture(GL_TEXTURE6);
	  m_texDudv.bind();
     m_shader->setInt("dudvCaustics", 6);
	  
     m_shader->setFloat("distortionCaustics", 0);
	  
	  //UnderWater
	  glActiveTexture(GL_TEXTURE7);
	  m_texCaustics.bind();
     m_shader->setInt("caustics", 7);
	  
     m_shader->setFloat("motion", m_motion);
	  
	  glActiveTexture(GL_TEXTURE8);
	  m_normalMap->GetTexture().bind();
     m_shader->setInt("normalmap", 8);
	  
	  m_shader->setFloat("kReflection", m_waterCfg.GetKReflection());
	  m_shader->setFloat("kRefraction", m_waterCfg.GetKRefraction());
	  m_shader->setInt("windowWidth", SCREEN_WIDTH);
	  m_shader->setInt("windowHeight", SCREEN_HEIGHT);
	  m_shader->setInt("texDetail", m_waterCfg.GetUvScale());
	  m_shader->setFloat("emission", m_waterCfg.GetEmission());
	  m_shader->setFloat("specular", m_waterCfg.GetSpecular());
	  m_shader->setInt("isCameraUnderWater", 0);

      m_patch.draw();
	  
	  glFinish();
   }
}
