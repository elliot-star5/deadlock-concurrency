#pragma once

// CreateAnimationCtrl - creates an animation control, positions it 
//                       below the specified control in a dialog box, 
//                       and opens the AVI clip for the animation control. 
// Returns the handle to the animation control. 
// hwndDlg             - handle to the dialog box. 
// nIDCtl              - identifier of the control below which the animation control 
//                       is to be positioned. 
// 
// Constants 
//     IDC_ANIMATE - identifier of the animation control. 
//     CX_FRAME, CY_FRAME - width and height of the frames 
//     in the AVI clip. 

#define IDC_ANIMATE 301


class MAVI_Animator
{
public:
    HWND hWindowhandler;

    void CreateAnimation(HWND hwnd, HINSTANCE g_hinst, const wchar_t* filename);
    void CreateAnimationControl(HWND hParent, HINSTANCE hInstance);

};
/*void MAVI_Animator::CreateAnimationCtrl(HWND hwndDlg, HINSTANCE hInstance, char *filename, int CX_FRAME,int CY_FRAME, int nIDCtl)
{
    HWND hwndAnim = NULL;


    // Create the animation control.
    // IDC_ANIMATE - identifier of the animation control. 
    // hwndDlg - handle to the dialog box.
    RECT rc;
    hwndAnim = Animate_Create(hwndDlg, IDC_ANIMATE,
        WS_BORDER | WS_CHILD, hInstance);

    // Get the screen coordinates of the specified control button.
    // nIDCtl - identifier of the control below which the animation control is to be positioned.
    GetWindowRect(GetDlgItem(hwndDlg, nIDCtl), &rc);

    // Convert the coordinates of the lower-left corner to 
    // client coordinates.
    POINT pt;
    pt.x = rc.left;
    pt.y = rc.bottom;
    ScreenToClient(hwndDlg, &pt);

    // Position the animation control below the Stop button.
    // CX_FRAME, CY_FRAME - width and height of the frames in the AVI clip.      
    SetWindowPos(hwndAnim, 0, pt.x, pt.y + 20,
        CX_FRAME, CY_FRAME,
        SWP_NOZORDER | SWP_DRAWFRAME);

    // Open the AVI clip, and show the animation control.
    Animate_Open(hwndAnim, filename);
    ShowWindow(hwndAnim, SW_SHOW);

}


*/


void MAVI_Animator::CreateAnimationControl(HWND hParent, HINSTANCE hInstance)
{
    hWindowhandler = Animate_Create(hParent, ACS_AUTOPLAY, WS_BORDER | WS_CHILD, hInstance);
    Animate_Open(hWindowhandler, L"drop.avi");
    ShowWindow(hWindowhandler, SW_SHOWNORMAL);
    
}


void MAVI_Animator::CreateAnimation(HWND hwnd, HINSTANCE g_hinst, const wchar_t *filename)
{
    hWindowhandler = MCIWndCreate(hwnd, g_hinst, WS_CHILD |     // child window
        WS_VISIBLE |               // visible
        MCIWNDF_NOTIFYMODE |       // notifies of mode changes
        MCIWNDF_NOPLAYBAR, filename);
}