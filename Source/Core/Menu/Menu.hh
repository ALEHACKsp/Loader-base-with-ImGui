#pragma once

#ifndef Menu_hh
#define Menu_hh

#include "../../Includes.hh"

enum ESize : int {

	Width = 0,
	Height,

	Count
};

class CMenu : public CSingleton<CMenu> {
public:
	struct Screen_t {
		float Size[ESize::Count] = {};
	} Screen;

	struct Menu_t {
		float Size[ESize::Count] = { 500.0f, 400.0f };
	} Menu;

	void SetupFrontend();
	void Render();

	bool bVisible = true;
	const char* LoaderName = "UnknownLoader";

private:
	void CreateStyles(ImGuiStyle* Style);
	void CreateColors(ImGuiStyle* Style);
	void CreateFonts(ImGuiIO& IO, UINT uiFontFlags = 0U);

	bool bSetuped = false;
	RECT ScreenSize = {};
	const ImGuiWindowFlags WindowFlags = /*ImGuiWindowFlags_NoTitleBar |*/ ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoBringToFrontOnFocus;
};

#endif // !Menu_hh