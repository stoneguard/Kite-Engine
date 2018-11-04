#ifndef REFLECTION_H
#define REFLECTION_H
#include "texture/texture.h"
#include "buffer/frame_buffer.h"

namespace kite
{
	class TextureViewer;
	
   /*
      \brief Representation of reflection of water surface. Need to render mirrored scene to frame buffer and get a result as a texture.
   */
	class Reflection
	{
	public:
	   Reflection(unsigned width_, unsigned height_);
	   ~Reflection();
	
	   const Texture& GetTexture() const;
	
	   void bind();
	   void unbind();
	
	   void Render();
	private:
	   Texture        m_deferredLightingSceneTexture;
	   
	   Texture        m_albedoTexture;
	   Texture        m_normalTexture;
	
	   FrameBuffer    m_fbo;
	
	   unsigned       m_width = 0;
	   unsigned       m_height = 0;
	
	   TextureViewer* m_texViewer = nullptr;
	};
}

#endif//REFLECTION_H