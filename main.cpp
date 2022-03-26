#ifndef UNICODE
#define UNICODE
#endif

#include "header_defination.h"


struct scene_ops scene_ops_info;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int nCmdShow)
{
    MainWindow win;
    const wchar_t WINDOW_NAME[] = L"MyWindow";

    // Create Main window
    if (!win.Create(WINDOW_NAME, WS_OVERLAPPEDWINDOW | WS_VSCROLL)) // WS_HSCROLL
    {
        return FALSE;
    }
    
    // Window is visible to the user
    ShowWindow(win.wininfo_struct->hwnd, SW_SHOWDEFAULT);


    // Set WS_EX_LAYERED on this window 
    SetWindowLong(win.wininfo_struct->hwnd, GWL_EXSTYLE,
        GetWindowLong(win.wininfo_struct->hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);

    // Make this window 70% alpha
    SetLayeredWindowAttributes(win.wininfo_struct->hwnd, 0, 240, LWA_ALPHA);


    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}



/*
  WindowProc function that
  will handle all message for
  current window and other events
  are been handle by default window
  proc method
  */
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    MainWindow* pThis = NULL;
    if (uMsg == WM_NCCREATE)
    {

        CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
        pThis = (MainWindow*)pCreate->lpCreateParams;
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);

        pThis->wininfo_struct->hwnd = hwnd;
    }
    else
    {
        pThis = (MainWindow*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
    }
    if (pThis)
    {
        return pThis->HandleMessage(uMsg, wParam, lParam);
    }
    else
    {
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}
