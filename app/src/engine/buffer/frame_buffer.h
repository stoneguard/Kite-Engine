#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H
#include <vector>

namespace kite
{
   /*
      \brief Buffer for storing mirrored texture
   */
	class FrameBuffer
	{
	public:
	   FrameBuffer();
	
	   void bind();
	   void unbind();
	   
	   void createColorTextureAttachment(unsigned texId_, int i_);
	   void createDepthBufferAttachment(unsigned width_, int height_);
	   void setDrawBuffers(const std::vector<unsigned>& buffer_);
	   void checkStatus() const;
	
	private:
	   unsigned m_id;
	};
}

#endif//FRAME_BUFFER_H