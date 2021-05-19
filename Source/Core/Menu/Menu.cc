#include "Menu.hh"

void CMenu::SetupFrontend() {

	if (!this->bSetuped) {

		this->CreateStyles(&ImGui::GetStyle());
		this->CreateColors(&ImGui::GetStyle());
		this->CreateFonts(ImGui::GetIO());

		this->bSetuped = true;
	}
}

void CMenu::Render() {

	GetWindowRect(GetDesktopWindow(), &ScreenSize);
	this->Screen.Size[ESize::Width] = (ScreenSize.right - this->Menu.Size[ESize::Width]) / 2.0f;
	this->Screen.Size[ESize::Height] = (ScreenSize.bottom - this->Menu.Size[ESize::Height]) / 2.0f;

	ImGui::SetNextWindowPos(ImVec2{ Screen.Size[ESize::Width], Screen.Size[ESize::Height] }, ImGuiCond_Once, ImVec2{ 0.0f, 0.0f });
	ImGui::SetNextWindowSize(ImVec2{ Menu.Size[ESize::Width], Menu.Size[ESize::Height] }, ImGuiCond_::ImGuiCond_Always);

	ImGui::Begin(LoaderName, &bVisible, WindowFlags); {

	}
	ImGui::End();
}

void CMenu::CreateStyles(ImGuiStyle* Style) {

	Style->WindowPadding = ImVec2{ 0.0f, 0.0f };
	Style->FramePadding = ImVec2{ 0.0f, 0.0f };
	Style->CellPadding = ImVec2{ 0.0f, 0.0f };
	Style->ItemSpacing = ImVec2{ 5.0f, 5.0f };
	Style->ItemInnerSpacing = ImVec2{ 5.0f, 5.0f };
	Style->TouchExtraPadding = ImVec2{ 0.0f, 0.0f };
	Style->IndentSpacing = 5.0f;
	Style->ScrollbarSize = 5.0f;
	Style->GrabMinSize = 5.0f;

	Style->WindowBorderSize = 0.0f;
	Style->ChildBorderSize = 0.0f;
	Style->PopupBorderSize = 0.0f;
	Style->FrameBorderSize = 0.0f;
	Style->TabBorderSize = 0.0f;

	Style->WindowRounding = 0.0f;
	Style->ChildRounding = 0.0f;
	Style->FrameRounding = 0.0f;
	Style->PopupRounding = 0.0f;
	Style->ScrollbarRounding = 10.0f;
	Style->GrabRounding = 0.0f;
	Style->LogSliderDeadzone = 0.0f;
	Style->TabRounding = 0.0f;

	Style->WindowTitleAlign = ImVec2{ 0.5f, 0.5f };
	Style->WindowMenuButtonPosition = ImGuiDir_None;
	Style->ColorButtonPosition = ImGuiDir_Right;
	Style->ButtonTextAlign = ImVec2{ 0.5f, 0.5f };
	Style->SelectableTextAlign = ImVec2{ 0.5f, 0.5f };

	Style->DisplaySafeAreaPadding = ImVec2{ 0.0f, 0.0f };
	Style->DisplayWindowPadding = ImVec2{ Menu.Size[ESize::Width], Menu.Size[ESize::Height] };

	Style->MouseCursorScale = 1.0f;

	Style->AntiAliasedLines = true;
	Style->AntiAliasedLinesUseTex = true;
	Style->AntiAliasedFill = true;

	Style = &ImGui::GetStyle();
}

void CMenu::CreateColors(ImGuiStyle* Style) {

	Style->Colors[ImGuiCol_Text] = ImColor(255, 255, 255, 255);
	Style->Colors[ImGuiCol_TextDisabled] = ImColor(100, 100, 100, 255);
	Style->Colors[ImGuiCol_WindowBg] = ImColor(40, 40, 40, 255);
	//Style->Colors[ImGuiCol_ChildBg] = ImColor(45, 45, 45, 200);

	Style = &ImGui::GetStyle();
}

void CMenu::CreateFonts(ImGuiIO& IO, UINT uiFontFlags) {

	static const ImWchar StaticRanges[] = { 0x0020, 0x00FF, 0x2000, 0x206F, 0x3000, 0x30FF, 0x31F0, 0x31FF, 0xFF00, 0xFFEF, 0x4e00, 0x9FAF, 0x0400, 0x052F, 0x2DE0, 0x2DFF, 0xA640, 0xA69F, 0 };

	ImFontConfig ImArialConfig;
	ImArialConfig.FontDataOwnedByAtlas = true;
	ImArialConfig.MergeMode = false;
	ImArialConfig.RasterizerMultiply = 1.2f;
	ImArialConfig.FontBuilderFlags = ImGuiFreeTypeBuilderFlags::ImGuiFreeTypeBuilderFlags_LightHinting;
	IO.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Arial.ttf", 14.0f, &ImArialConfig, StaticRanges);

	ImGuiFreeType::BuildFontAtlas(IO.Fonts, uiFontFlags);
}