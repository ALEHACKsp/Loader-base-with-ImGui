#include "CustomImGui.hh"

/* Render this your custom ImGui widgets */

void CustomImGui::TextWithFont(ImFont* Font, std::string sText, ImColor Color) {

	ImGui::PushFont(Font); {

		ImGui::TextColored(Color, sText.c_str());
	} ImGui::PopFont();
}

void CustomImGui::TextWithFont(ImDrawList* DrawList, ImFont* Font, std::string sText, const ImVec2& SizeArgument, ImColor Color) {

	ImGui::PushFont(Font); {

		DrawList->AddText(ImVec2{ SizeArgument.x, SizeArgument.y }, Color, sText.c_str(), NULL);
	} ImGui::PopFont();
}

void CustomImGui::CircleImageFilled(ImTextureID TextureId, const ImVec2& CentrePos, float fRadius, ImColor Color, int iNumSegments) {

	ImGuiWindow* Window = ImGui::GetCurrentWindow();

	if (Window->SkipItems) {
		return;
	}

	Window->DrawList->PathClear();

	if ((Color & IM_COL32_A_MASK) == 0 || iNumSegments <= 2) {
		return;
	}

	const bool PushTextureId = Window->DrawList->_TextureIdStack.empty() || TextureId != Window->DrawList->_TextureIdStack.back();

	if (PushTextureId) {

		Window->DrawList->PushTextureID(TextureId);
	}

	int VertsStartBufferSize = Window->DrawList->VtxBuffer.Size;
	const float ArcMax = IM_PI * 2.0f * (static_cast<float>(iNumSegments) - 1.0f) / static_cast<float>(iNumSegments);
	Window->DrawList->PathArcTo(CentrePos, fRadius, 0.0f, ArcMax, iNumSegments - 1);
	Window->DrawList->PathFillConvex(Color);
	int VertsEndBufferSize = Window->DrawList->VtxBuffer.Size;

	ImGui::ShadeVertsLinearUV(Window->DrawList, VertsStartBufferSize, VertsEndBufferSize,
		ImVec2{ CentrePos.x - fRadius, CentrePos.y - fRadius }, ImVec2{ CentrePos.x + fRadius,CentrePos.y + fRadius },
		ImVec2{ 0.0f, 0.0f }, ImVec2{ 1.0f, 1.0f }, true);

	if (PushTextureId) {

		Window->DrawList->PopTextureID();
	}
}

void CustomImGui::ProgressBar(float fFraction, const ImVec2& SizeArgument, std::string sOverlay) {

	ImGuiWindow* Window = ImGui::GetCurrentWindow();

	if (Window->SkipItems) {
		return;
	}

	ImGuiContext& Context = *GImGui;
	const ImGuiStyle& Style = Context.Style;

	ImVec2 Position = Window->DC.CursorPos;
	ImVec2 Size = ImGui::CalcItemSize(SizeArgument, ImGui::CalcItemWidth(), Context.FontSize +
		Style.FramePadding.y * 2.0f);

	ImRect bb(Position, Position + Size);

	ImGui::ItemSize(Size, Style.FramePadding.y);
	if (!ImGui::ItemAdd(bb, NULL, NULL, ImGuiItemAddFlags_::ImGuiItemAddFlags_None)) {
		return;
	}

	// Render
	fFraction = ImSaturate(fFraction);
	ImGui::RenderFrame(bb.Min, bb.Max, ImGui::GetColorU32(ImGuiCol_FrameBg), true, Style.FrameRounding);
	bb.Expand(ImVec2{ -Style.FrameBorderSize, -Style.FrameBorderSize });
	const ImVec2 FillBr = ImVec2(ImLerp(bb.Min.x, bb.Max.x, fFraction), bb.Max.y);
	ImGui::RenderRectFilledRangeH(Window->DrawList, bb, ImGui::GetColorU32(ImGuiCol_PlotHistogram), 0.0f,
		fFraction, Style.FrameRounding);

	// Default displaying the fraction as percentage string, but user can override it
	char OverlayBuffer[64];

	if (!sOverlay.c_str()) {

		ImFormatString(OverlayBuffer, IM_ARRAYSIZE(OverlayBuffer), "%.0f%%", fFraction * 100.0f + 0.01f);
		sOverlay = OverlayBuffer;
	}

	ImVec2 OverlaySize = ImGui::CalcTextSize(sOverlay.c_str(), NULL, false, -1.0f);

	if (OverlaySize.x > 0.0f) {

		ImGui::RenderTextClipped(ImVec2{ ImClamp(FillBr.x + Style.ItemSpacing.x, bb.Min.x, bb.Max.x - OverlaySize.x -
			Style.ItemInnerSpacing.x), bb.Min.y }, bb.Max, sOverlay.c_str(), NULL, &OverlaySize, ImVec2(0.0f, 0.5f),&bb);
	}
}