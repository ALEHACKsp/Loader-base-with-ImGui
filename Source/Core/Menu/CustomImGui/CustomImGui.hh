#pragma once

#ifndef CustomImGui_hh
#define CustomImGui_hh

#include "../../../Includes.hh"
#include "../Menu.hh"

namespace CustomImGui {

	void TextWithFont(ImDrawList* DrawList, ImFont* Font, std::string sText = XorStr("Text"), const ImVec2& Size = ImVec2{ 0.0f, 0.0f }, ImColor Color = ImColor(255, 255, 255, 255));
}

#endif // !CustomImGui_hh