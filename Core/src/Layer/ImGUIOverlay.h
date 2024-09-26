#pragma once
#include "Layer.h"
#include "../Application.h"

#include <imgui/imgui.h>
#include <imgui/backends/OpenGL/imgui_impl_opengl3.h>

class ENGINE_API ImGUIOverlay : public Layer
{
	using EventCallbackFn = std::function<void(Event&)>;

public:
	ImGUIOverlay(const Scene* activeScene) : Layer("ImGui") {}
	ImGUIOverlay(const Scene* activeScene, const EventCallbackFn& callback) : Layer("ImGui", callback) {}

	~ImGUIOverlay()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui::DestroyContext();
	}

	void OnAttach() override
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGui_ImplOpenGL3_Init();
	}

	void OnUpdate(float deltaTime) override
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(1720.0f, 1080.0f);

		Renderer::ToggleWireframe(m_WireframeActive);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();
		DisplayMenu();
		DisplayStats();
	}

	void DisplayMenu()
	{
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("Utils"))
			{
				ImGui::Checkbox("Wireframe", &m_WireframeActive);
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}
	}

	void DisplayStats()
	{
		ImGui::SetNextWindowBgAlpha(0.35f);
		if (ImGui::Begin("Profiler"))
		{
			ImGui::Text("Active scene: %s", m_ActiveScene->GetName());
			ImGui::Separator();

			ImGui::Text("Displaying all profiles");
			ImGui::Separator();

			for (auto it = Profiler::begin(); it != Profiler::end(); it++)
			{
				ImGui::Text("%s: %.4f", it->second.m_Label, it->second.ReadValue<float>());
			}
		}
		ImGui::End();
	}

	void OnRender(const Renderer& renderer) override
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void OnEvent(Event& event) override
	{
		EventDispatcher dispatcher(event);
		
		dispatcher.Dispatch<MousePositionEvent>(BIND_EVENT_FUNCTION(ImGUIOverlay::OnMousePosition));
		dispatcher.Dispatch<MouseClickEvent>(BIND_EVENT_FUNCTION(ImGUIOverlay::OnMouseClick));
		dispatcher.Dispatch<MouseUnclickEvent>(BIND_EVENT_FUNCTION(ImGUIOverlay::OnMouseUnclicked));
		dispatcher.Dispatch<SceneChangeEvent>(BIND_EVENT_FUNCTION(ImGUIOverlay::OnSceneChanged));
	}

	bool OnMousePosition(MousePositionEvent& e) 
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(e.GetPositionX(), e.GetPositionY());
		return false;
	}

	bool OnMouseClick(MouseClickEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetButton()] = true;
		return false;
	}

	bool OnMouseUnclicked(MouseUnclickEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetButton()] = false;
		return false;
	}

	bool OnSceneChanged(SceneChangeEvent& e) 
	{
		m_ActiveScene = e.GetScene();
		return true;
	}

private:
	bool m_WireframeActive = false;
	const Scene* m_ActiveScene = nullptr;
};