#include "draw.h"
#include <windows.h>
#include <stdio.h>

void hideCursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

void setCursorPosition(int xPos, int yPos)
{
	COORD coord;

	coord.X = xPos;
	coord.Y = yPos;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void movePaddle(int *xPos, int direction) {
	*xPos += direction;
	setCursorPosition(*xPos - 1, 25);
	printf(" лллллл ");
}

void drawPaddle(int xPos) {
	setCursorPosition(xPos, 25);
	printf("лллллл");
}

void drawBricks(int** bricks, int rows, int columns) {
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if (bricks[i][j]) {
				setCursorPosition(j * 10 + 4, i * 2 + 3);
				printf("ллллллл");
			}
		}
	}
}