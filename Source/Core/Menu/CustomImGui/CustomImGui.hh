#pragma once

#ifndef CustomImGui_hh
#define CustomImGui_hh

#include "../../../Includes.hh"
#include "../Menu.hh"

namespace CustomImGui {

	void TextWithFont(ImFont* Font, std::string sText = XorStr("Text"), ImColor Color = ImColor(255, 255, 255, 255));
	void TextWithFont(ImDrawList* DrawList, ImFont* Font, std::string sText = XorStr("Text"), const ImVec2& SizeArgument = ImVec2{ 0.0f, 0.0f }, ImColor Color = ImColor(255, 255, 255, 255));

	void CircleImageFilled(ImTextureID TextureId, const ImVec2& CentrePos = ImVec2{ 0.0f, 0.0f }, float fRadius = 1.0f, ImColor Color = ImColor(255, 255, 255, 255), int iNumSegments = 1);

	void ProgressBar(float fFraction, const ImVec2& SizeArgument = ImVec2{ 0.0f, 0.0f }, std::string sOverlay = NULL);
}

#endif // !CustomImGui_hh