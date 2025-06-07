#include "Framebuffer.h"
#include <ForgexDebugTools.h>
#include <GL/glew.h>

namespace Forgex::Graphics::Resources
{
	Framebuffer::Framebuffer(Math::UVec2 size) : m_Size(size)
	{
		glGenFramebuffers(1, &m_TextureBufferID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_TextureBufferID);

		// Create texture for color attachment
		glGenTextures(1, &m_ColorBufferID);
		glBindTexture(GL_TEXTURE_2D, m_ColorBufferID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size.x, size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorBufferID, 0);

		glGenRenderbuffers(1, &m_RenderBufferID);
		glBindRenderbuffer(GL_RENDERBUFFER, m_RenderBufferID);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, size.x, size.y);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_RenderBufferID);
	
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			LOG_CORE(Debug::LogLevel::Error, "FRAMEBUFFER::Framebuffer is not complete!");

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}
	
	Framebuffer::~Framebuffer() {}

	void Framebuffer::UpdateSize(Math::UVec2 newSize)
	{
	 	if(newSize == m_Size) return;

		m_Size = newSize;

		glBindFramebuffer(GL_FRAMEBUFFER, m_TextureBufferID);
		glBindTexture(GL_TEXTURE_2D, m_ColorBufferID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Size.x, m_Size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorBufferID, 0);

		glBindRenderbuffer(GL_RENDERBUFFER, m_RenderBufferID);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, m_Size.x, m_Size.y);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_RenderBufferID);

		glBindTexture(GL_TEXTURE_2D, 0);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}	
}
