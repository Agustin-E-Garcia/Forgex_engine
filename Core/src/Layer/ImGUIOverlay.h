#pragma once
#include "Layer.h"
#include "Window.h"
#include "Profiler/Profiler.h"
#include "Utils/glfwToImGui.h"

#include <imgui/imgui.h>
#include <imgui/backends/OpenGL/imgui_impl_opengl3.h>

class ENGINE_API Menu
{
public:
	Menu(const char* name) : m_Name(name) {}
	~Menu() {}

	inline void Draw()
	{
		Begin();
		OnDraw();
		End();
	};

protected:
	const char* m_Name;

	inline void Begin() { ImGui::Begin(m_Name); }
	inline void End() { ImGui::End(); }
	virtual void OnDraw() {};
};

class ENGINE_API ImGUIOverlay : public Layer
{
	using EventCallbackFn = std::function<void(Event&)>;

public:
	ImGUIOverlay() : Layer("ImGui") {}
	ImGUIOverlay(const EventCallbackFn& callback) : Layer("ImGui", callback) {}

	~ImGUIOverlay()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui::DestroyContext();
	}

	void OnAttach() override
	{
		IMGUI_CHECKVERSION();
		m_ImGuiContext = ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGui_ImplOpenGL3_Init();

		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(Application::GetWindow()->GetWidth(), Application::GetWindow()->GetHeight());
	}

	void OnUpdate(float deltaTime) override
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		//ImGui::ShowDemoWindow();
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
		dispatcher.Dispatch<MouseWheelScrollEvent>(BIND_EVENT_FUNCTION(ImGUIOverlay::OnMouseWheelScroll));
		dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FUNCTION(ImGUIOverlay::OnKeyPressedEvent));
		dispatcher.Dispatch<KeyReleasedEvent>(BIND_EVENT_FUNCTION(ImGUIOverlay::OnKeyReleasedEvent));
		dispatcher.Dispatch<CharInputEvent>	(BIND_EVENT_FUNCTION(ImGUIOverlay::OnCharInputEvent));
		dispatcher.Dispatch<WindowResizedEvent>(BIND_EVENT_FUNCTION(ImGUIOverlay::OnWindowResized));
	}

protected:
	ImGuiContext* m_ImGuiContext = nullptr;

private:

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

	bool OnMouseWheelScroll(MouseWheelScrollEvent& e) 
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheel = e.GetYOffset();
		return false;
	}

	bool OnKeyPressedEvent(KeyPressedEvent& e) 
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddKeyEvent(glfwKeyToImGuiKey(e.GetKeyCode()), true);
		return false;
	}

	bool OnKeyReleasedEvent(KeyReleasedEvent& e) 
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddKeyEvent(glfwKeyToImGuiKey(e.GetKeyCode()), false);
		return false;
	}

	bool OnCharInputEvent(CharInputEvent& e) 
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddInputCharacter(e.GetKeyCode());
		return false;
	}

	bool OnWindowResized(WindowResizedEvent& e) 
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
		return false;
	}
};