#include "reflection.h"
#include "shaders/water/ReflectRefractShader.h"
#include <GL/gl3w.h>
#include "tools/constants.h"

//DEBUG
#include "texture/texture_viewer.h"

namespace kite
{
	Reflection::Reflection(unsigned width_, unsigned height_) :
	   m_deferredLightingSceneTexture(width_, height_), m_albedoTexture(width_, height_), m_normalTexture(width_, height_), m_width(width_), m_height(height_)
	{
	   m_texViewer = new TextureViewer();
	
	   m_deferredLightingSceneTexture.bind();
	   m_deferredLightingSceneTexture.allocateImage2D(GL_RGBA16F, GL_RGBA, GL_FLOAT);
	   m_deferredLightingSceneTexture.bilinearFilter();
	   m_deferredLightingSceneTexture.unbind();
	
	   //albedo
	   m_albedoTexture.bind();
	   m_albedoTexture.allocateImage2D(GL_RGBA16F, GL_RGBA, GL_FLOAT);
	   m_albedoTexture.noFilter();
	   m_albedoTexture.clampToEdge();
	   m_albedoTexture.unbind();
	
	   //normal
	   m_normalTexture.bind();
	   m_normalTexture.allocateImage2D(GL_RGBA16F, GL_RGBA, GL_FLOAT);
	   m_normalTexture.noFilter();
	   m_normalTexture.clampToEdge();
	   m_normalTexture.unbind();
	
	   std::vector<unsigned> buffer;
	   buffer.emplace_back(GL_COLOR_ATTACHMENT0);
	   buffer.emplace_back(GL_COLOR_ATTACHMENT1);
	   buffer.emplace_back(GL_COLOR_ATTACHMENT2);
	
	   m_fbo.bind();
	   m_fbo.createColorTextureAttachment(m_albedoTexture.GetID(), 0);
	   m_fbo.createColorTextureAttachment(m_normalTexture.GetID(), 2);
	   m_fbo.createDepthBufferAttachment(m_width, m_height);
	   m_fbo.setDrawBuffers(buffer);
	   m_fbo.checkStatus();
	   m_fbo.unbind();
	}
	
	Reflection::~Reflection()
	{
	   delete m_texViewer;
	   m_texViewer = nullptr;
	}
	
	const Texture& Reflection::GetTexture() const
	{
	   return m_deferredLightingSceneTexture;
	}
	
	void Reflection::bind()
	{
	   m_fbo.bind();
	}
	
	void Reflection::unbind()
	{
	   m_fbo.unbind();
	}
	
	void Reflection::Render()
	{
	   auto& shader = ReflectRefractShader::Instance();
	   shader.Use();
	
	   //shader.setBlockBinding("Camera", CAMERA_UNIFORM);
	   //shader.setVec3("camera.frustumPlanes", glm::vec3(1.0f, -2.0f, 1.0f));
	   //shader.setFloat("camera.m_View", 1.0f);
	   //shader.setVec3("camera.m_ViewProjection", glm::vec3(0.08f, 0.08f, 0.08f));
	   //shader.setVec3("camera.frustumPlanes", glm::vec3(1, 0.95f, 0.87f));
	
	   //shader.setBlockBinding("DirectionalLight", DIRECTIONAL_LIGHT);
	   shader.setVec3("directional_light.direction", glm::vec3(1.0f, -2.0f, 1.0f));
	   shader.setFloat("directional_light.intensity", 1.0f);
	   shader.setVec3("directional_light.ambient", glm::vec3(0.08f, 0.08f, 0.08f));
	   shader.setVec3("directional_light.color", glm::vec3(1, 0.95f, 0.87f));
	
	   glBindImageTexture(0, m_deferredLightingSceneTexture.GetID(), 0, false, 0, GL_WRITE_ONLY, GL_RGBA16F);
	   glBindImageTexture(1, m_albedoTexture.GetID(), 0, false, 0, GL_READ_ONLY, GL_RGBA16F);
	   glBindImageTexture(2, m_normalTexture.GetID(), 0, false, 0, GL_READ_ONLY, GL_RGBA32F);
	   
	   //glDispatchCompute(m_width / 8, m_height / 8, 1);
	   glDispatchCompute(m_width / 4, m_height / 4, 1);
	
	   //m_texViewer->Draw(m_deferredLightingSceneTexture);
	}

}