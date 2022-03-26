#pragma once

#include "header_defination.h"

extern struct scene_ops scene_ops_info;


/*
Main Window
class handles
information about
every thing required by
the main window
*/
class MainWindow
{
public:
    struct window_info *wininfo_struct;

    MainWindow()
    {
        wininfo_struct = new window_info;
        createScene(&scene_ops_info, wininfo_struct);
    }

    ~MainWindow()
    {
      delete wininfo_struct;
    }


    PCWSTR  ClassName() const { return L"Circle Window Class"; }

    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
    BOOL Create(PCWSTR lpWindowName, DWORD dwStyle, DWORD dwExStyle = 0,
        int x = CW_USEDEFAULT,
        int y = CW_USEDEFAULT,
        int nWidth = CW_USEDEFAULT,
        int nHeight = CW_USEDEFAULT,
        HWND hWndParent = 0,
        HMENU hMenu = 0
    );

};


/*
Handles Windows
message
and other windows
message are handle with
DefWindowProc
*/
LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CLOSE:
    {
        // Create the message box. If the user clicks 
        // the Yes button, destroy the main window. 
        if (MessageBoxA(NULL, "Ready to exit the program", "Exit Window", MB_ICONQUESTION | MB_YESNO) == IDYES)
            DestroyWindow(wininfo_struct->hwnd);
        else
            return 0;
    }
    case WM_DESTROY:
        scene_ops_info.freeScene(&scene_ops_info);
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
        scene_ops_info.OnPaint(&scene_ops_info);
        return 0;

    // change scene on pressing 
    // space key
    case WM_CHAR:
        scene_ops_info.OnKeyCharPress(&scene_ops_info, wParam, lParam);
        return 0;

    case WM_COMMAND:
        scene_ops_info.CmdHandler(&scene_ops_info, wParam, lParam);
        return 0;
    }
    return scene_ops_info.handleDefaultProc(&scene_ops_info, uMsg, wParam, lParam);
}





/*
Creates a main window
with a given parameter
and adds a handler
for current process to
access bitmaps and other resources
of mainwindow
*/
BOOL MainWindow::Create(
    PCWSTR lpWindowName,
    DWORD dwStyle,
    DWORD dwExStyle,
    int x,
    int y,
    int nWidth,
    int nHeight,
    HWND hWndParent,
    HMENU hMenu
)
{

    // Register window class
    WNDCLASS wc = {};

    // get main instance
    wininfo_struct->hInstance = GetModuleHandle(NULL);

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = wininfo_struct->hInstance;
    wc.lpszClassName = ClassName();

    RegisterClass(&wc);

    wininfo_struct->hwnd = CreateWindowEx(
        dwExStyle, ClassName(), lpWindowName, dwStyle, x, y,
        nWidth, nHeight, hWndParent, hMenu, wininfo_struct->hInstance, this
    );

    return (wininfo_struct->hwnd ? TRUE : FALSE);
}
