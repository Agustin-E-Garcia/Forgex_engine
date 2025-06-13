#include "UIWindowManager.h"
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>

#include <ForgexDebugTools.h>

namespace Forgex::UI
{
    UIWindowManager::UIWindowManager()
    {
    	IMGUI_CHECKVERSION();
    	m_ActiveContext = ImGui::CreateContext();
    	ImGuiIO& io = ImGui::GetIO();
    	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    	io.DisplaySize = ImVec2(800, 600);
    	io.KeyRepeatRate = 0.5f;

    	ImGui::StyleColorsDark();
    	ImGui_ImplOpenGL3_Init();
    }

    UIWindowManager::~UIWindowManager()
    {
    	ImGui_ImplOpenGL3_Shutdown();
    	ImGui::DestroyContext();
    }

    void UIWindowManager::SetContext()
    {
        ImGui::SetCurrentContext(static_cast<ImGuiContext*>(m_ActiveContext));
    }

    void UIWindowManager::Update(float deltaTime)
    {
    	ImGui_ImplOpenGL3_NewFrame();
    	ImGui::NewFrame();

        ImGui::DockSpaceOverViewport(0U, 0, ImGuiDockNodeFlags_PassthruCentralNode);

	for(GUIWindow* window : m_WindowCollection)
		window->Draw();
    }

    void UIWindowManager::Render()
    {
    	if (!m_WindowActive) return;

    	ImGui::Render();
    	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void UIWindowManager::UpdateMousePosition(double xPos, double yPos)
    {
        ImGui::GetIO().MousePos = ImVec2(xPos, yPos);
    }
    
    void UIWindowManager::OnMouseClick(unsigned int button, bool clicked)
    {
        ImGui::GetIO().MouseDown[button] = clicked;
    }

    void UIWindowManager::OnMouseWheelScroll(double xOffset, double yOffset)
    {
        ImGui::GetIO().MouseWheel = yOffset;
    }

    void UIWindowManager::OnCharInput(unsigned int keycode)
    {
        ImGui::GetIO().AddInputCharacter(keycode);
    }

    void UIWindowManager::OnKeyPressed(unsigned int keycode, bool repeat, bool pressed)
    {
        // need to implement a function to translate GLFW keycodes into ImGui keycodes
    }

    void UIWindowManager::OnWindowResized(int width, int height)
    {
        m_WindowActive = width > 0 && height > 0;
        if (!m_WindowActive) return;

        ImGui::GetIO().DisplaySize = ImVec2(width, height);
    }
}
