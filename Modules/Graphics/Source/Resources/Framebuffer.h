#pragma once
#include "../GraphicsExports.h"
#include <ForgexMath.h>

namespace Forgex::Graphics::Resources
{
	struct GRAPHICS_API Framebuffer
	{
	public:
		Framebuffer(Math::UVec2 size);
		~Framebuffer();

		void UpdateSize(Math::UVec2 newSize);

		unsigned int GetTextureID() const { return m_TextureBufferID; }
		Math::UVec2 GetFramebufferSize() const { return m_Size; }
	private:
		Math::UVec2 m_Size;

		unsigned int m_TextureBufferID;
		unsigned int m_ColorBufferID;
		unsigned int m_RenderBufferID;
	};
}
