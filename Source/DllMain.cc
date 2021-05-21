#include "DllMain.hh"
#include "Core/Menu/Menu.hh"

BOOL APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int iShowCmd) {

    WNDCLASSEX WNDClassEx = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0, 0, GetModuleHandle(NULL), NULL, LoadCursor(NULL, IDC_ARROW), NULL, NULL, CMenu::Get().LoaderName.c_str(), NULL };
    RegisterClassEx(&WNDClassEx);

    CMenu::Get().LoaderHWND = CreateWindowEx(WS_EX_LAYERED, WNDClassEx.lpszClassName, CMenu::Get().LoaderName.c_str(), WS_POPUP, 0, 0, 1, 1, NULL, NULL, WNDClassEx.hInstance, NULL);
    
    /* Initialize Direct3D */
    if (!CreateDevice(CMenu::Get().LoaderHWND)) {

        CleanupDevice();
        UnregisterClass(WNDClassEx.lpszClassName, WNDClassEx.hInstance);

        return TRUE;
    }

    /* Show the window */
    ShowWindow(CMenu::Get().LoaderHWND, SW_HIDE);
    UpdateWindow(CMenu::Get().LoaderHWND);

    /* Setup ImGui context */
    ImGui::CreateContext();

    ImGui::GetIO().IniFilename = NULL;
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_::ImGuiConfigFlags_NavEnableKeyboard;
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_::ImGuiConfigFlags_ViewportsEnable;

    /* Create Fonts/Colors */
    CMenu::Get().SetupFrontend();

    ImGui_ImplWin32_Init(CMenu::Get().LoaderHWND);
    ImGui_ImplDX9_Init(g_LpDirect3DDevice);

    while (CMenu::Get().bVisible) {
        ZeroMemory(&g_Message, sizeof(g_Message));

        while (PeekMessage(&g_Message, NULL, 0U, 0U, PM_REMOVE)) {

            TranslateMessage(&g_Message);
            DispatchMessage(&g_Message);

            if (g_Message.message == WM_QUIT) {

                CMenu::Get().bVisible = false;
            }
        }

        if (!CMenu::Get().bVisible) {

            break;
        }

        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        CMenu::Get().Render();

        ImGui::EndFrame();

        g_LpDirect3DDevice->Clear(0UL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, NULL, 1.0f, 0UL);

        if (g_LpDirect3DDevice->BeginScene() >= 0) {

            ImGui::Render();
            ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
            g_LpDirect3DDevice->EndScene();
        }

        if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_::ImGuiConfigFlags_ViewportsEnable) {

            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }

        HRESULT HResult = g_LpDirect3DDevice->Present(NULL, NULL, NULL, NULL);

        if (HResult == D3DERR_DEVICELOST && g_LpDirect3DDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET) {

            ResetDevice();
        }
    }

    /* Cleanup */
    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDevice();
    DestroyWindow(CMenu::Get().LoaderHWND);
    UnregisterClass(WNDClassEx.lpszClassName, WNDClassEx.hInstance);

    return FALSE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam) {

    if (ImGui_ImplWin32_WndProcHandler(hWnd, uiMsg, wParam, lParam)) {

        return 1LL;
    }

    switch (uiMsg) {
        case WM_DESTROY: {
            PostQuitMessage(WM_QUIT);
            return 0LL;
        } break;

        case WM_SIZE: {
            if (g_LpDirect3DDevice != NULL && wParam != SIZE_MINIMIZED) {

                g_D3DPresentParameters.BackBufferWidth = LOWORD(lParam);
                g_D3DPresentParameters.BackBufferHeight = HIWORD(lParam);

                ResetDevice();
            }
            return 0LL;
        } break;

        case WM_SYSCOMMAND: {
            /* Disable ALT application menu */
            if ((wParam & 0xfff0) == SC_KEYMENU) {

                return 0LL;
            }
        } break;
    }

    return DefWindowProc(hWnd, uiMsg, wParam, lParam);
}