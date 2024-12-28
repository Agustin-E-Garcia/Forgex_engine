#pragma once
#include "Exports.h"

class ENGINE_API Framebuffer
{
public:
	Framebuffer(int width, int height);

	void TryUpdate(int width, int height);
	void BindBuffer();
	void UnbindBuffer();

	inline unsigned int GetTextureID() { return m_TextureColorBuffer; }

private:
	unsigned int m_FrameBuffer;
	unsigned int m_TextureColorBuffer;
	unsigned int m_RenderBuffer;

	int m_Width;
	int m_Height;
};