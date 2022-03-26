#pragma once

// Window command handler
void cmdHandlerScene3(struct scene_ops* self, WPARAM wParam, LPARAM lParam)
{
	if (HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) == SCENE3_BUTTON_SAMPLE_EXAMPLE)
	{
		struct banker_ptable btable = { 0 };
		MessageBeep(0);
		sampleBankingData(self);
		getBankingData(self, &btable);
		calculateBankingData(self, &btable);

	}
	else if (HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) == SCENE3_BUTTON_FIND_AVAILABLE)
	{
		struct banker_ptable btable = {0};
		
		MessageBeep(0);
		getBankingData(self, &btable);
		calculateBankingData(self, &btable);
	}
	else if (LOWORD(wParam) == SCENE3_BUTTON_RESET && HIWORD(wParam) == BN_CLICKED)
	{
		MessageBeep(0);
		resetBankingData(self);
	}
}



/*
Create windows
and subwindows
for the process
table
*/
void create_ptable(struct scene_ops* self, DWORD ptable_index, DWORD startX, DWORD startY)
{
	RECT* mRect;

	const int padding = 4;
	const int PTABLE_WIDTH = 350 - padding * 2;
	const int PTABLE_HEIGHT = 350 - padding;
	const int BOX_RIGHT = 100;
	const int SRNO_BOX_RIGHT = 50;
	const int BOX_BOTTOM = 50;
	const int FIRST_BOX_BOTTOM = 40;

	struct scene_3_info* scene3 = (scene_3_info*)self->private_data;
	struct process_table* ptable = scene3->ptable_info[ptable_index];


	ptable->mCoordinates[0].left = startX;
	ptable->mCoordinates[0].top = startY;
	ptable->mCoordinates[0].right = startX + PTABLE_WIDTH;
	ptable->mCoordinates[0].bottom = startY + PTABLE_HEIGHT;

	ptable->mCoordinates[1].left = ptable->mCoordinates[0].left + padding;
	ptable->mCoordinates[1].top = ptable->mCoordinates[0].top + padding;
	ptable->mCoordinates[1].right = ptable->mCoordinates[0].left + PTABLE_WIDTH - padding;
	ptable->mCoordinates[1].bottom = ptable->mCoordinates[1].top + BOX_BOTTOM - padding;


	// Second row 
	ptable->mCoordinates[2].left = ptable->mCoordinates[1].left;
	ptable->mCoordinates[2].top = ptable->mCoordinates[1].bottom + padding;
	ptable->mCoordinates[2].right = ptable->mCoordinates[2].left + SRNO_BOX_RIGHT - padding;
	ptable->mCoordinates[2].bottom = ptable->mCoordinates[2].top + FIRST_BOX_BOTTOM - padding;

	ptable->mCoordinates[3].left = ptable->mCoordinates[2].right + padding;
	ptable->mCoordinates[3].top = ptable->mCoordinates[2].top;
	ptable->mCoordinates[3].right = ptable->mCoordinates[2].right + BOX_RIGHT - padding;
	ptable->mCoordinates[3].bottom = ptable->mCoordinates[2].bottom;


	ptable->mCoordinates[4].left = ptable->mCoordinates[3].right + padding;
	ptable->mCoordinates[4].top = ptable->mCoordinates[2].top;
	ptable->mCoordinates[4].right = ptable->mCoordinates[3].right + BOX_RIGHT - padding;
	ptable->mCoordinates[4].bottom = ptable->mCoordinates[2].bottom;

	ptable->mCoordinates[5].left = ptable->mCoordinates[4].right + padding;
	ptable->mCoordinates[5].top = ptable->mCoordinates[2].top;
	ptable->mCoordinates[5].right = ptable->mCoordinates[4].right + BOX_RIGHT - padding;
	ptable->mCoordinates[5].bottom = ptable->mCoordinates[2].bottom;



	HWND* child_info = &scene3->ptable_info[ptable_index]->child_data[0];

	// other rows
	mRect = &ptable->mCoordinates[6];
	DWORD bottom = ptable->mCoordinates[5].bottom;
	for (DWORD i = 0; i < 20; i += 4)
	{
		mRect[i].left = ptable->mCoordinates[1].left;
		mRect[i].top = bottom + padding;
		mRect[i].right = mRect[i].left + SRNO_BOX_RIGHT - padding;
		mRect[i].bottom = mRect[i].top + BOX_BOTTOM - padding;

		mRect[i + 1].left = mRect[i].right + padding;
		mRect[i + 1].top = mRect[i].top;
		mRect[i + 1].right = mRect[i].right + BOX_RIGHT - padding;
		mRect[i + 1].bottom = mRect[i].bottom;
		*child_info = CreateWindow(L"EDIT", L"", WS_BORDER | WS_VISIBLE | WS_CHILD,
			mRect[i + 1].left + padding,
			mRect[i + 1].top + padding,
			84,
			38,
			self->_wininfo->hwnd,
			NULL,
			self->_wininfo->hInstance,
			NULL);
		child_info++;



		mRect[i + 2].left = mRect[i + 1].right + padding;
		mRect[i + 2].top = mRect[i].top;
		mRect[i + 2].right = mRect[i + 1].right + BOX_RIGHT - padding;
		mRect[i + 2].bottom = mRect[i].bottom;
		*child_info = CreateWindow(L"EDIT", L"", WS_BORDER | WS_VISIBLE | WS_CHILD,
			mRect[i + 2].left + padding,
			mRect[i + 2].top + padding,
			84,
			38,
			self->_wininfo->hwnd,
			NULL,
			self->_wininfo->hInstance,
			NULL);
		child_info++;

		mRect[i + 3].left = mRect[i + 2].right + padding;
		mRect[i + 3].top = mRect[i].top;
		mRect[i + 3].right = mRect[i + 2].right + BOX_RIGHT - padding;
		mRect[i + 3].bottom = mRect[i].bottom;
		*child_info = CreateWindow(L"EDIT", L"", WS_BORDER | WS_VISIBLE | WS_CHILD,
			mRect[i + 3].left + padding,
			mRect[i + 3].top + padding,
			84,
			38,
			self->_wininfo->hwnd,
			NULL,
			self->_wininfo->hInstance,
			NULL);
		child_info++;

		bottom += BOX_BOTTOM;
	}

}

/*
paint process
table will draw
process table on screen
device context
*/

void paint_ptable(struct scene_ops* self, HDC hdc)
{
	struct scene_3_info* scene3 = (scene_3_info*)self->private_data;
	HBRUSH rectBrush = CreateSolidBrush(0x00EBCE87);
	HBRUSH borderBrush = CreateSolidBrush(0x00);
	wchar_t pname[4] = { 0 };
	DWORD start;

	FrameRect(hdc, &scene3->ptable_info[0]->mCoordinates[0],borderBrush);
	FillRect(hdc, &scene3->ptable_info[0]->mCoordinates[1], rectBrush);
	FrameRect(hdc, &scene3->ptable_info[0]->mCoordinates[1],borderBrush);
	DrawTextInCenter(hdc, L"Allocation", &scene3->ptable_info[0]->mCoordinates[1], 20, 0x00, L"Arial");


	FrameRect(hdc, &scene3->ptable_info[1]->mCoordinates[0],borderBrush);
	FillRect(hdc, &scene3->ptable_info[1]->mCoordinates[1], rectBrush);
	FrameRect(hdc, &scene3->ptable_info[1]->mCoordinates[1],borderBrush);
	DrawTextInCenter(hdc, L"Max", &scene3->ptable_info[1]->mCoordinates[1], 20, 0x00, L"Arial");


	FrameRect(hdc, &scene3->ptable_info[2]->mCoordinates[0],borderBrush);
	FillRect(hdc, &scene3->ptable_info[2]->mCoordinates[1], rectBrush);
	FrameRect(hdc, &scene3->ptable_info[2]->mCoordinates[1],borderBrush);
	DrawTextInCenter(hdc, L"Need", &scene3->ptable_info[2]->mCoordinates[1], 20, 0x00, L"Arial");


	for (DWORD i = 0; i < scene3->ptable_len; i++)
	{
		RECT* pTableRect = &scene3->ptable_info[i]->mCoordinates[2];

		FillRect(hdc, &pTableRect[0], rectBrush);
		FrameRect(hdc, &pTableRect[0], borderBrush);

		// Draw A
		FillRect(hdc, &pTableRect[1], rectBrush);
		FrameRect(hdc, &pTableRect[1], borderBrush);
		DrawTextInCenter(hdc, L"A", &pTableRect[1], 20, 0x00, L"Arial");

		// Draw B
		FillRect(hdc, &pTableRect[2], rectBrush);
		FrameRect(hdc, &pTableRect[2], borderBrush);
		DrawTextInCenter(hdc, L"B", &pTableRect[2], 20, 0x00, L"Arial");

		// Draw C
		FillRect(hdc, &pTableRect[3], rectBrush);
		FrameRect(hdc, &pTableRect[3], borderBrush);
		DrawTextInCenter(hdc, L"C", &pTableRect[3], 20, 0x00, L"Arial");

		start = 1;
		for (DWORD j = 4; j < 24; start++, j++)
		{
			swprintf(pname, 3, L"P%d", start);
			// Draw Pj
			FillRect(hdc, &pTableRect[j], rectBrush);
			FrameRect(hdc, &pTableRect[j], borderBrush);
			DrawTextInCenter(hdc, pname, &pTableRect[j], 20, 0x00, L"Arial");

			j++;
			FillRect(hdc, &pTableRect[j], rectBrush);
			FrameRect(hdc, &pTableRect[j], borderBrush);

			j++;
			FillRect(hdc, &pTableRect[j], rectBrush);
			FrameRect(hdc, &pTableRect[j], borderBrush);

			j++;
			FillRect(hdc, &pTableRect[j], rectBrush);
			FrameRect(hdc, &pTableRect[j], borderBrush);
		}

	}
	DeleteObject(rectBrush);
	DeleteObject(borderBrush);

}

/*
Destroy Existing
window for current scene
deallocate memory
*/
void free_ptable(struct scene_ops* self)
{
	struct scene_3_info* scene3 = (scene_3_info*)self->private_data;

	for (DWORD i = 0; i < scene3->ptable_len; i++)
	{
		for (DWORD j = 0; j < PTABLE_CHILD_LEN; j++)
		{
			DestroyWindow(scene3->ptable_info[i]->child_data[j]);
		}
		delete scene3->ptable_info[i];
	}
}


/*
create  a process
table and create
child windows
required by process
table
*/
void create_available_ptable(struct scene_ops* self, DWORD startX, DWORD startY)
{
	const int padding = 4;
	const int PTABLE_WIDTH = 300 + padding;
	const int PTABLE_HEIGHT = 140;
	const int BOX_BOTTOM = 50;
	const int BOX_RIGHT = 100;
	const int FIRST_BOX_BOTTOM = 40;
	struct scene_3_info* scene3 = (scene_3_info*)self->private_data;

	struct available_ptable* available_pt = scene3->available_pt;
	HWND* child_info = scene3->available_pt->child_data;

	available_pt->mCoordinates[0].left = startX;
	available_pt->mCoordinates[0].top = startY;
	available_pt->mCoordinates[0].right = startX + PTABLE_WIDTH;
	available_pt->mCoordinates[0].bottom = startY + PTABLE_HEIGHT;

	available_pt->mCoordinates[1].left = available_pt->mCoordinates[0].left + padding;
	available_pt->mCoordinates[1].top = available_pt->mCoordinates[0].top + padding;
	available_pt->mCoordinates[1].right = available_pt->mCoordinates[0].left + PTABLE_WIDTH - padding;
	available_pt->mCoordinates[1].bottom = available_pt->mCoordinates[0].top + BOX_BOTTOM - padding;

	// A
	available_pt->mCoordinates[2].left = available_pt->mCoordinates[1].left;
	available_pt->mCoordinates[2].top = available_pt->mCoordinates[1].bottom + padding;
	available_pt->mCoordinates[2].right = available_pt->mCoordinates[1].left + BOX_RIGHT - padding;
	available_pt->mCoordinates[2].bottom = available_pt->mCoordinates[2].top + FIRST_BOX_BOTTOM - padding;

	// B
	available_pt->mCoordinates[3].left = available_pt->mCoordinates[2].right + padding;
	available_pt->mCoordinates[3].top = available_pt->mCoordinates[2].top;
	available_pt->mCoordinates[3].right = available_pt->mCoordinates[3].left + BOX_RIGHT - padding;
	available_pt->mCoordinates[3].bottom = available_pt->mCoordinates[2].bottom;

	// C
	available_pt->mCoordinates[4].left = available_pt->mCoordinates[3].right + padding;
	available_pt->mCoordinates[4].top = available_pt->mCoordinates[2].top;
	available_pt->mCoordinates[4].right = available_pt->mCoordinates[4].left + BOX_RIGHT - padding;
	available_pt->mCoordinates[4].bottom = available_pt->mCoordinates[2].bottom;


	available_pt->mCoordinates[5].left = available_pt->mCoordinates[2].left;
	available_pt->mCoordinates[5].top = available_pt->mCoordinates[4].bottom + padding;
	available_pt->mCoordinates[5].right = available_pt->mCoordinates[2].right;
	available_pt->mCoordinates[5].bottom = available_pt->mCoordinates[5].top + BOX_BOTTOM - padding;

	*child_info = CreateWindow(L"EDIT", L"", WS_BORDER | WS_VISIBLE | WS_CHILD,
		available_pt->mCoordinates[5].left + padding,
		available_pt->mCoordinates[5].top + padding,
		88,
		38,
		self->_wininfo->hwnd,
		NULL,
		self->_wininfo->hInstance,
		NULL);
	child_info++;


	available_pt->mCoordinates[6].left = available_pt->mCoordinates[5].right + padding;
	available_pt->mCoordinates[6].top = available_pt->mCoordinates[5].top;
	available_pt->mCoordinates[6].right = available_pt->mCoordinates[6].left + BOX_RIGHT - padding;
	available_pt->mCoordinates[6].bottom = available_pt->mCoordinates[5].bottom;
	*child_info = CreateWindow(L"EDIT", L"", WS_BORDER | WS_VISIBLE | WS_CHILD,
		available_pt->mCoordinates[6].left + padding,
		available_pt->mCoordinates[6].top + padding,
		88,
		38,
		self->_wininfo->hwnd,
		NULL,
		self->_wininfo->hInstance,
		NULL);
	child_info++;

	available_pt->mCoordinates[7].left = available_pt->mCoordinates[6].right + padding;
	available_pt->mCoordinates[7].top = available_pt->mCoordinates[5].top;
	available_pt->mCoordinates[7].right = available_pt->mCoordinates[7].left + BOX_RIGHT - padding;
	available_pt->mCoordinates[7].bottom = available_pt->mCoordinates[5].bottom;

	*child_info = CreateWindow(L"EDIT", L"", WS_BORDER | WS_VISIBLE | WS_CHILD,
		available_pt->mCoordinates[7].left + padding,
		available_pt->mCoordinates[7].top + padding,
		88,
		38,
		self->_wininfo->hwnd,
		NULL,
		self->_wininfo->hInstance,
		NULL);
	child_info++;

}

/*
paints available process
table on screen device
contexts
*/
void paint_available_ptable(struct scene_ops* self, HDC hdc)
{
	struct scene_3_info* scene3 = (scene_3_info*)self->private_data;

	RECT* available_ptable_Rect = &scene3->available_pt->mCoordinates[0];
	HBRUSH rectBrush = CreateSolidBrush(0x00EBCE87);
	HBRUSH borderBrush = CreateSolidBrush(0x00);

	FrameRect(hdc, &available_ptable_Rect[0],borderBrush);

	FillRect(hdc, &available_ptable_Rect[1], rectBrush);
	FrameRect(hdc, &available_ptable_Rect[1],borderBrush);
	DrawTextInCenter(hdc, L"Available", &available_ptable_Rect[1], 20, 0x00, L"Arial");

	FillRect(hdc, &available_ptable_Rect[2], rectBrush);
	FrameRect(hdc, &available_ptable_Rect[2],borderBrush);
	DrawTextInCenter(hdc, L"A", &available_ptable_Rect[2], 20, 0x00, L"Arial");

	FillRect(hdc, &available_ptable_Rect[3], rectBrush);
	FrameRect(hdc, &available_ptable_Rect[3],borderBrush);
	DrawTextInCenter(hdc, L"B", &available_ptable_Rect[3], 20, 0x00, L"Arial");

	FillRect(hdc, &available_ptable_Rect[4], rectBrush);
	FrameRect(hdc, &available_ptable_Rect[4],borderBrush);
	DrawTextInCenter(hdc, L"C", &available_ptable_Rect[4], 20, 0x00, L"Arial");

	for (DWORD i = 0; i < 3; i++)
	{
		FillRect(hdc, &available_ptable_Rect[5 + i], rectBrush);
		FrameRect(hdc, &available_ptable_Rect[5 + i],borderBrush);
	}
	DeleteObject(rectBrush);
	DeleteObject(borderBrush);
}

// Free available ptable
void free_available_ptable(struct scene_ops* self)
{
	struct scene_3_info* scene3 = (scene_3_info*)self->private_data;

	for (DWORD i = 0; i < AVAILABLE_PTABLE_CHILD_LEN; i++)
	{
		DestroyWindow(scene3->available_pt->child_data[i]);
	}
}

#ifndef BUTTONS_START_X
#define BUTTONS_START_X 450

#ifndef BUTTONS_START_Y
#define BUTTONS_START_Y 540


/*
Paint function for the
scene3
*/
void paintScene3(struct scene_ops* self)
{
	PAINTSTRUCT ps;
	RECT rc;
	HDC hdc;
	HBRUSH rectBrush = CreateSolidBrush(0x00ffffff);

	GetClientRect(self->_wininfo->hwnd, &rc);

	hdc = BeginPaint(self->_wininfo->hwnd, &ps);
	
	FillRect(hdc, &rc, rectBrush);
	paint_ptable(self, hdc);
	paint_available_ptable(self, hdc);

	TextWithFontColorStyle(hdc, L"Banker's Algorithm Simulator", 600, 50,
		40, 0x00000000, L"Arial");

	
	TextWithFontColorStyle(hdc, L"No. of instances of A:", BUTTONS_START_X, 650,
		20, 0x00000000, L"Arial");
	TextWithFontColorStyle(hdc, L"No. of instances of B:", BUTTONS_START_X+300, 650,
		20, 0x00000000, L"Arial");
	TextWithFontColorStyle(hdc, L"No. of instances of C:", BUTTONS_START_X+600, 650,
		20, 0x00000000, L"Arial");
	
	TextWithFontColorStyle(hdc, L"Safe Process Sequence:",  1280, 200,
		20, 0x00000000, L"Arial");

	DeleteObject(rectBrush);
	EndPaint(self->_wininfo->hwnd, &ps);
}

/*
Create window and
background scene3
*/
void create_background_scene3(struct scene_ops* self)
{
	struct scene_3_info* scene3 = (struct scene_3_info*)self->private_data;
	const int editbox_width = 80;
	const int editbox_height = 40;
	const int padding = 12;

	scene3->child_len = 13;


	scene3->bchild_window[0] = CreateWindow(L"BUTTON", L"Sample Example", WS_BORDER | WS_VISIBLE | WS_CHILD,
		BUTTONS_START_X, BUTTONS_START_Y,
		140, 50,
		self->_wininfo->hwnd,
		(HMENU)SCENE3_BUTTON_SAMPLE_EXAMPLE,
		self->_wininfo->hInstance,
		NULL);

	scene3->bchild_window[1] = CreateWindow(L"BUTTON", L"Find Available", WS_BORDER | WS_VISIBLE | WS_CHILD,
		BUTTONS_START_X + 150, BUTTONS_START_Y,
		200, 50,
		self->_wininfo->hwnd,
		(HMENU)SCENE3_BUTTON_FIND_AVAILABLE,
		self->_wininfo->hInstance,
		NULL);

// Button at bottom right
	scene3->bchild_window[2] = CreateWindow(L"BUTTON", L"Find need", WS_BORDER | WS_VISIBLE | WS_CHILD,
		BUTTONS_START_X + 360, BUTTONS_START_Y,
		100, 50,
		self->_wininfo->hwnd,
		(HMENU)SCENE3_BUTTON_FIND_NEED,
		self->_wininfo->hInstance,
		NULL);

	scene3->bchild_window[3] = CreateWindow(L"BUTTON", L"Find process sequence", WS_BORDER | WS_VISIBLE | WS_CHILD,
		BUTTONS_START_X + 470, BUTTONS_START_Y,
		170, 50,
		self->_wininfo->hwnd,
		(HMENU)SCENE3_BUTTON_FIND_PROCESS_SEQ,
		self->_wininfo->hInstance,
		NULL);

	scene3->bchild_window[4] = CreateWindow(L"BUTTON", L"RESET", WS_BORDER | WS_VISIBLE | WS_CHILD,
		BUTTONS_START_X + 650, BUTTONS_START_Y,
		100, 50,
		self->_wininfo->hwnd,
		(HMENU)SCENE3_BUTTON_RESET,
		self->_wininfo->hInstance,
		NULL);

// editbox at bottom right 
	scene3->bchild_window[5] = CreateWindow(L"EDIT", L"", WS_BORDER | WS_VISIBLE | WS_CHILD,
		BUTTONS_START_X + 180, BUTTONS_START_Y + 100,
		editbox_width, editbox_height,
		self->_wininfo->hwnd,
		NULL,
		self->_wininfo->hInstance,
		NULL);
	scene3->bchild_window[6] = CreateWindow(L"EDIT", L"", WS_BORDER | WS_VISIBLE | WS_CHILD,
		BUTTONS_START_X + 480, BUTTONS_START_Y + 100,
		editbox_width, editbox_height,
		self->_wininfo->hwnd,
		NULL,
		self->_wininfo->hInstance,
		NULL);

	scene3->bchild_window[7] = CreateWindow(L"EDIT", L"", WS_BORDER | WS_VISIBLE | WS_CHILD,
		BUTTONS_START_X + 780, BUTTONS_START_Y + 100,
		editbox_width, editbox_height,
		self->_wininfo->hwnd,
		NULL,
		self->_wininfo->hInstance,
		NULL);




	scene3->bchild_window[8] = CreateWindow(L"EDIT", L"", WS_BORDER | WS_VISIBLE | WS_CHILD,
		1280, 250,
		editbox_width, editbox_height,
		self->_wininfo->hwnd,
		NULL,
		self->_wininfo->hInstance,
		NULL);

	scene3->bchild_window[9] = CreateWindow(L"EDIT", L"", WS_BORDER | WS_VISIBLE | WS_CHILD,
		1280+ editbox_width + padding, 250,
		editbox_width, editbox_height,
		self->_wininfo->hwnd,
		NULL,
		self->_wininfo->hInstance,
		NULL);

	scene3->bchild_window[10] = CreateWindow(L"EDIT", L"", WS_BORDER | WS_VISIBLE | WS_CHILD,
		1280, 250 + editbox_height + padding,
		editbox_width, editbox_height,
		self->_wininfo->hwnd,
		NULL,
		self->_wininfo->hInstance,
		NULL);

	scene3->bchild_window[11] = CreateWindow(L"EDIT", L"", WS_BORDER | WS_VISIBLE | WS_CHILD,
		1280 + editbox_width + padding, 250 + editbox_height + padding,
		editbox_width, editbox_height,
		self->_wininfo->hwnd,
		NULL,
		self->_wininfo->hInstance,
		NULL);
	scene3->bchild_window[12] = CreateWindow(L"EDIT", L"", WS_BORDER | WS_VISIBLE | WS_CHILD,
		1280, 250 + (editbox_height + padding) * 2,
		editbox_width, editbox_height,
		self->_wininfo->hwnd,
		NULL,
		self->_wininfo->hInstance,
		NULL);
}


#endif
#endif


void destroy_background_scene3(struct scene_ops* self)
{
	struct scene_3_info* scene3 = (struct scene_3_info*)self->private_data;

	for (DWORD i = 0; i < scene3->child_len; i++)
	{
		DestroyWindow(scene3->bchild_window[i]);
	}
}



/*
free all
allocated memory
for scene3 operations

*/
void free_scene3_ops(struct scene_ops* self)
{

	destroy_background_scene3(self);
	free_ptable(self);
	free_available_ptable(self);

	struct scene_3_info* scene3 = (scene_3_info*)self->private_data;
	delete scene3->available_pt;
	delete self->private_data;
	delete self->shared_data;
}


// initialize scene data
void init_scene3_ops(struct scene_ops* self)
{
	self->OnPaint = paintScene3;
	self->loadNextScene = init_scene_ops;
	self->freeScene = free_scene3_ops;
	self->CmdHandler = cmdHandlerScene3;

	struct scene_3_info* scene3 = new struct scene_3_info;
	self->private_data = scene3;
	scene3->ptable_len = 3;

	for (DWORD num = 0; num < scene3->ptable_len; num++)
	{
		scene3->ptable_info[num] = new struct process_table;
	}
	scene3->available_pt = new struct available_ptable;

	create_ptable(self, 0, 100, 150);
	create_ptable(self, 1, 500, 150);
	create_ptable(self, 2, 900, 150);

	create_available_ptable(self, 100, 540);
	create_background_scene3(self);

	// repaint window rectangle
	InvalidateRect(self->_wininfo->hwnd, NULL, FALSE);
}