#pragma once
#include "ImGui\imgui.h"
#include "ImGui\backend\imgui_impl_dx9.h"
#include "ImGui\backend\imgui_impl_win32.h"
#include "AuUI_Widgets.hpp"
#include <d3d9.h>
#include <tchar.h>
#include <vector>

enum AuUICol_
{
    AuUICol_Text,
    AuUICol_TextDisabled,
    AuUICol_WindowBg,              // Background of normal windows
    AuUICol_ChildBg,               // Background of child windows
    AuUICol_PopupBg,               // Background of popups, menus, tooltips windows
    AuUICol_Border,
    AuUICol_BorderShadow,
    AuUICol_FrameBg,               // Background of checkbox, radio button, plot, slider, text input
    AuUICol_FrameBgHovered,
    AuUICol_FrameBgActive,
    AuUICol_TitleBg,
    AuUICol_TitleBgActive,
    AuUICol_TitleBgCollapsed,
    AuUICol_MenuBarBg,
    AuUICol_ScrollbarBg,
    AuUICol_ScrollbarGrab,
    AuUICol_ScrollbarGrabHovered,
    AuUICol_ScrollbarGrabActive,
    AuUICol_CheckMark,
    AuUICol_SliderGrab,
    AuUICol_SliderGrabActive,
    AuUICol_Button,
    AuUICol_ButtonHovered,
    AuUICol_ButtonActive,
    AuUICol_Header,                // Header* colors are used for CollapsingHeader, TreeNode, Selectable, MenuItem
    AuUICol_HeaderHovered,
    AuUICol_HeaderActive,
    AuUICol_Separator,
    AuUICol_SeparatorHovered,
    AuUICol_SeparatorActive,
    AuUICol_ResizeGrip,
    AuUICol_ResizeGripHovered,
    AuUICol_ResizeGripActive,
    AuUICol_Tab,
    AuUICol_TabHovered,
    AuUICol_TabActive,
    AuUICol_TabUnfocused,
    AuUICol_TabUnfocusedActive,
    AuUICol_PlotLines,
    AuUICol_PlotLinesHovered,
    AuUICol_PlotHistogram,
    AuUICol_PlotHistogramHovered,
    AuUICol_TableHeaderBg,         // Table header background
    AuUICol_TableBorderStrong,     // Table outer and header borders (prefer using Alpha=1.0 here)
    AuUICol_TableBorderLight,      // Table inner borders (prefer using Alpha=1.0 here)
    AuUICol_TableRowBg,            // Table row background (even rows)
    AuUICol_TableRowBgAlt,         // Table row background (odd rows)
    AuUICol_TextSelectedBg,
    AuUICol_DragDropTarget,
    AuUICol_NavHighlight,          // Gamepad/keyboard: current highlighted item
    AuUICol_NavWindowingHighlight, // Highlight window when using CTRL+TAB
    AuUICol_NavWindowingDimBg,     // Darken/colorize entire screen behind the CTRL+TAB window list, when active
    AuUICol_ModalWindowDimBg,      // Darken/colorize entire screen behind a modal window, when one is active
    AuUICol_COUNT
};

class ButtonAnimation
{
public:
    ButtonAnimation(bool Border, bool BorderAnimation, bool FrameAnimation) :
        Border(Border), BorderAnimation(BorderAnimation), FrameAnimation(FrameAnimation)
    {}

    bool Border = false;
    bool BorderAnimation = false;
    bool FrameAnimation = true;
};

class AnimationConfiguration
{
public:
    AnimationConfiguration(float Speed, ButtonAnimation buttonAnimation) :
        Speed(Speed), button(buttonAnimation)
    {}

    float Speed; // Speed of any animation (Right now it's this but soon it will be individually for every widget)
    ButtonAnimation button;
};

namespace AuUI
{

	extern ImGuiWindowFlags AUUI_DEFAULT_FLAGS;

	class WindowData 
	{
	public:
		WindowData(const char* name, bool* pOpen, ImVec2 size, ImVec2 pos, ImGuiWindowFlags flags) :
			Name(name), pOpen(pOpen), Size(size), Pos(pos), Flags(flags | AUUI_DEFAULT_FLAGS)
		{}
		
		WindowData(const char* name, ImVec2 size, ImVec2 pos, ImGuiWindowFlags flags) :
			Name(name), pOpen(nullptr), Size(size), Pos(pos), Flags(flags | AUUI_DEFAULT_FLAGS)
		{}

		WindowData(const char* name, bool* pOpen, ImVec2 pos, ImVec2 size) :
			Name(name), pOpen(pOpen), Size(size), Pos(pos), Flags(AUUI_DEFAULT_FLAGS)
		{}

		WindowData(const char* name, ImVec2 size, ImVec2 pos) :
			Name(name), pOpen(nullptr), Size(size), Pos(pos), Flags(AUUI_DEFAULT_FLAGS)
		{}

        WindowData(const char* name, ImVec2 size) :
            Name(name), pOpen(nullptr), Size(size), Pos(-1, -1), Flags(AUUI_DEFAULT_FLAGS)
        {}

		WindowData(const char* name) :
			Name(name), pOpen(nullptr), Size(ImVec2(-1, -1)), Flags(ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse)
		{}

		const char* GetName() const { return Name; } 
		bool* GetOpen() const { return pOpen; }
		ImVec2 GetSize() const { return Size; }
        ImVec2 GetPos() const { return Pos; }
		ImGuiWindowFlags GetFlags() const { return Flags; };

		// Clearing the flags will make the window look like the default ImGui and if you prefer it then use this function!

		void clearFlags() { Flags = 0; }
		void clearFlags(ImGuiWindowFlags flags) { Flags = flags; }
	private:
		const char* Name;
		bool* pOpen;
		ImVec2 Size, Pos;
		ImGuiWindowFlags Flags;
	};

   

	// Forward declarations
	void InitImGui(HWND hwnd, LPDIRECT3DDEVICE9 device);

	void BeginFrame();
	void EndFrame();
	
	void Begin(const WindowData& windowData);
	void End();

    void LoadStyle();
    ImGuiStyle* GetStyle();
    ImGuiIO* GetIO();

}
