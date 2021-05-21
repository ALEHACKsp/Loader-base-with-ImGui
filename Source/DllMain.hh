#pragma once

#ifndef DllMain_hh
#define DllMain_hh

#include "Includes.hh"

LPDIRECT3D9             g_LpDirect3D9 = NULL;
LPDIRECT3DDEVICE9       g_LpDirect3DDevice = NULL;
D3DPRESENT_PARAMETERS   g_D3DPresentParameters = {};
MSG                     g_Message = {};

bool CreateDevice(HWND hWnd) {

    if ((g_LpDirect3D9 = IFH_64(Direct3DCreate9)(D3D_SDK_VERSION)) == NULL) {
        return false;
    }

    LI_FN(memset)(&g_D3DPresentParameters, NULL, sizeof(g_D3DPresentParameters));
    g_D3DPresentParameters.BackBufferWidth = 0U;
    g_D3DPresentParameters.BackBufferHeight = 0U;
    g_D3DPresentParameters.BackBufferFormat = _D3DFORMAT::D3DFMT_UNKNOWN;
    g_D3DPresentParameters.BackBufferCount = 2U;
    g_D3DPresentParameters.MultiSampleType = _D3DMULTISAMPLE_TYPE::D3DMULTISAMPLE_NONMASKABLE;
    g_D3DPresentParameters.MultiSampleQuality = 1UL;
    g_D3DPresentParameters.SwapEffect = _D3DSWAPEFFECT::D3DSWAPEFFECT_DISCARD;
    g_D3DPresentParameters.hDeviceWindow = hWnd;
    g_D3DPresentParameters.Windowed = TRUE;
    g_D3DPresentParameters.EnableAutoDepthStencil = TRUE;
    g_D3DPresentParameters.AutoDepthStencilFormat = _D3DFORMAT::D3DFMT_D16;
    g_D3DPresentParameters.Flags = D3DPRESENTFLAG_DEVICECLIP;
    g_D3DPresentParameters.FullScreen_RefreshRateInHz = 0U;
    g_D3DPresentParameters.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

    if (g_LpDirect3D9->CreateDevice(D3DADAPTER_DEFAULT, _D3DDEVTYPE::D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING,
        &g_D3DPresentParameters, &g_LpDirect3DDevice) < 0L) {

        return false;
    }

    return true;
}

void CleanupDevice() {

    if (g_LpDirect3DDevice) {

        g_LpDirect3DDevice->Release();
        g_LpDirect3DDevice = NULL;
    }

    if (g_LpDirect3D9) {

        g_LpDirect3D9->Release();
        g_LpDirect3D9 = NULL;
    }
}

void ResetDevice() {

    IFH_64(ImGui_ImplDX9_InvalidateDeviceObjects)();
    HRESULT HResult = g_LpDirect3DDevice->Reset(&g_D3DPresentParameters);

    if (HResult == D3DERR_INVALIDCALL) {

        assert(NULL);
    }

    IFH_64(ImGui_ImplDX9_CreateDeviceObjects)();
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam);
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam);

#endif // !DllMain_hh