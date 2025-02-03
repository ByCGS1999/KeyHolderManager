#include <Themes.h>
#include <Includes.h>

void SetOceanBlueTheme()
{
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    // Ocean Blue theme colors
    colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.55f, 0.55f, 0.55f, 1.00f);
    colors[ImGuiCol_WindowBg] = ImVec4(0.15f, 0.20f, 0.30f, 1.00f);  // Dark ocean blue background
    colors[ImGuiCol_Border] = ImVec4(0.1f, 0.15f, 0.25f, 0.50f);     // Dark border color
    colors[ImGuiCol_Button] = ImVec4(0.35f, 0.55f, 0.75f, 1.00f);    // Light blue button
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.45f, 0.65f, 0.85f, 1.00f); // Hovered button (lighter blue)
    colors[ImGuiCol_ButtonActive] = ImVec4(0.25f, 0.45f, 0.65f, 1.00f); // Active button (dark blue)
    colors[ImGuiCol_Separator] = ImVec4(0.10f, 0.15f, 0.25f, 1.00f);   // Dark separator
}

void SetSunsetRedTheme()
{
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    // Sunset Red theme colors
    colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);     // White text
    colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f); // Disabled text
    colors[ImGuiCol_WindowBg] = ImVec4(0.20f, 0.10f, 0.10f, 1.00f);    // Dark red background
    colors[ImGuiCol_Border] = ImVec4(0.25f, 0.15f, 0.15f, 0.50f);     // Border color (dark red)
    colors[ImGuiCol_Button] = ImVec4(0.85f, 0.15f, 0.15f, 1.00f);     // Bright red button
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.95f, 0.25f, 0.25f, 1.00f); // Hovered button (lighter red)
    colors[ImGuiCol_ButtonActive] = ImVec4(0.75f, 0.05f, 0.05f, 1.00f); // Active button (darker red)
    colors[ImGuiCol_Separator] = ImVec4(0.30f, 0.10f, 0.10f, 1.00f);   // Separator color (dark red)
}

void SetGreenForestTheme()
{
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    // Green Forest theme colors
    colors[ImGuiCol_Text] = ImVec4(0.90f, 1.00f, 0.90f, 1.00f);     // Light green text
    colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f); // Disabled text
    colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.20f, 0.10f, 1.00f);    // Forest green background
    colors[ImGuiCol_Border] = ImVec4(0.15f, 0.30f, 0.15f, 0.50f);     // Dark green border
    colors[ImGuiCol_Button] = ImVec4(0.20f, 0.60f, 0.20f, 1.00f);     // Bright green button
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.30f, 0.70f, 0.30f, 1.00f); // Hovered button (lighter green)
    colors[ImGuiCol_ButtonActive] = ImVec4(0.10f, 0.50f, 0.10f, 1.00f); // Active button (darker green)
    colors[ImGuiCol_Separator] = ImVec4(0.15f, 0.30f, 0.15f, 1.00f);   // Separator color (forest green)
}


void SetCinderTheme()
{
    ImGuiStyle& style = ImGui::GetStyle();

    style.WindowMinSize = ImVec2(160, 20);
    style.FramePadding = ImVec2(4, 2);
    style.ItemSpacing = ImVec2(6, 2);
    style.ItemInnerSpacing = ImVec2(6, 4);
    style.Alpha = 0.95f;
    style.WindowRounding = 4.0f;
    style.FrameRounding = 2.0f;
    style.IndentSpacing = 6.0f;
    style.ItemInnerSpacing = ImVec2(2, 4);
    style.ColumnsMinSpacing = 50.0f;
    style.GrabMinSize = 14.0f;
    style.GrabRounding = 16.0f;
    style.ScrollbarSize = 12.0f;
    style.ScrollbarRounding = 16.0f;

    style.Colors[ImGuiCol_Text] = ImVec4(0.86f, 0.93f, 0.89f, 0.78f);
    style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.86f, 0.93f, 0.89f, 0.28f);
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.13f, 0.14f, 0.17f, 1.00f);
    style.Colors[ImGuiCol_Border] = ImVec4(0.31f, 0.31f, 1.00f, 0.00f);
    style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style.Colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.78f);
    style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
    style.Colors[ImGuiCol_TitleBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
    style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.20f, 0.22f, 0.27f, 0.75f);
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
    style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.20f, 0.22f, 0.27f, 0.47f);
    style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.09f, 0.15f, 0.16f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.78f);
    style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
    style.Colors[ImGuiCol_CheckMark] = ImVec4(0.71f, 0.22f, 0.27f, 1.00f);
    style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.47f, 0.77f, 0.83f, 0.14f);
    style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
    style.Colors[ImGuiCol_Button] = ImVec4(0.47f, 0.77f, 0.83f, 0.14f);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.86f);
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
    style.Colors[ImGuiCol_Header] = ImVec4(0.92f, 0.18f, 0.29f, 0.76f);
    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.86f);
    style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
    style.Colors[ImGuiCol_Separator] = ImVec4(0.14f, 0.16f, 0.19f, 1.00f);
    style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.78f);
    style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
    style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.47f, 0.77f, 0.83f, 0.04f);
    style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.78f);
    style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
    style.Colors[ImGuiCol_PlotLines] = ImVec4(0.86f, 0.93f, 0.89f, 0.63f);
    style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
    style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.86f, 0.93f, 0.89f, 0.63f);
    style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
    style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.92f, 0.18f, 0.29f, 0.43f);
    style.Colors[ImGuiCol_PopupBg] = ImVec4(0.20f, 0.22f, 0.27f, 0.9f);
    style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.20f, 0.22f, 0.27f, 0.73f);
}


void SetDarkCrimsonTheme()
{
    ImGuiStyle& style = ImGui::GetStyle();

    style.WindowMinSize = ImVec2(160, 20);
    style.FramePadding = ImVec2(4, 2);
    style.ItemSpacing = ImVec2(6, 2);
    style.ItemInnerSpacing = ImVec2(6, 4);
    style.Alpha = 0.95f;
    style.WindowRounding = 4.0f;
    style.FrameRounding = 2.0f;
    style.IndentSpacing = 6.0f;
    style.ItemInnerSpacing = ImVec2(2, 4);
    style.ColumnsMinSpacing = 50.0f;
    style.GrabMinSize = 14.0f;
    style.GrabRounding = 16.0f;
    style.ScrollbarSize = 12.0f;
    style.ScrollbarRounding = 16.0f;

    style.Colors[ImGuiCol_Text] = ImVec4(0.92f, 0.93f, 0.91f, 1.00f);
    style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.92f, 0.93f, 0.91f, 0.40f);
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.12f, 0.12f, 0.14f, 1.00f);
    style.Colors[ImGuiCol_Border] = ImVec4(0.38f, 0.30f, 0.47f, 0.00f);
    style.Colors[ImGuiCol_FrameBg] = ImVec4(0.17f, 0.20f, 0.25f, 1.00f);
    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.86f, 0.18f, 0.30f, 0.80f);
    style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.86f, 0.18f, 0.30f, 1.00f);
    style.Colors[ImGuiCol_TitleBg] = ImVec4(0.17f, 0.20f, 0.25f, 1.00f);
    style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.17f, 0.20f, 0.25f, 0.75f);
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.86f, 0.18f, 0.30f, 1.00f);
    style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.17f, 0.20f, 0.25f, 0.47f);
    style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.17f, 0.20f, 0.25f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.11f, 0.13f, 0.18f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.86f, 0.18f, 0.30f, 0.78f);
    style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.86f, 0.18f, 0.30f, 1.00f);
    style.Colors[ImGuiCol_CheckMark] = ImVec4(0.82f, 0.25f, 0.30f, 1.00f);
    style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.47f, 0.72f, 0.78f, 0.14f);
    style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.86f, 0.18f, 0.30f, 1.00f);
    style.Colors[ImGuiCol_Button] = ImVec4(0.47f, 0.72f, 0.78f, 0.14f);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.86f, 0.18f, 0.30f, 0.86f);
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.86f, 0.18f, 0.30f, 1.00f);
    style.Colors[ImGuiCol_Header] = ImVec4(0.86f, 0.18f, 0.30f, 0.75f);
    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.86f, 0.18f, 0.30f, 0.86f);
    style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.86f, 0.18f, 0.30f, 1.00f);
    style.Colors[ImGuiCol_Separator] = ImVec4(0.12f, 0.14f, 0.18f, 1.00f);
    style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.86f, 0.18f, 0.30f, 0.78f);
    style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.86f, 0.18f, 0.30f, 1.00f);
    style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.47f, 0.72f, 0.78f, 0.04f);
    style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.86f, 0.18f, 0.30f, 0.78f);
    style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.86f, 0.18f, 0.30f, 1.00f);
    style.Colors[ImGuiCol_PlotLines] = ImVec4(0.92f, 0.93f, 0.91f, 0.60f);
    style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.86f, 0.18f, 0.30f, 1.00f);
    style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.92f, 0.93f, 0.91f, 0.60f);
    style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.86f, 0.18f, 0.30f, 1.00f);
    style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.86f, 0.18f, 0.30f, 0.43f);
    style.Colors[ImGuiCol_PopupBg] = ImVec4(0.17f, 0.20f, 0.25f, 0.9f);
    style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.17f, 0.20f, 0.25f, 0.73f);
}

void SetNeonGlowTheme()
{
    ImGuiStyle& style = ImGui::GetStyle();

    style.WindowMinSize = ImVec2(160, 20);
    style.FramePadding = ImVec2(4, 2);
    style.ItemSpacing = ImVec2(6, 2);
    style.ItemInnerSpacing = ImVec2(6, 4);
    style.Alpha = 0.95f;
    style.WindowRounding = 4.0f;
    style.FrameRounding = 2.0f;
    style.IndentSpacing = 6.0f;
    style.ItemInnerSpacing = ImVec2(2, 4);
    style.ColumnsMinSpacing = 50.0f;
    style.GrabMinSize = 14.0f;
    style.GrabRounding = 16.0f;
    style.ScrollbarSize = 12.0f;
    style.ScrollbarRounding = 16.0f;

    style.Colors[ImGuiCol_Text] = ImVec4(0.93f, 0.96f, 0.99f, 0.85f);
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.08f, 0.08f, 0.12f, 1.00f);
    style.Colors[ImGuiCol_Border] = ImVec4(0.65f, 0.85f, 1.00f, 0.15f);
    style.Colors[ImGuiCol_FrameBg] = ImVec4(0.12f, 0.14f, 0.18f, 1.00f);
    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.29f, 0.56f, 1.00f, 0.75f);
    style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.29f, 0.56f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_TitleBg] = ImVec4(0.12f, 0.14f, 0.18f, 1.00f);
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.29f, 0.56f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_Button] = ImVec4(0.0f, 0.88f, 1.0f, 0.80f);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.29f, 0.56f, 1.00f, 0.95f);
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.0f, 0.78f, 1.0f, 1.00f);
    style.Colors[ImGuiCol_Header] = ImVec4(0.29f, 0.56f, 1.00f, 0.75f);
    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.29f, 0.56f, 1.00f, 0.85f);
    style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.29f, 0.56f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.12f, 0.14f, 0.18f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.29f, 0.56f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.29f, 0.56f, 1.00f, 0.75f);
    style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.29f, 0.56f, 1.00f, 1.00f);
}

void SetDarkRedVelvetTheme()
{
    ImGuiStyle& style = ImGui::GetStyle();

    style.WindowMinSize = ImVec2(160, 20);
    style.FramePadding = ImVec2(4, 2);
    style.ItemSpacing = ImVec2(6, 2);
    style.ItemInnerSpacing = ImVec2(6, 4);
    style.Alpha = 0.95f;
    style.WindowRounding = 4.0f;
    style.FrameRounding = 2.0f;
    style.IndentSpacing = 6.0f;
    style.ItemInnerSpacing = ImVec2(2, 4);
    style.ColumnsMinSpacing = 50.0f;
    style.GrabMinSize = 14.0f;
    style.GrabRounding = 16.0f;
    style.ScrollbarSize = 12.0f;
    style.ScrollbarRounding = 16.0f;

    style.Colors[ImGuiCol_Text] = ImVec4(0.91f, 0.60f, 0.60f, 0.90f);
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.08f, 0.08f, 0.1f, 1.00f);
    style.Colors[ImGuiCol_Border] = ImVec4(0.85f, 0.22f, 0.30f, 0.00f);
    style.Colors[ImGuiCol_FrameBg] = ImVec4(0.13f, 0.13f, 0.16f, 1.00f);
    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.85f, 0.22f, 0.30f, 0.70f);
    style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.85f, 0.22f, 0.30f, 1.00f);
    style.Colors[ImGuiCol_TitleBg] = ImVec4(0.13f, 0.13f, 0.16f, 1.00f);
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.85f, 0.22f, 0.30f, 1.00f);
    style.Colors[ImGuiCol_Button] = ImVec4(0.85f, 0.22f, 0.30f, 0.60f);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.80f);
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
    style.Colors[ImGuiCol_Header] = ImVec4(0.92f, 0.18f, 0.29f, 0.60f);
    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.80f);
    style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.13f, 0.13f, 0.16f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.85f, 0.22f, 0.30f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.70f);
    style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
}


void SetOceanBreezeTheme()
{
    ImGuiStyle& style = ImGui::GetStyle();

    style.WindowMinSize = ImVec2(160, 20);
    style.FramePadding = ImVec2(4, 2);
    style.ItemSpacing = ImVec2(6, 2);
    style.ItemInnerSpacing = ImVec2(6, 4);
    style.Alpha = 0.95f;
    style.WindowRounding = 4.0f;
    style.FrameRounding = 2.0f;
    style.IndentSpacing = 6.0f;
    style.ItemInnerSpacing = ImVec2(2, 4);
    style.ColumnsMinSpacing = 50.0f;
    style.GrabMinSize = 14.0f;
    style.GrabRounding = 16.0f;
    style.ScrollbarSize = 12.0f;
    style.ScrollbarRounding = 16.0f;

    style.Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.94f, 0.98f, 0.85f);
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.13f, 0.19f, 0.24f, 1.00f);
    style.Colors[ImGuiCol_Border] = ImVec4(0.30f, 0.50f, 0.75f, 0.00f);
    style.Colors[ImGuiCol_FrameBg] = ImVec4(0.18f, 0.24f, 0.30f, 1.00f);
    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.23f, 0.56f, 0.86f, 0.70f);
    style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.23f, 0.56f, 0.86f, 1.00f);
    style.Colors[ImGuiCol_TitleBg] = ImVec4(0.18f, 0.24f, 0.30f, 1.00f);
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.23f, 0.56f, 0.86f, 1.00f);
    style.Colors[ImGuiCol_Button] = ImVec4(0.23f, 0.56f, 0.86f, 0.60f);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.23f, 0.56f, 0.86f, 0.85f);
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.23f, 0.56f, 0.86f, 1.00f);
    style.Colors[ImGuiCol_Header] = ImVec4(0.23f, 0.56f, 0.86f, 0.60f);
    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.23f, 0.56f, 0.86f, 0.85f);
    style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.23f, 0.56f, 0.86f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.18f, 0.24f, 0.30f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.23f, 0.56f, 0.86f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.23f, 0.56f, 0.86f, 0.70f);
    style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.23f, 0.56f, 0.86f, 1.00f);

}