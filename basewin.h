#pragma once
#ifndef _BASEWIN_H
#define _BASEWIN_H

template <class DERIVED_TYPE>
class BaseWindow
{
public:
  
    BaseWindow() : m_hwnd(NULL) { }

    /*
    Creates a main window
    with a given parameter 
    and adds a handler 
    for current process to
    access bitmaps and other resources
    of mainwindow
    */
    BOOL Create(
        PCWSTR lpWindowName,
        DWORD dwStyle,
        DWORD dwExStyle = 0,
        int x = CW_USEDEFAULT,
        int y = CW_USEDEFAULT,
        int nWidth = CW_USEDEFAULT,
        int nHeight = CW_USEDEFAULT,
        HWND hWndParent = 0,
        HMENU hMenu = 0
    )
    {

        // Register window class
        WNDCLASS wc = {};

        // get main instance
        wininfo_struct->hInstance = GetModuleHandle(NULL);

        wc.lpfnWndProc = DERIVED_TYPE::WindowProc;
        wc.hInstance = wininfo_struct->hInstance;
        wc.lpszClassName = ClassName();

        RegisterClass(&wc);

        wininfo_struct->hwnd = CreateWindowEx(
            dwExStyle, ClassName(), lpWindowName, dwStyle, x, y,
            nWidth, nHeight, hWndParent, hMenu, hInstance, this
        );

        return (wininfo_struct.m_hwnd ? TRUE : FALSE);
    }

protected:

    virtual PCWSTR  ClassName() const = 0;
    virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;

};

#endif