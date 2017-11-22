#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>
#include "draw.h"

#define ROWS 4
#define COLUMNS 6
#define LEFT 75
#define RIGHT 77

const double FPS = 60;

int *bricks[ROWS];
int paddlePos;

void init();
void wait(clock_t *t);

int main() {
	clock_t t = (clock() * 1000 / CLOCKS_PER_SEC);
	int input;
	init();
	//hideCursor();
	drawBricks(bricks, ROWS, COLUMNS);
	drawPaddle(paddlePos);
	while (1) {
		//system("cls");
		if (kbhit()) {
			input = getch();
			switch (input) {
			case LEFT: 
				movePaddle(&paddlePos, -1);
				break;
			case RIGHT:
				movePaddle(&paddlePos, 1);
				break;
			}
		}
		wait(&t);
	}
	return 0;
}

// Initialize game variables
void init() {
	paddlePos = 40;
	for (int i = 0; i < ROWS; i++)
	{
		bricks[i] = (int*)malloc(COLUMNS * sizeof(int));
		for (int j = 0; j < COLUMNS; j++)
		{
			bricks[i][j] = 1;
		}
	}
}

// Limit frame rate
void wait(clock_t *t) {
	clock_t diff = (clock() * 1000 / CLOCKS_PER_SEC) - *t; // Calculate time elapsed in miliseconds
	if (*t < 1000 / FPS) { // If time elapsed is less than time per frame
		Sleep((1000 / FPS) - *t); // Sleep for remaining time
	}
	*t = (clock() * 1000 / CLOCKS_PER_SEC); // Set new time
}