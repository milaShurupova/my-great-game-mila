#pragma once
#include "main.h"

#define MAX_LOADSTRING 100

HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];
HWND hScore;

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

#define INDENT_IN_PIXELS				(20)
#define SUPPORT_FIELD_WIDTH_IN_PIXEL	(350)
#define BLOCK_SIZE_IN_PIXEL				(25)

#define PLAY_FIELD_HEIGHT_IN_BLOCKS		(21) // field + 1 for boundary
#define PLAY_FIELD_WIDTH_IN_BLOCKS		(12) // field + 2 for boundary

#define TETROMINO_TYPES		(7)
#define TETROMINO_HEIGHT	(4)
#define TETROMINO_WIDTH		(4)

#define ID_BUTTON_START		(500)
#define ID_BUTTON_SCORE		(600)

enum gameStatus
{
	PLAYING,
	GAME_OVER
};

enum blockType
{
	EMPTY_BLOCK,
	MOVING_BLOCK,
	STAYING_BLOCK,
	BOUNDARY_BLOCK
};

typedef struct _Tetromino
{
	int x;
	int y;
	int type;
	int tetromino[TETROMINO_HEIGHT][TETROMINO_WIDTH];
} Tetromino;

typedef enum _MoveType
{
	MOVE_TO_LEFT,
	MOVE_TO_RIGHT,
	MOVE_TO_DOWN
} MoveType;

typedef enum _RotateType
{
	CLOCKWISE,
	COUNTER_CLOCKWISE
} RotateType;