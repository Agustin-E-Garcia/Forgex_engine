#include "SessionContext.h"
#include "HeaderSystem/UISceneProxy.h"
#include <ForgexGraphics.h>
#include <ForgexScene.h>
#include <ForgexMath.h>

#include <ForgexDebugTools.h>

namespace Forgex::Core
{
	SessionContext::SessionContext() {}

	SessionContext::~SessionContext()
	{
		if(m_ViewportFramebuffer) delete m_ViewportFramebuffer;
		if(m_UISceneProxy) delete m_UISceneProxy;
	}

	// ---------- ViewportFramebuffer ----------//
	unsigned int SessionContext::GetViewportID() { return Internal_GetViewportFramebuffer()->GetTextureID(); }

	void SessionContext::ResizeViewportFramebuffer(float width, float height)
	{
		Internal_GetViewportFramebuffer()->UpdateSize(Math::UVec2(width, height));
	}

	const Graphics::Resources::Framebuffer* SessionContext::GetViewportFramebuffer() { return Internal_GetViewportFramebuffer(); }

	Graphics::Resources::Framebuffer* SessionContext::Internal_GetViewportFramebuffer()
	{
		if(!m_ViewportFramebuffer) m_ViewportFramebuffer = new Graphics::Resources::Framebuffer();

		return m_ViewportFramebuffer;
	}
	// ---------- ViewportFramebuffer ----------//
	// ---------- UISceneProxy ----------//
	UISceneProxy* SessionContext::GetUISceneProxy() { return Internal_GetUISceneProxy(); }

	UISceneProxy* SessionContext::Internal_GetUISceneProxy()
	{
		if(!m_UISceneProxy) m_UISceneProxy = new UISceneProxy();

		return m_UISceneProxy;
	}

	void SessionContext::SyncUIProxy(Scene::Scene* scene)
	{
		Internal_GetUISceneProxy()->SyncScene(*scene);
	}
	// ---------- UISceneProxy ----------//

}
