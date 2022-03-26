#pragma once

#ifndef __DEFINATION_H
#define __DEFINATION_H 1


#define APPLICATION_WIDTH  1600
#define APPLICATION_HEIGHT 900

#define ID_EDITCHILD 100

#include <d2d1.h>

#pragma comment(lib, "d2d1")

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"") 


using namespace std;

#include <Windows.h>
#include <WinUser.h>
#include <atlbase.h>
#include <list>
#include <memory>
#include <shobjidl.h> 

#include <vfw.h>

#pragma comment(lib, "Vfw32")


static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

#include <Commctrl.h>

#include "helperfcn.h"
#include "safety.h"
#include "shapes.h"
#include <stdio.h>
#include <wchar.h>
#include <string.h>

// #include "animationavi.h"
#include "scenedata.h"
#include "csv_parser.h"
#include "MainWindow.h"

#include "scene1.h"
#include "scene2.h"
#include "scene3.h"

extern struct scene_ops scene_ops_info;


#endif