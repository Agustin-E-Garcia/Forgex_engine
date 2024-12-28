#pragma once
#include "Menus/SceneInspector.h"
#include "Menus/ProfilerViewer.h"
#include "Menus/Viewport.h"

class EngineUIOverlay : public ImGUIOverlay
{
public:
	EngineUIOverlay() : ImGUIOverlay() {};
	~EngineUIOverlay() 
	{
		delete m_SceneInspector;
		delete m_ProfileViewer;
		delete m_Viewport;
	};

	void OnAttach() override
	{
		ImGUIOverlay::OnAttach();
		ImGui::SetCurrentContext(m_ImGuiContext);
		
		m_SceneInspector = new SceneInspector();
		m_ProfileViewer = new ProfileViewer();
		m_Viewport = new Viewport();
	}

	void OnBegin() override
	{
		AddMenu(m_SceneInspector);
		AddMenu(m_ProfileViewer);
		AddMenu(m_Viewport);
	}

	void OnUpdate(float deltaTime) override 
	{
		if (!m_WindowActive) return;

		ImGUIOverlay::OnUpdate(deltaTime);

		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Debug"))
			{
				if (ImGui::Checkbox("Toggle Wireframe", &m_Wireframe)) { Renderer::ToggleWireframe(m_Wireframe); }
				if (ImGui::Checkbox("Toggle OpenGL face culling", &m_FaceCulling)) { Renderer::ToggleFaceCulling(m_FaceCulling); }
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Menus"))
			{
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}

		for (Menu* menu : m_MenuCollection)
			menu->Draw();
	}

	void OnRender(const Renderer& rend) override
	{
		ImGUIOverlay::OnRender(rend);
		rend.SetRenderTarget(m_Viewport->GetRenderTarget());
	}

	void OnEvent(Event& e) override
	{
		ImGUIOverlay::OnEvent(e);

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<SceneChangeEvent>(BIND_EVENT_FUNCTION(EngineUIOverlay::OnSceneChangedEvent));
	}

	bool OnSceneChangedEvent(SceneChangeEvent& e)
	{
		m_SceneInspector->SetActiveScene(e.GetScene());
		return true;
	}

private:
	std::vector<Menu*> m_MenuCollection;

	SceneInspector* m_SceneInspector = nullptr;
	ProfileViewer* m_ProfileViewer = nullptr;
	Viewport* m_Viewport = nullptr;

	bool m_Wireframe = false;
	bool m_FaceCulling = true;

	void AddMenu(Menu* menu)
	{
		m_MenuCollection.emplace_back(menu);
	}

	void RemoveMenu(Menu* menu)
	{
		auto it = std::find(m_MenuCollection.begin(), m_MenuCollection.end(), menu);
		if (it != m_MenuCollection.end())
			m_MenuCollection.erase(it);
	}
};