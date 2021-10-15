#include "AuUI.hpp"
#include <iostream>
#include <string>
namespace AuUI 
{
    ImGuiWindowFlags AUUI_DEFAULT_FLAGS = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings;

    static inline ImVec2 AuLerp(const ImVec2& a, const ImVec2& b, float t) { return ImVec2(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t); }
    static inline ImVec2 AuLerp(const ImVec2& a, const ImVec2& b, const ImVec2& t) { return ImVec2(a.x + (b.x - a.x) * t.x, a.y + (b.y - a.y) * t.y); }
    static inline ImVec4 AuLerp(const ImVec4& a, const ImVec4& b, float t) { return ImVec4(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t, a.z + (b.z - a.z) * t, a.w + (b.w - a.w) * t); }
    
	void AuUI::InitImGui(HWND hwnd, LPDIRECT3DDEVICE9 device)
	{
        // These are ImGui initalize process for specifically DirectX 9 but can easily be modified for other versions e.g DirectX 12 or another graphical api that ImGui Support

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

        // Loading Style!
        LoadStyle();

        // Setup Platform/Renderer backends
        ImGui_ImplWin32_Init(hwnd);
        ImGui_ImplDX9_Init(device);
	}

    void AuUI::LoadStyle()
    {
        ImGuiStyle& style = ImGui::GetStyle();
        ImGuiIO& io = ImGui::GetIO();
    }

    void AuUI::BeginFrame() 
    {
        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
    }

    void AuUI::EndFrame() 
    {
        ImGui::EndFrame();
    }

    void AuUI::Begin(const WindowData& windowData)
    {
        if (windowData.GetSize().x != -1 && windowData.GetSize().y != -1)
            ImGui::SetNextWindowSize(windowData.GetSize(), ImGuiCond_FirstUseEver);

        if (windowData.GetPos().x != -1 && windowData.GetPos().y != -1)
            ImGui::SetNextWindowPos(windowData.GetSize(), ImGuiCond_FirstUseEver);

        // Creating the window with the data given to us
        ImGui::Begin(windowData.GetName(), windowData.GetOpen(), windowData.GetFlags());
    }

    void AuUI::End() 
    {
        ImGui::End();
    }

    ImGuiStyle* AuUI::GetStyle() { return &ImGui::GetStyle(); }

    ImGuiIO* AuUI::GetIO() 
    {
        return &ImGui::GetIO();
    }
}