#pragma once

extern void init_scene3_ops(struct scene_ops*);


HBRUSH CreateGradientBrush(COLORREF top, COLORREF bottom, LPNMCUSTOMDRAW item)
{
    HBRUSH Brush = NULL;
    HDC hdcmem = CreateCompatibleDC(item->hdc);
    HBITMAP hbitmap = CreateCompatibleBitmap(item->hdc, item->rc.right - item->rc.left, item->rc.bottom - item->rc.top);
    SelectObject(hdcmem, hbitmap);

    int r1 = GetRValue(top), r2 = GetRValue(bottom), g1 = GetGValue(top), g2 = GetGValue(bottom), b1 = GetBValue(top), b2 = GetBValue(bottom);
    for (int i = 0; i < item->rc.bottom - item->rc.top; i++)
    {
        RECT temp;
        int r, g, b;
        r = int(r1 + double(i * (r2 - r1) / item->rc.bottom - item->rc.top));
        g = int(g1 + double(i * (g2 - g1) / item->rc.bottom - item->rc.top));
        b = int(b1 + double(i * (b2 - b1) / item->rc.bottom - item->rc.top));
        Brush = CreateSolidBrush(RGB(r, g, b));
        temp.left = 0;
        temp.top = i;
        temp.right = item->rc.right - item->rc.left;
        temp.bottom = i + 1;
        FillRect(hdcmem, &temp, Brush);
        DeleteObject(Brush);
    }
    HBRUSH pattern = CreatePatternBrush(hbitmap);

    DeleteDC(hdcmem);
    DeleteObject(hbitmap);

    return pattern;
}

void cmdHandlerScene2(struct scene_ops* self, WPARAM wParam, LPARAM lParam)
{
    extern void readFileNameWithDialogbox(struct scene_ops* self);


    if (LOWORD(wParam) == IDC_EXIT_BUTTON && HIWORD(wParam) == BN_CLICKED)
    {
        self->freeScene(self);
        self->loadNextScene(self);
        InvalidateRect(self->_wininfo->hwnd, NULL, NULL);
    }
    else if (LOWORD(wParam) == IDC_PUSHLIKE_BUTTON && HIWORD(wParam) == BN_CLICKED)
    {
        readFileNameWithDialogbox(self);
        self->freeScene(self);
        self->loadNextScene(self);
        InvalidateRect(self->_wininfo->hwnd, NULL, NULL);
    }
}


LRESULT CALLBACK handleWinProcScene2(struct scene_ops* self, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    struct scene_2_info* scene = (struct scene_2_info *)self->private_data;

    switch (uMsg)
    {
    case WM_NOTIFY:
    {
        LPNMHDR some_item = (LPNMHDR)lParam;

        if (some_item->idFrom == IDC_EXIT_BUTTON && some_item->code == NM_CUSTOMDRAW)
        {
            LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;

            if (item->uItemState & CDIS_SELECTED)
            {
                //Select our color when the button is selected
                if (scene->selectbrush == NULL)
                    scene->selectbrush = CreateGradientBrush(RGB(180, 0, 0), RGB(255, 180, 0), item);

                //Create pen for button border
                HPEN pen = CreatePen(PS_INSIDEFRAME, 0, RGB(0, 0, 0));

                //Select our brush into hDC
                HGDIOBJ old_pen = SelectObject(item->hdc, pen);
                HGDIOBJ old_brush = SelectObject(item->hdc, scene->selectbrush);

                //If you want rounded button, then use this, otherwise use FillRect().
                RoundRect(item->hdc, item->rc.left, item->rc.top, item->rc.right, item->rc.bottom, 5, 5);

                //Clean up
                SelectObject(item->hdc, old_pen);
                SelectObject(item->hdc, old_brush);
                DeleteObject(pen);

                //Now, I don't want to do anything else myself (draw text) so I use this value for return:
                return CDRF_DODEFAULT;
                //Let's say I wanted to draw text and stuff, then I would have to do it before return with
                //DrawText() or other function and return CDRF_SKIPDEFAULT
            }
            else
            {
                if (item->uItemState & CDIS_HOT) //Our mouse is over the button
                {
                    //Select our color when the mouse hovers our button
                    if (scene->hotbrush == NULL)
                        scene->hotbrush = CreateGradientBrush(RGB(255, 230, 0), RGB(245, 0, 0), item);

                    HPEN pen = CreatePen(PS_INSIDEFRAME, 0, RGB(0, 0, 0));

                    HGDIOBJ old_pen = SelectObject(item->hdc, pen);
                    HGDIOBJ old_brush = SelectObject(item->hdc, scene->hotbrush);

                    RoundRect(item->hdc, item->rc.left, item->rc.top, item->rc.right, item->rc.bottom, 5, 5);

                    SelectObject(item->hdc, old_pen);
                    SelectObject(item->hdc, old_brush);
                    DeleteObject(pen);

                    return CDRF_DODEFAULT;
                }

                //Select our color when our button is doing nothing
                if (scene->defaultbrush == NULL)
                    scene->defaultbrush = CreateGradientBrush(RGB(255, 180, 0), RGB(180, 0, 0), item);

                HPEN pen = CreatePen(PS_INSIDEFRAME, 0, RGB(0, 0, 0));

                HGDIOBJ old_pen = SelectObject(item->hdc, pen);
                HGDIOBJ old_brush = SelectObject(item->hdc, scene->defaultbrush);

                RoundRect(item->hdc, item->rc.left, item->rc.top, item->rc.right, item->rc.bottom, 5, 5);

                SelectObject(item->hdc, old_pen);
                SelectObject(item->hdc, old_brush);
                DeleteObject(pen);

                return CDRF_DODEFAULT;
            }
        }
        else if (some_item->idFrom == IDC_PUSHLIKE_BUTTON && some_item->code == NM_CUSTOMDRAW)
        {
            LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;

            if (IsDlgButtonChecked(self->_wininfo->hwnd, some_item->idFrom))
            {
                if (item->uItemState & CDIS_HOT)
                {

                    if (scene->push_hotbrush1 == NULL)
                        scene->push_hotbrush1 = CreateGradientBrush(RGB(0, 0, 245), RGB(0, 230, 255), item);

                    HPEN pen = CreatePen(PS_INSIDEFRAME, 0, RGB(0, 0, 0));

                    HGDIOBJ old_pen = SelectObject(item->hdc, pen);
                    HGDIOBJ old_brush = SelectObject(item->hdc, scene->push_hotbrush1);

                    RoundRect(item->hdc, item->rc.left, item->rc.top, item->rc.right, item->rc.bottom, 10, 10);

                    SelectObject(item->hdc, old_pen);
                    SelectObject(item->hdc, old_brush);
                    DeleteObject(pen);

                    return CDRF_DODEFAULT;
                }


                if (scene->push_checkedbrush == NULL)
                    scene->push_checkedbrush = CreateGradientBrush(RGB(0, 0, 180), RGB(0, 222, 200), item);


                HPEN pen = CreatePen(PS_INSIDEFRAME, 0, RGB(0, 0, 0));


                HGDIOBJ old_pen = SelectObject(item->hdc, pen);
                HGDIOBJ old_brush = SelectObject(item->hdc, scene->push_checkedbrush);


                RoundRect(item->hdc, item->rc.left, item->rc.top, item->rc.right, item->rc.bottom, 10, 10);


                SelectObject(item->hdc, old_pen);
                SelectObject(item->hdc, old_brush);
                DeleteObject(pen);


                return CDRF_DODEFAULT;
            }
            else
            {
                if (item->uItemState & CDIS_HOT)
                {
                    if (scene->push_hotbrush2 == NULL)
                        scene->push_hotbrush2 = CreateGradientBrush(RGB(255, 230, 0), RGB(245, 0, 0), item);

                    HPEN pen = CreatePen(PS_INSIDEFRAME, 0, RGB(0, 0, 0));

                    HGDIOBJ old_pen = SelectObject(item->hdc, pen);
                    HGDIOBJ old_brush = SelectObject(item->hdc, scene->push_hotbrush2);

                    RoundRect(item->hdc, item->rc.left, item->rc.top, item->rc.right, item->rc.bottom, 10, 10);

                    SelectObject(item->hdc, old_pen);
                    SelectObject(item->hdc, old_brush);
                    DeleteObject(pen);

                    return CDRF_DODEFAULT;
                }

                if (scene->push_uncheckedbrush == NULL)
                    scene->push_uncheckedbrush = CreateGradientBrush(RGB(255, 180, 0), RGB(180, 0, 0), item);

                HPEN pen = CreatePen(PS_INSIDEFRAME, 0, RGB(0, 0, 0));

                HGDIOBJ old_pen = SelectObject(item->hdc, pen);
                HGDIOBJ old_brush = SelectObject(item->hdc, scene->defaultbrush);

                RoundRect(item->hdc, item->rc.left, item->rc.top, item->rc.right, item->rc.bottom, 10, 10);

                SelectObject(item->hdc, old_pen);
                SelectObject(item->hdc, old_brush);
                DeleteObject(pen);

                return CDRF_DODEFAULT;
            }
        }
        return CDRF_DODEFAULT;
    }
    break;
    case WM_CTLCOLORBTN: //In order to make those edges invisble when we use RoundRect(),
    {                //we make the color of our button's background match window's background
        return (LRESULT)GetSysColorBrush(COLOR_WINDOW + 1);
    }
    break;
    }
    return DefWindowProc(self->_wininfo->hwnd, uMsg, wParam, lParam);
}






void paintScene2(struct scene_ops* self)
{
    PAINTSTRUCT ps;
    RECT rc = { 0 };
    HDC hdc = BeginPaint(self->_wininfo->hwnd, &ps);
    HBRUSH cleanupBrush = CreateSolidBrush(0x00ffffff);

    GetClientRect(self->_wininfo->hwnd, &rc);

    GetClientRect(self->_wininfo->hwnd, &rc);
    FillRect(hdc, &rc, cleanupBrush);

    DeleteObject(cleanupBrush);
}


/* read file
name selected from explorer
dialogbox
*/
void readFileNameWithDialogbox(struct scene_ops* self)
{
    // open filedialog box
    HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED |
        COINIT_DISABLE_OLE1DDE);
    if (SUCCEEDED(hr))
    {
        IFileOpenDialog* pFileOpen;

        // Create the FileOpenDialog object.
        hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
            IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));

        if (SUCCEEDED(hr))
        {
            // Show the Open dialog box.
            hr = pFileOpen->Show(NULL);

            // Get the file name from the dialog box.
            if (SUCCEEDED(hr))
            {
                IShellItem* pItem;
                hr = pFileOpen->GetResult(&pItem);
                if (SUCCEEDED(hr))
                {
                    PWSTR pszFilePath;
                    hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

                    size_t size = wcslen(pszFilePath) + 1;

                    self->shared_data = new wchar_t[size];
                    wcscpy_s((wchar_t*)self->shared_data, size, pszFilePath);

                    // Display the file name to the user.
                    if (SUCCEEDED(hr))
                    {
                        MessageBoxW(NULL, pszFilePath, L"File Path", MB_OK);
                        CoTaskMemFree(pszFilePath);
                    }
                    pItem->Release();
                }
            }
            pFileOpen->Release();
        }
        CoUninitialize();
    }
}


void free_scene2_ops(struct scene_ops* self)
{
    struct scene_2_info* scene2 = (struct scene_2_info*)self->private_data;
    
    DeleteObject(scene2->defaultbrush);
    DeleteObject(scene2->selectbrush);
    DeleteObject(scene2->hotbrush);
    DeleteObject(scene2->push_checkedbrush);
    DeleteObject(scene2->push_hotbrush1);
    DeleteObject(scene2->push_hotbrush2);
    DeleteObject(scene2->push_uncheckedbrush);

    DestroyWindow(scene2->Exit_Button);
    DestroyWindow(scene2->Pushlike_Button);

    delete self->private_data;
}

void init_scene2_ops(struct scene_ops* self)
{
	self->OnPaint = paintScene2;
	self->loadNextScene = init_scene3_ops;
    self->handleDefaultProc = handleWinProcScene2;
    self->CmdHandler = cmdHandlerScene2;
    self->freeScene = free_scene2_ops;

    struct scene_2_info *scene2 = new scene_2_info;
    self->private_data = (void *)scene2;

    memset(scene2, 0, sizeof(scene_2_info));


    scene2->Exit_Button = CreateWindowEx(NULL, L"BUTTON", L"Use Manually",
        WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
        850, 300, 200, 200, self->_wininfo->hwnd, (HMENU)IDC_EXIT_BUTTON, NULL, NULL);
    if (scene2->Exit_Button == NULL)
    {
        MessageBox(NULL, L"Button Creation Failed!", L"Error!", MB_ICONEXCLAMATION);
        exit(EXIT_FAILURE);
    }

    scene2->Pushlike_Button = CreateWindowEx(NULL, L"BUTTON", L"Open With",
        WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX | BS_PUSHLIKE,
        450, 300, 200, 200, self->_wininfo->hwnd, (HMENU)IDC_PUSHLIKE_BUTTON, NULL, NULL);

    if (scene2->Pushlike_Button == NULL)
    {
        MessageBox(NULL, L"Button Creation Failed!", L"Error!", MB_ICONEXCLAMATION);
        exit(EXIT_FAILURE);
    }
    InvalidateRect(self->_wininfo->hwnd, NULL, NULL);
}
