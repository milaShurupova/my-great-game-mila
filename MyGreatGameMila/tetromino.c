#include "tetromino.h"

extern int score;
extern UINT speed;
extern enum gameStatus currentGameStatus;
extern int playField[PLAY_FIELD_HEIGHT_IN_BLOCKS][PLAY_FIELD_WIDTH_IN_BLOCKS];
extern int tetrominos[TETROMINO_TYPES][TETROMINO_HEIGHT][TETROMINO_WIDTH];
extern Tetromino currentTetromino;


void stopTetromino(Tetromino t) 
{
	int x, y;
	for (y = 0; y < TETROMINO_HEIGHT; y++) 
	{
		for (x = 0; x < TETROMINO_WIDTH; x++) 
		{
			if (playField[t.y + y][t.x + x] == MOVING_BLOCK) 
			{
				playField[t.y + y][t.x + x] = STAYING_BLOCK;
			}
		}
	}
}


BOOL noCollisionCheck(Tetromino t, int x, int y) 
{
	int i, j;
	for (i = 0; i < TETROMINO_HEIGHT; i++) 
	{
		for (j = 0; j < TETROMINO_WIDTH; j++) 
		{

			if (t.tetromino[i][j] == 0) 
			{
				continue;
			}

			int next_x = x + j;
			int next_y = y + i;

			if (playField[next_y][next_x] != EMPTY_BLOCK)
			{
				return FALSE;
			}
		}
	}
	return TRUE;
}


BOOL placeTetromino(Tetromino t) 
{
	if (noCollisionCheck(t, t.x, t.y) == FALSE) 
	{
		return FALSE;
	}

	int x, y;
	for (y = 0; y < TETROMINO_HEIGHT; y++) 
	{
		for (x = 0; x < TETROMINO_WIDTH; x++) 
		{
			if (t.tetromino[y][x] == MOVING_BLOCK) {
				playField[t.y + y][t.x + x] = MOVING_BLOCK;
			}
		}
	}
	return TRUE;
}


void removeTetromino(Tetromino t) 
{
	int x, y;
	for (y = 0; y < TETROMINO_HEIGHT; y++) 
	{
		for (x = 0; x < TETROMINO_HEIGHT; x++) 
		{
			if (playField[t.y + y][t.x + x] == MOVING_BLOCK) 
			{
				playField[t.y + y][t.x + x] = EMPTY_BLOCK;
			}
		}
	}
}


BOOL createTetromino(int x, int y, int type) 
{
	int i, j;
	Tetromino t;

	t.x = x;
	t.y = y;
	t.type = type;

	for (i = 0; i < TETROMINO_HEIGHT; i++) 
	{
		for (j = 0; j < TETROMINO_WIDTH; j++) 
		{
			t.tetromino[i][j] = tetrominos[type][i][j];
		}
	}

	currentTetromino = t;

	if (noCollisionCheck(t, x, y) == FALSE) 
	{
		return FALSE;
	}

	placeTetromino(currentTetromino);
	return TRUE;
}


BOOL moveTetromino(Tetromino t, MoveType type) 
{
	Tetromino next_t = t;
	switch (type) 
	{
		case MOVE_TO_LEFT:
			next_t.x = next_t.x - 1;
			break;
		case MOVE_TO_RIGHT:
			next_t.x = next_t.x + 1;
			break;
		case MOVE_TO_DOWN:
			next_t.y = next_t.y + 1;
			break;
	}

	removeTetromino(t);

	if (placeTetromino(next_t) == FALSE) 
	{
		placeTetromino(t);
		return FALSE;
	}

	currentTetromino = next_t;
	return TRUE;
}


void shiftLine(int n) 
{
	int i, j;
	for (i = n; i > 0; i--) 
	{
		for (j = 1; j < (PLAY_FIELD_WIDTH_IN_BLOCKS - 1); j++) 
		{
			playField[i][j] = playField[i - 1][j];
		}
	}

	for (j = 1; j < (PLAY_FIELD_WIDTH_IN_BLOCKS - 1); j++) 
	{
		playField[0][j] = EMPTY_BLOCK;
	}
}


BOOL isFullLine(int n) 
{
	int i;
	for (i = 1; i < (PLAY_FIELD_WIDTH_IN_BLOCKS - 1); i++) 
	{
		if (playField[n][i] == EMPTY_BLOCK) 
		{
			return FALSE;
		}
	}
	return TRUE;
}


int eraseLines()
{
	int result = 0;
	int i;

	for (i = 1; i < (PLAY_FIELD_HEIGHT_IN_BLOCKS - 1); i++)
	{
		if (isFullLine(i) == TRUE) 
		{
			shiftLine(i);
			result++;
		}
	}
	return result;
}


BOOL downTetromino()
{
	if (moveTetromino(currentTetromino, MOVE_TO_DOWN) == FALSE) 
	{
		stopTetromino(currentTetromino);
		score += eraseLines();

		if (createTetromino(PLAY_FIELD_WIDTH_IN_BLOCKS / 2, 0, rand() % TETROMINO_TYPES) == FALSE) 
		{
			currentGameStatus = GAME_OVER;
		}
		return FALSE;
	}
	return TRUE;
}


BOOL rotateTetromino(Tetromino t, RotateType type) 
{
	int i, j;
	Tetromino next_t = t;

	if (type == CLOCKWISE) 
	{
		for (i = 0; i < TETROMINO_HEIGHT; i++) 
		{
			for (j = 0; j < TETROMINO_WIDTH; j++) 
			{
				next_t.tetromino[i][j] = t.tetromino[TETROMINO_HEIGHT - 1 - j][i];
			}
		}
	}
	else 
	{
		for (i = 0; i < TETROMINO_HEIGHT; i++) 
		{
			for (j = 0; j < TETROMINO_WIDTH; j++) 
			{
				next_t.tetromino[i][j] = t.tetromino[j][TETROMINO_WIDTH - 1 - i];
			}
		}
	}

	removeTetromino(t);

	if (placeTetromino(next_t) == FALSE)
	{
		placeTetromino(t);
		return FALSE;
	}

	currentTetromino = next_t;
	return TRUE;
}