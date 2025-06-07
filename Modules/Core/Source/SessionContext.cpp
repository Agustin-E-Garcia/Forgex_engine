#include "SessionContext.h"
#include <ForgexGraphics.h>

namespace Forgex::Core
{
	SessionContext::SessionContext() {}

	SessionContext::~SessionContext()
	{
		if(m_ViewportFramebuffer) delete m_ViewportFramebuffer;
	}

	const Graphics::Resources::Framebuffer* SessionContext::GetViewportFramebuffer()
	{
		if(!m_ViewportFramebuffer) m_ViewportFramebuffer = new Graphics::Resources::Framebuffer();

		return m_ViewportFramebuffer;
	}
}
