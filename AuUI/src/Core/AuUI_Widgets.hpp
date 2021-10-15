#pragma once
#include "AuUI.hpp"

namespace AuUI 
{
	void Text(const char* fmt, ...);
	bool Button(const char* text, const char* button_id, ImVec2 size, ImGuiButtonFlags flags = 0);
	bool CreateTab(const char* name, const char* tab_id);
	bool Checkbox(const char* label, const char* check_id, bool* v);
}