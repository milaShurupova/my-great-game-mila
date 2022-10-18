#include "helpers.h"

extern enum gameStatus currentGameStatus;
extern Tetromino currentTetromino;
extern int score;
extern UINT speed = 700;

extern int playField[PLAY_FIELD_HEIGHT_IN_BLOCKS][PLAY_FIELD_WIDTH_IN_BLOCKS];

//extern int tetrominos[TETROMINO_TYPES][TETROMINO_HEIGHT][TETROMINO_WIDTH];



void updateScore(int score, HWND hScore)
{
    wchar_t scoreString[15];
    swprintf_s(scoreString, 15, L"Score: %d", score);
    SetWindowTextW(hScore, scoreString);
}

void initializeGame(HWND hWnd)
{
    int i, j;
    currentGameStatus = PLAYING;
    score = 0;
    srand((unsigned)time(NULL));
    SetTimer(hWnd, speed, speed, NULL);

    for (i = 1; i < (PLAY_FIELD_HEIGHT_IN_BLOCKS - 1); i++)
    {
        for (j = 1; j < (PLAY_FIELD_WIDTH_IN_BLOCKS - 1); j++)
        {
            playField[i][j] = EMPTY_BLOCK;
        }
    }

    for (i = 0; i < PLAY_FIELD_HEIGHT_IN_BLOCKS; i++)
    {
        playField[i][0] = BOUNDARY_BLOCK;
        playField[i][PLAY_FIELD_WIDTH_IN_BLOCKS - 1] = BOUNDARY_BLOCK;
    }

    for (j = 0; j < PLAY_FIELD_WIDTH_IN_BLOCKS; j++)
    {
        playField[PLAY_FIELD_HEIGHT_IN_BLOCKS - 1][j] = BOUNDARY_BLOCK;
    }

    createTetromino((PLAY_FIELD_WIDTH_IN_BLOCKS / 2 - 2), 0, rand() % TETROMINO_TYPES);
}

