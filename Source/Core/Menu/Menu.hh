#pragma once

#ifndef Menu_hh
#define Menu_hh

#include "../../Includes.hh"
#include "CustomImGui/CustomImGui.hh"

enum ESize : int {

	Width = 0,
	Height = 1,

	Count = 2
};

class CMenu : public CSingleton<CMenu> {
public:
	struct Screen_t {

		float Size[ESize::Count] = {};
	} Screen;

	struct Menu_t {

		float Size[ESize::Count] = { 400.0f, 350.0f };
	} Menu;

	void SetupBackend();
	void Render();

	bool bVisible = true;
	HWND LoaderHWND = nullptr;
	std::string LoaderName = XorStr("ImGui Loader");

private:
	struct ImFont_t {

		ImFont* Default;
		ImFontConfig ImDefaultConfig;

		ImFont* Second;
		ImFontConfig ImSecondConfig;
	} ImFont;

	void CreateStyles(ImGuiStyle* Style);
	void CreateColors(ImGuiStyle* Style);
	void CreateFonts(ImGuiIO& IO, UINT uiFontFlags = 0U);

	RECT ScreenSize = {};
	bool bSetuped = false;
	const ImGuiWindowFlags WindowFlags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoBringToFrontOnFocus;
};

#endif // !Menu_hh