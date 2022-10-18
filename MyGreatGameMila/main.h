#pragma once

#include "framework.h"
#include "MyGreatGameMila.h"
#include "helpers.h"
#include "entity.h"
#include "draw.h"
#include "tetromino.h"

#define MAX_LOADSTRING 100

HINSTANCE hInst;                                
WCHAR szTitle[MAX_LOADSTRING];                  
WCHAR szWindowClass[MAX_LOADSTRING];   
HWND hScore;

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);