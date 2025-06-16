#pragma once
#include "CoreExports.h"

namespace Forgex::Graphics::Resources { struct Framebuffer; }
namespace Forgex::Scene { class Scene; }

namespace Forgex::Core
{
	class UISceneProxy;	

	struct CORE_API SessionContext
	{
	public:
		SessionContext();
		~SessionContext();
		
	// ---------- ViewportFramebuffer ----------//
		const Graphics::Resources::Framebuffer* GetViewportFramebuffer(); 
		unsigned int GetViewportID();
		void ResizeViewportFramebuffer(float width, float height);
	// ---------- ViewportFramebuffer ----------//
	// ---------- UISceneProxy ----------//
		UISceneProxy* GetUISceneProxy();
		void SyncUIProxy(Scene::Scene* scene);
	// ---------- UISceneProxy ----------//
	private:
	// ---------- ViewportFramebuffer ----------//
		Graphics::Resources::Framebuffer* m_ViewportFramebuffer;
		Graphics::Resources::Framebuffer* Internal_GetViewportFramebuffer();
	// ---------- ViewportFramebuffer ----------//
	// ---------- UISceneProxy ----------//
		UISceneProxy* m_UISceneProxy;
		UISceneProxy* Internal_GetUISceneProxy();
	// ---------- UISceneProxy ----------//
	};
}
