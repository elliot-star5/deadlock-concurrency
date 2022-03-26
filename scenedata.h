#pragma once

#define PTABLE_CHILD_LEN 15
#define AVAILABLE_PTABLE_CHILD_LEN 3

#define IDC_EXIT_BUTTON 101
#define IDC_PUSHLIKE_BUTTON 102


#define SCENE3_BUTTON_SAMPLE_EXAMPLE		(WM_USER+1)
#define SCENE3_BUTTON_FIND_AVAILABLE		(WM_USER+2)
#define SCENE3_BUTTON_FIND_NEED				(WM_USER+3)
#define SCENE3_BUTTON_FIND_PROCESS_SEQ		(WM_USER+4)
#define SCENE3_BUTTON_RESET					(WM_USER+5)

/*
window_info
struct contains
current instance and
handle to window
*/
struct window_info {
	HWND hwnd;
	HINSTANCE hInstance;

};

/*
process table is used
for drawing process table on
screen mCoordinates are
are Rectangle of the process
table
*/
struct process_table {
	HWND child_data[PTABLE_CHILD_LEN];
	RECT mCoordinates[26];
};

/*
Available ptable is
used for storing available
resources for the process
in system
*/
struct available_ptable {
	HWND child_data[AVAILABLE_PTABLE_CHILD_LEN];
	RECT mCoordinates[10];
};

struct scene_3_info
{
	struct process_table* ptable_info[3];						// Process table drawing info
	struct available_ptable* available_pt;						// available process table drawing info

	DWORD ptable_len;											// total number of Process table drawing
	DWORD child_len;											// Number of child window
	HWND bchild_window[14];										// background child windows
};


struct scene_2_info
{
	// Brushes for drawing buttons
	HBRUSH defaultbrush;
	HBRUSH hotbrush;
	HBRUSH selectbrush;
	HBRUSH push_uncheckedbrush;
	HBRUSH push_checkedbrush;
	HBRUSH push_hotbrush1;
	HBRUSH push_hotbrush2;

	HWND Exit_Button;											// Button 2
	HWND Pushlike_Button;										// Button 1

};


/*
Scene operation struct
which contains information
about a particular scene

*/
struct scene_ops
{
	struct window_info* _wininfo;								// Main Window information
	void* private_data;											// private data of `a scene
	void* shared_data;											// shared data between scenes


	void (*OnPaint)(struct scene_ops*);							// it is over written 
																// by Paint function of given scene

	void (*OnKeyCharPress)(struct scene_ops*, WPARAM, LPARAM);	// ... OnKeyCharPress function ...
	void (*loadNextScene)(struct scene_ops*);					// ... loadNextScene function ...
	void (*freeScene)(struct scene_ops*);						// ... freeScene function 
	void (*CmdHandler)(struct scene_ops*, WPARAM, LPARAM);		// ...  WM_COMMAND command handler function

	LRESULT (*handleDefaultProc)(struct scene_ops*, UINT, WPARAM, LPARAM);				// handles other messages
};


extern void init_scene_ops(struct scene_ops*);

void createScene(struct scene_ops* scene_struct, struct window_info* _wininfo)
{
	scene_struct->_wininfo = _wininfo;
	init_scene_ops(scene_struct);
}

void default_free(struct scene_ops*) { }


LRESULT handleDefaultProc(struct scene_ops* self, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(self->_wininfo->hwnd, uMsg, wParam, lParam);
}