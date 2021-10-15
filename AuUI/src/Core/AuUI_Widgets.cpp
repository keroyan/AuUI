#include "ImGui/imgui_internal.h"
#include "AuUI_Widgets.hpp"
#include "AuUI_internal.h"
#include <map>

namespace AuUI 
{
    // Please remember that this helper or whatever you want to call it is for animation hence if you wont use animation
    // then use ImGui becuase there isn't any point of using this framework other than that!
    // Unless you want to use it because it makes imgui easier to use then enjoy. -<->-

    static inline ImVec2 operator*(const ImVec2& lhs, const float rhs) { return ImVec2(lhs.x * rhs, lhs.y * rhs); }
    static inline ImVec2 operator/(const ImVec2& lhs, const float rhs) { return ImVec2(lhs.x / rhs, lhs.y / rhs); }
    static inline ImVec2 operator+(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x + rhs.x, lhs.y + rhs.y); }
    static inline ImVec2 operator-(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x - rhs.x, lhs.y - rhs.y); }
    static inline ImVec2 operator*(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x * rhs.x, lhs.y * rhs.y); }
    static inline ImVec2 operator/(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x / rhs.x, lhs.y / rhs.y); }
    static inline ImVec2& operator*=(ImVec2& lhs, const float rhs) { lhs.x *= rhs; lhs.y *= rhs; return lhs; }
    static inline ImVec2& operator/=(ImVec2& lhs, const float rhs) { lhs.x /= rhs; lhs.y /= rhs; return lhs; }
    static inline ImVec2& operator+=(ImVec2& lhs, const ImVec2& rhs) { lhs.x += rhs.x; lhs.y += rhs.y; return lhs; }
    static inline ImVec2& operator-=(ImVec2& lhs, const ImVec2& rhs) { lhs.x -= rhs.x; lhs.y -= rhs.y; return lhs; }
    static inline ImVec2& operator*=(ImVec2& lhs, const ImVec2& rhs) { lhs.x *= rhs.x; lhs.y *= rhs.y; return lhs; }
    static inline ImVec2& operator/=(ImVec2& lhs, const ImVec2& rhs) { lhs.x /= rhs.x; lhs.y /= rhs.y; return lhs; }
    static inline ImVec4 operator+(const ImVec4& lhs, const ImVec4& rhs) { return ImVec4(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w); }
    static inline ImVec4 operator-(const ImVec4& lhs, const ImVec4& rhs) { return ImVec4(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w); }
    static inline ImVec4 operator*(const ImVec4& lhs, const ImVec4& rhs) { return ImVec4(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z, lhs.w * rhs.w); }

    struct TabData 
    {
        ImVec2 position;
    };

    float speedAnimation = 9.0f;


    template<class T, class U>
    static T Clamp(T in, U low, U high) 
    {
        return in <= low ? low : in >= high ? high : in;
    }

    void AuUI::Text(const char* fmt, ...)
    {
        va_list args;
        va_start(args, fmt);
        ImGui::Text(fmt, args);
        va_end(args);
    }

    float CalcAnimation(float startingPoint, float speed, float delta, float starting, float ending, bool* when)
    {
        return Clamp(startingPoint + (speed * ImGui::GetIO().DeltaTime * (*when ? starting : -starting)), starting, ending);
    }

    // Need to create an actual config system to set all the ways you want! 
    bool border = false;
    bool borderAnim = false;
    float startingValue = 100 / 255;
    
    bool AuUI::Button(const char* text, const char* button_id, ImVec2 size, ImGuiButtonFlags flags)
    {
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        if (window->SkipItems)
            return false;

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID(button_id);
        const ImVec2 label_size = ImGui::CalcTextSize(text);
        ImDrawList* draw = ImGui::GetWindowDrawList();
        
        // Calculations
        ImVec2 startPos = window->DC.CursorPos;
        if ((flags & ImGuiButtonFlags_AlignTextBaseLine) && style.FramePadding.y < window->DC.CurrLineTextBaseOffset) // Try to vertically align buttons that are smaller/have no padding so that text baseline matches (bit hacky, since it shouldn't be a flag)
            startPos.y += window->DC.CurrLineTextBaseOffset - style.FramePadding.y;

        // Min is the position we want and max is the position we want and the plus the size ( the way it's made is weird but using AuUI drawing it's a lot easier to make elements)
        ImRect buttonSize = ImRect(startPos, startPos + size);

        // Setting that this position & size is reserved for this id
        ImGui::ItemSize(buttonSize);
        if (!ImGui::ItemAdd(buttonSize, id))
            return false;

        // Getting what's happening with the button in this specific frame!
        bool hovered, held;
        bool pressed = ImGui::ButtonBehavior(buttonSize, id, &hovered, &held);

        // Creating Animation & Rendering
        static std::map<ImGuiID, float> alphaAnimation;

        // Finding our id
        auto aSpecificButton = alphaAnimation.find(id);

        // if it doesn't exist we insert
        if (aSpecificButton == alphaAnimation.end())
            alphaAnimation.insert({ id, 0.5f }),
            aSpecificButton = alphaAnimation.find(id);

        // Calculating the next alpha value in this specific frame
        aSpecificButton->second = CalcAnimation(aSpecificButton->second, speedAnimation, ImGui::GetIO().DeltaTime, 0.5f, 1.0f, &hovered);

        // Converting U32 to ImColor is a bit of hassle!
        ImColor
            staticCol = ImGui::ColorConvertU32ToFloat4(ImGui::GetColorU32(AuUICol_Button)),
            hoverCol = ImGui::ColorConvertU32ToFloat4(ImGui::GetColorU32(AuUICol_ButtonHovered)),
            heldCol = ImGui::ColorConvertU32ToFloat4(ImGui::GetColorU32(AuUICol_ButtonActive));
  

        const ImColor col = 
            (held && hovered) ? ImColor(heldCol.Value.x, heldCol.Value.y, heldCol.Value.z, aSpecificButton->second) :
            hovered ? ImColor(hoverCol.Value.x, hoverCol.Value.y, hoverCol.Value.z, aSpecificButton->second)
            : ImColor(staticCol.Value.x, staticCol.Value.y, staticCol.Value.z, aSpecificButton->second);

        // Rendering the main bg
        ImGui::RenderFrame(buttonSize.Min, buttonSize.Max, col, true, 3.0f);

        // Rendering Border
        if (border)
        {
            // If border animation is set to false then we will set alpha to 255 which the max value
            if (!borderAnim)
                aSpecificButton->second = 255;

            draw->AddRect(buttonSize.Min, buttonSize.Max, ImColor(1.0f, 0.f, 0.f, aSpecificButton->second), 6.0f);
        }
         
        // Rendering Text 
        draw->AddText(ImVec2(((buttonSize.Min.x + buttonSize.Max.x) / 2) - label_size.x * 0.5f, ((buttonSize.Min.y + buttonSize.Max.y) / 2) - label_size.y * 0.5f), ImGui::GetColorU32(AuUICol_Text), text);

        // Returning if the button was pressed on this specific frame!
        return pressed;
    }



    bool AuUI::CreateTab(const char* name, const char* tab_id) 
    {
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        if (window->SkipItems)
            return false;

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID(tab_id);
        const ImVec2 label_size = ImGui::CalcTextSize(name);

        ImDrawList* draw = ImGui::GetWindowDrawList();
        ImVec2 startPos = window->DC.CursorPos;

        static std::map<ImGuiID, ImVec2> tabs;

        auto currentTab = tabs.find(id);
        if (currentTab == tabs.end()) 
            tabs.insert({ id, startPos }),
            currentTab = tabs.find(id);

        currentTab->second = startPos;

        ImRect size = ImRect(ImVec2(startPos), ImVec2(startPos + label_size));
        ImGui::ItemSize(size);
        if (!ImGui::ItemAdd(size, id))
            return false;

        bool hovered, held;
        bool pressed = ImGui::ButtonBehavior(size, id, &hovered, &held);

        static std::map<ImGuiID, float> slideAnimation;

        auto currentTabSlide = slideAnimation.find(id);

        // if it doesn't exist we insert
        if (currentTabSlide == slideAnimation.end())
            slideAnimation.insert({ id, 2.f }),
            currentTabSlide = slideAnimation.find(id);

        // Calculating the next alpha value in this specific frame
        currentTabSlide->second = CalcAnimation(currentTabSlide->second, 20.0f, ImGui::GetIO().DeltaTime, 2.f, 10.0f, &hovered);

        draw->AddText(currentTab->second + ImVec2(currentTabSlide->second, 0), ImColor(255, 255, 255, 255), name);

        return true;
    }



    bool AuUI::Checkbox(const char* label, const char* check_id, bool* v) 
    {
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        if (window->SkipItems)
            return false;

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID(label);
        const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

        const float square_sz = ImGui::GetFrameHeight();
        const ImVec2 pos = window->DC.CursorPos;
        const ImRect total_bb(pos, pos + ImVec2(square_sz + (label_size.x > 0.0f ? style.ItemInnerSpacing.x + label_size.x : 0.0f), label_size.y + style.FramePadding.y * 2.0f));

        ImGui::ItemSize(total_bb, style.FramePadding.y);
        if (!ImGui::ItemAdd(total_bb, id))
        {
            IMGUI_TEST_ENGINE_ITEM_INFO(id, label, g.LastItemData.StatusFlags | ImGuiItemStatusFlags_Checkable | (*v ? ImGuiItemStatusFlags_Checked : 0));
            return false;
        }

        bool hovered, held;
        bool pressed = ImGui::ButtonBehavior(total_bb, id, &hovered, &held);
        if (pressed)
        {
            *v = !(*v);
            ImGui::MarkItemEdited(id);
        }


        static std::map<ImGuiID, float> borderAnimation;

        auto currentBorderAnimation = borderAnimation.find(id);

        // if it doesn't exist we insert
        if (currentBorderAnimation == borderAnimation.end())
            borderAnimation.insert({ id, 1.f }),
            currentBorderAnimation = borderAnimation.find(id);

        // Calculating the next alpha value in this specific frame
        currentBorderAnimation->second = CalcAnimation(currentBorderAnimation->second, 50.0f, ImGui::GetIO().DeltaTime, 1.f, 10.0f, v);

        static std::map<ImGuiID, float> rectAnimation;

        auto currentRectAnimation = rectAnimation.find(id);

        // if it doesn't exist we insert
        if (currentRectAnimation == rectAnimation.end())
            rectAnimation.insert({ id, 1.f }),
            currentRectAnimation = rectAnimation.find(id);

        // Calculating the next alpha value in this specific frame
        currentRectAnimation->second = CalcAnimation(currentRectAnimation->second, 30.f, ImGui::GetIO().DeltaTime, 1.f, 10.0f, v);


        static std::map<ImGuiID, float> checkmarkAnimation;
        static std::map<ImGuiID, float> checkmark2Animation;

        auto currentCheckmarkAnimation = checkmarkAnimation.find(id);
        auto currentCheckmark2Animation = checkmark2Animation.find(id);

        // if it doesn't exist we insert
        if (currentCheckmarkAnimation == checkmarkAnimation.end() && currentCheckmark2Animation == checkmark2Animation.end())
            checkmarkAnimation.insert({ id, 1.f }),
            currentCheckmarkAnimation = checkmarkAnimation.find(id),
            checkmark2Animation.insert({ id, 1.f }),
            currentCheckmark2Animation = checkmark2Animation.find(id);

        // Calculating the next alpha value in this specific frame
        currentCheckmarkAnimation->second = CalcAnimation(currentCheckmarkAnimation->second, 30.f, ImGui::GetIO().DeltaTime, 1.f, 5.0f, v);
        currentCheckmark2Animation->second = CalcAnimation(currentCheckmark2Animation->second, 30.f, ImGui::GetIO().DeltaTime, 1.f, 7.0f, v);

        const ImRect check_bb(pos, pos + ImVec2(square_sz, square_sz));
        const float pad = ImMax(1.0f, IM_FLOOR(square_sz / 6.0f));
        
        ImColor
            staticCol = ImGui::ColorConvertU32ToFloat4(ImGui::GetColorU32(ImGuiCol_FrameBg)),
            hoverCol = ImGui::ColorConvertU32ToFloat4(ImGui::GetColorU32(ImGuiCol_FrameBgHovered)),
            heldCol = ImGui::ColorConvertU32ToFloat4(ImGui::GetColorU32(ImGuiCol_FrameBgActive));

        ImGui::RenderNavHighlight(total_bb, id);
        ImGui::RenderFrame(check_bb.Min, check_bb.Max, (held && hovered) ? heldCol : hovered ? hoverCol : heldCol, true, 1.0f);
         
        window->DrawList->AddRect(check_bb.Min + ImVec2(10 - currentBorderAnimation->second, 10 - currentBorderAnimation->second), check_bb.Max - ImVec2(10 - currentBorderAnimation->second, 10 - currentBorderAnimation->second), ImColor(255, 255, 255, 255), 1.0f, 0);
        window->DrawList->AddRectFilled(check_bb.Min + ImVec2(10 - currentRectAnimation->second, 10 - currentRectAnimation->second), check_bb.Max - ImVec2(10 - currentRectAnimation->second, 10 - currentRectAnimation->second), ImColor(255, 255, 255, currentRectAnimation->second == 1.f ? 0 : 255), 1.0f, 0);

        static float minX = -2, minY = 4, maxX = -6 + currentRectAnimation->second, maxY = -2 + currentRectAnimation->second;

        if (currentRectAnimation->second >= 1.f)
        {
            window->DrawList->AddLine(pos + ImVec2(square_sz / 4, square_sz / 4) + ImVec2(-2, 4), pos + ImVec2(square_sz / 2, square_sz / 2) + ImVec2(-6 + currentCheckmarkAnimation->second, -2 + currentCheckmark2Animation->second), ImColor(255, 0, 0, 255), 2.f);
            window->DrawList->AddLine(pos + ImVec2(square_sz / 2, square_sz / 2) + ImVec2(-3, 4), pos + ImVec2(square_sz -3, 4), ImColor(255, 0, 0, 255), 2.f);
        }

        ImGui::SliderFloat("Min X", &currentCheckmarkAnimation->second, -100, 100);
        ImGui::SliderFloat("Min X", &currentCheckmark2Animation->second, -100, 100);

        bool mixed_value = (g.LastItemData.InFlags & ImGuiItemFlags_MixedValue) != 0;

        ImVec2 label_pos = ImVec2(check_bb.Max.x + style.ItemInnerSpacing.x, check_bb.Min.y + style.FramePadding.y);
        if (g.LogEnabled)
            ImGui::LogRenderedText(&label_pos, mixed_value ? "[~]" : *v ? "[x]" : "[ ]");
        if (label_size.x > 0.0f)
            ImGui::RenderText(label_pos, label);

        IMGUI_TEST_ENGINE_ITEM_INFO(id, label, g.LastItemData.StatusFlags | ImGuiItemStatusFlags_Checkable | (*v ? ImGuiItemStatusFlags_Checked : 0));
        return pressed;
    }
}