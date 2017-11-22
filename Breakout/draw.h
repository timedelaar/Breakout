#pragma once

void hideCursor();
void setCursorPosition(int xPos, int yPos);
void movePaddle(int *xPos, int direction);
void drawPaddle(int xPos);
void drawBricks(int **bricks, int rows, int columns);