#pragma once
#include "CoreExports.h"

namespace Forgex::Graphics::Resources { struct Framebuffer; }

namespace Forgex::Core
{
	struct CORE_API SessionContext
	{
	public:
		SessionContext();
		~SessionContext();

		const Graphics::Resources::Framebuffer* GetViewportFramebuffer(); 
	private:
		Graphics::Resources::Framebuffer* m_ViewportFramebuffer;
	};
}
