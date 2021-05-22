#include "CustomImGui.hh"

/* Render this your custom ImGui widgets */

void CustomImGui::TextWithFont(ImDrawList* DrawList, ImFont* Font, std::string sText, const ImVec2& Size, ImColor Color) {

	ImGui::PushFont(Font); {
		DrawList->AddText(ImVec2{ Size.x, Size.y }, Color, sText.c_str(), NULL);
	} ImGui::PopFont();
}