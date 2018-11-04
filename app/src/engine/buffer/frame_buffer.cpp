#include "frame_buffer.h"
#include "GL/gl3w.h"
#include <iostream>

namespace kite
{
	FrameBuffer::FrameBuffer()
	{
	   glGenFramebuffers(1, &m_id);
	}
	
	void FrameBuffer::bind()
	{
	   glBindFramebuffer(GL_FRAMEBUFFER, m_id);
	
	   //
	   glClearColor(0.1f, 0.125f, 0.24f, 1.0f);
	   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	
	void FrameBuffer::unbind()
	{
	   glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	
	void FrameBuffer::createColorTextureAttachment(unsigned texId_, int i_)
	{
	   glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i_, GL_TEXTURE_2D, texId_, 0);
	}
	
	void FrameBuffer::createDepthBufferAttachment(unsigned width_, int height_)
	{
	   unsigned depthBuffer;
	   glGenRenderbuffers(1, &depthBuffer);
	
	   glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
	   glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32F, width_, height_);
	   glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);
	}
	
	void FrameBuffer::setDrawBuffers(const std::vector<unsigned>& buffer_)
	{
	   glDrawBuffers((GLsizei)buffer_.size(), &buffer_[0]);
	}
	
	void FrameBuffer::checkStatus() const
	{
	   if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	      std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	}
}