#pragma once


/*
Output text with given 
font, color, style
and coordinates
*/
void TextWithFontColorStyle(HDC hdc,
	const wchar_t *text,
	DWORD startX,
	DWORD startY,
	DWORD fontsize,
	COLORREF color, 
	const wchar_t *style)
{
	HFONT hFont;
	RECT rect;

	rect.left = startX;
	rect.top = startY;

	rect.right = APPLICATION_WIDTH;
	rect.bottom = APPLICATION_HEIGHT;

	//Logical units are device dependent pixels, so this will create a handle to a logical font that is 48 pixels in height.
	//The width, when set to 0, will cause the font mapper to choose the closest matching value.
	//The font face name will be Impact.
	hFont = CreateFontW(fontsize, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, style);
	SelectObject(hdc, hFont);
	SetTextColor(hdc, color);
	SetBkMode(hdc, TRANSPARENT);

	DrawText(hdc, text, -1, &rect, DT_NOCLIP);
}



/*
Draws text
in center of rectangle
from horizontally and
vertically
both with
font, color, style
*/
void DrawTextInCenter(HDC hdc,
	const wchar_t* text,
	RECT* rc,
	DWORD fontsize,
	COLORREF color,
	const wchar_t* style)
{
	HFONT hFont;
	RECT rect;

	rect.left = rc->left;
	rect.top = (rc->top + rc->bottom) / 2 - fontsize / 2;

	rect.right = rc->right;
	rect.bottom = rc->bottom;

	//Logical units are device dependent pixels, so this will create a handle to a logical font that is 48 pixels in height.
	//The width, when set to 0, will cause the font mapper to choose the closest matching value.
	//The font face name will be Impact.
	hFont = CreateFontW(fontsize, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, style);
	SelectObject(hdc, hFont);
	SetTextColor(hdc, color);
	SetBkMode(hdc, TRANSPARENT);

	DrawText(hdc, text, -1, &rect, DT_CENTER);
}


bool LoadAndBlitBitmap(LPCWSTR szFileName, HDC
	hWinDC, int startX, int startY)
{
	// Load the bitmap image file
	HBITMAP hBitmap;


	hBitmap = (HBITMAP)::LoadImage(NULL, szFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (hBitmap == NULL) {
		MessageBox(NULL, __T("LoadImage Failed"), __T("Error"), MB_OK);
		return false;
	}

	// Create a device context that is compatible with the window
	HDC hLocalDC;
	hLocalDC = CreateCompatibleDC(hWinDC);
	if (hLocalDC == NULL) {
		MessageBox(NULL, __T("CreateCompatibleDC Failed"), __T("Error"), MB_OK);
		return false;
	}

	// Get the bitmap's parameters and verify the get
	BITMAP qBitmap;

	int iReturn = GetObject(reinterpret_cast<HGDIOBJ>(hBitmap), sizeof(BITMAP),
		reinterpret_cast<LPVOID>(&qBitmap));
	if (!iReturn) {
		MessageBox(NULL, __T("GetObject Failed"), __T("Error"), MB_OK);
		return false;
	}


	// Select the loaded bitmap into the device context
	HBITMAP hOldBmp = (HBITMAP)::SelectObject(hLocalDC, hBitmap);
	if (hOldBmp == NULL) {
		MessageBox(NULL, __T("SelectObject Failed"), __T("Error"), MB_OK);
		return false;
	}



// Blit the dc which holds the bitmap onto the window's dc
	BOOL qRetBlit = BitBlt(hWinDC, startX-qBitmap.bmWidth/2, startY-qBitmap.bmHeight/2, qBitmap.bmWidth, qBitmap.bmHeight,
		hLocalDC, 0, 0, SRCCOPY);
	if (!qRetBlit) {
		MessageBox(NULL, __T("Blit Failed"), __T("Error"), MB_OK);
		return false;
	}

	// Unitialize and deallocate resources
	SelectObject(hLocalDC, hOldBmp);
	DeleteDC(hLocalDC);
	DeleteObject(hBitmap);
	return true;
}





bool LoadStreatchBitmap(LPCWSTR szFileName, HDC hWinDC, RECT *imageSizeRect)
{
	// Load the bitmap image file
	HBITMAP hBitmap;

	hBitmap = (HBITMAP)::LoadImage(NULL, szFileName, IMAGE_BITMAP, 0, 0,
		LR_LOADFROMFILE);
	// Verify that the image was loaded
	if (hBitmap == NULL) {
		::MessageBox(NULL, __T("LoadImage Failed"), __T("Error"), MB_OK);
		return false;
	}

	// Create a device context that is compatible with the window
	HDC hLocalDC;
	hLocalDC = ::CreateCompatibleDC(hWinDC);
	// Verify that the device context was created
	if (hLocalDC == NULL) {
		::MessageBox(NULL, __T("CreateCompatibleDC Failed"), __T("Error"), MB_OK);
		return false;
	}

	// Get the bitmap's parameters and verify the get
	BITMAP qBitmap;

	int iReturn = GetObject(reinterpret_cast<HGDIOBJ>(hBitmap), sizeof(BITMAP),
		reinterpret_cast<LPVOID>(&qBitmap));
	if (!iReturn) {
		::MessageBox(NULL, __T("GetObject Failed"), __T("Error"), MB_OK);
		return false;
	}


	// Select the loaded bitmap into the device context
	HBITMAP hOldBmp = (HBITMAP)::SelectObject(hLocalDC, hBitmap);
	if (hOldBmp == NULL) {
		::MessageBox(NULL, __T("SelectObject Failed"), __T("Error"), MB_OK);
		return false;
	}


	BOOL qRetBlit = StretchBlt(hWinDC, 
		imageSizeRect->left, 
		imageSizeRect->top, 
		imageSizeRect->right, 
		imageSizeRect->bottom
		, hLocalDC,
		0, 
		0, 
		qBitmap.bmWidth, 
		qBitmap.bmHeight,
		SRCCOPY);


	if (!qRetBlit) {
		::MessageBox(NULL, __T("Blit Failed"), __T("Error"), MB_OK);
		return false;
	}

	// Unitialize and deallocate resources
	::SelectObject(hLocalDC, hOldBmp);
	::DeleteDC(hLocalDC);
	::DeleteObject(hBitmap);
	return true;
}