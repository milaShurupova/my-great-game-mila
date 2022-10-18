#include "draw.h"

extern int score;
extern enum gameStatus currentGameStatus;
extern int playField[PLAY_FIELD_HEIGHT_IN_BLOCKS][PLAY_FIELD_WIDTH_IN_BLOCKS];


void drawBackground(HDC hdc)
{
	int x, y;
	x = PLAY_FIELD_WIDTH_IN_BLOCKS * BLOCK_SIZE_IN_PIXEL + INDENT_IN_PIXELS * 2 + SUPPORT_FIELD_WIDTH_IN_PIXEL;
	y = PLAY_FIELD_HEIGHT_IN_BLOCKS * BLOCK_SIZE_IN_PIXEL + INDENT_IN_PIXELS * 2;

	SelectObject(hdc, GetStockObject(DC_PEN));
	SetDCPenColor(hdc, RGB(128, 128, 128));
	HBRUSH hBrushBackground = CreateSolidBrush(RGB(128, 128, 128));
	HBRUSH holdBrush = SelectObject(hdc, hBrushBackground);
	Rectangle(hdc, 0, 0, x, y);
	SelectObject(hdc, holdBrush);
	DeleteObject(hBrushBackground);
}


void drawScoreField(HDC hdc)
{
	static TCHAR buf[128];
	int x = PLAY_FIELD_WIDTH_IN_BLOCKS * BLOCK_SIZE_IN_PIXEL + INDENT_IN_PIXELS * 3;

	wsprintf(buf, L"Move right: push right arrow");
	SetTextColor(hdc, RGB(255, 255, 255));
	SetBkColor(hdc, RGB(128, 128, 128));
	TextOut(hdc, x, 120, buf, lstrlen(buf));

	wsprintf(buf, L"Move left: push left arrow");
	SetTextColor(hdc, RGB(255, 255, 255));
	SetBkColor(hdc, RGB(128, 128, 128));
	TextOut(hdc, x, 160, buf, lstrlen(buf));

	wsprintf(buf, L"Move down: push down arrow");
	SetTextColor(hdc, RGB(255, 255, 255));
	SetBkColor(hdc, RGB(128, 128, 128));
	TextOut(hdc, x, 200, buf, lstrlen(buf));

	wsprintf(buf, L"Rotate clockwise: push up arrow");
	SetTextColor(hdc, RGB(255, 255, 255));
	SetBkColor(hdc, RGB(128, 128, 128));
	TextOut(hdc, x, 240, buf, lstrlen(buf));

	wsprintf(buf, L"Rotate counter clockwise: push space");
	SetTextColor(hdc, RGB(255, 255, 255));
	SetBkColor(hdc, RGB(128, 128, 128));
	TextOut(hdc, x, 280, buf, lstrlen(buf));

	wsprintf(buf, L"Exit game: push escape");
	SetTextColor(hdc, RGB(255, 255, 255));
	SetBkColor(hdc, RGB(128, 128, 128));
	TextOut(hdc, x, 320, buf, lstrlen(buf));
}


void drawFieldBoundary(HDC hdc) 
{
	int x1, x2, y1, y2;
	x1 = y1 = INDENT_IN_PIXELS;
	x2 = (BLOCK_SIZE_IN_PIXEL * PLAY_FIELD_WIDTH_IN_BLOCKS) + INDENT_IN_PIXELS;
	y2 = (BLOCK_SIZE_IN_PIXEL * PLAY_FIELD_HEIGHT_IN_BLOCKS) + INDENT_IN_PIXELS;

	SelectObject(hdc, GetStockObject(DC_PEN));
	SetDCPenColor(hdc, RGB(255, 192, 203));
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x1, y2);
	LineTo(hdc, x2, y2);
	LineTo(hdc, x2, y1);
	LineTo(hdc, x1, y1);
}


void drawBlock(HDC hdc, int i, int j)
{
	int x1, x2, y1, y2;

	x1 = INDENT_IN_PIXELS + (i * BLOCK_SIZE_IN_PIXEL);
	x2 = x1 + BLOCK_SIZE_IN_PIXEL;
	y1 = INDENT_IN_PIXELS + (j * BLOCK_SIZE_IN_PIXEL);
	y2 = y1 + BLOCK_SIZE_IN_PIXEL;

	Rectangle(hdc, x1, y1, x2, y2);
}


void drawField(HDC hdc) 
{
	int x, y;
	HBRUSH hBrushMoving = CreateSolidBrush(RGB(255, 105, 180));
	HBRUSH hBrushStaying = CreateSolidBrush(RGB(135, 206, 250));
	HBRUSH hBrushBoundary = CreateSolidBrush(RGB(255, 192, 203));
	HBRUSH holdBrush = SelectObject(hdc, hBrushBoundary);

	for (y = 0; y < PLAY_FIELD_HEIGHT_IN_BLOCKS; y++) 
	{
		for (x = 0; x < PLAY_FIELD_WIDTH_IN_BLOCKS; x++) 
		{
			if (playField[y][x] == MOVING_BLOCK) {
				SelectObject(hdc, hBrushMoving);
				drawBlock(hdc, x, y);
			}
			else if (playField[y][x] == STAYING_BLOCK) {
				SelectObject(hdc, hBrushStaying);
				drawBlock(hdc, x, y);
			}
			else if (playField[y][x] == BOUNDARY_BLOCK) {
				SelectObject(hdc, hBrushBoundary);
				drawBlock(hdc, x, y);
			}
		}
	}

	SelectObject(hdc, holdBrush);
	DeleteObject(hBrushMoving);
	DeleteObject(hBrushStaying);
	DeleteObject(hBrushBoundary);
}


void drawWithBuffer(HDC hdc)
{
	int bufferX = PLAY_FIELD_WIDTH_IN_BLOCKS * BLOCK_SIZE_IN_PIXEL + INDENT_IN_PIXELS * 2 + SUPPORT_FIELD_WIDTH_IN_PIXEL;
	int bufferY = PLAY_FIELD_HEIGHT_IN_BLOCKS * BLOCK_SIZE_IN_PIXEL + INDENT_IN_PIXELS * 2;

	HDC bdc = CreateCompatibleDC(hdc);
	HBITMAP bufferBitmap = CreateCompatibleBitmap(hdc, bufferX, bufferY);
	SelectObject(bdc, bufferBitmap);

	drawBackground(bdc);
	drawFieldBoundary(bdc);
	drawField(bdc);
	drawScoreField(bdc);
	BitBlt(hdc, 0, 0, bufferX, bufferY, bdc, 0, 0, SRCCOPY);

	DeleteDC(bdc);
	DeleteObject(bufferBitmap);
}