#pragma once

extern void init_scene2_ops(struct scene_ops*);

// Paint the scene1
void paintScene1(struct scene_ops* self)
{
	PAINTSTRUCT ps;
	RECT rc;
	HDC hdc = BeginPaint(self->_wininfo->hwnd, &ps);
	HBRUSH rectBrush = CreateSolidBrush(0x00ffffff);

	GetClientRect(self->_wininfo->hwnd, &rc);
	FillRect(hdc, &rc, rectBrush);

	LoadAndBlitBitmap(L"simulator.bmp", hdc, APPLICATION_WIDTH/2, APPLICATION_HEIGHT/2);
	DeleteObject(rectBrush);

	EndPaint(self->_wininfo->hwnd, &ps);

}

/*
handles keyboard keys
for the scene1
*/
void keyCharPressScene1(struct scene_ops* self, WPARAM wParam, LPARAM lParam)
{
	if (wParam == VK_SPACE)
	{
		self->freeScene(self);
		self->loadNextScene(self);
		InvalidateRect(self->_wininfo->hwnd, NULL, FALSE);
	}
}

/*
initialize scene1
and load all required function
pointers with corresponding
functions
*/
void init_scene_ops(struct scene_ops* self)
{
	self->OnPaint = paintScene1;
	self->loadNextScene = init_scene2_ops;
	self->OnKeyCharPress = keyCharPressScene1;
	self->handleDefaultProc = handleDefaultProc;
	self->freeScene = default_free;
}

