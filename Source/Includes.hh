#pragma once

#ifndef Includes_hh
#define Includes_hh

#include <Windows.h>

#include <D3d9.h>
#pragma comment(lib, "D3d9.lib")

/* ImGui */
#include "Resources/ImGui/ImGui.hh"
#include "Resources/ImGui/FreeType.hh"
#pragma comment(lib, "FreeType.lib")

/* Fix operators for ImGui */
#define IMGUI_ENABLE_FREETYPE
#define IMGUI_DEFINE_MATH_OPERATORS

/* ImGui Implementation */
#include "Resources/ImGui/Internal.hh"
#include "Resources/ImGui/Others/DX9/Impl_DX9.hh"
#include "Resources/ImGui/Others/Win32/Impl_Win32.hh"
#include "Resources/ImGui/Others/StdLib/StdLib.hh"

/* Utilities */
#include "Utilities/Singleton.hh"

#endif // !Includes_hh