#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <GL\glut.h>
#include "draw.h"

#define ROWS 7
#define COLS 10

#define ESC 27

#define FPS 60

long speedTimer;
long currentTime;
int increaseTime = 60; // seconds
double speedIncrease = 0.2;

const char *title = "Breakout";
const int windowWidth = 960;
const int windowHeight = 480;

const int fieldX = 20;
const int fieldY = 20;
const int fieldWidth = 700;
const int fieldHeight = 440;

const int msPerFrame = 1000 / FPS;

int paddleWidth = 50;
const int paddleHeight = 10;
int paddleX = 0;
int paddleY;
int paddleSpeed = 15;

const int brickWidth = 50;
const int brickHeight = 20;
int bricks[ROWS][COLS];

int ballRadius = 5;
int ballSpeed = 2;
float directionX = 0.5;
float directionY = 0.5;
float ballX = 200;
float ballY = 200;

int score = 0;
int lives = 3;

void initializeGLUT(int argc, char **argv);
void init();
void paint();
void resize(GLsizei width, GLsizei height);
void gameMain(int value);
void keyHandler(int key, int x, int y);
void specialKeyHandler(int key, int x, int y);
void drawBricks();
void fillScoreboard();
int hitPaddle();
int hitBrick();
void moveBall();
void movePaddle(int direction);
int sign(int val);

/* Initialize GLUT function
** Initializes GLUT, sets defaults and registers callbacks.
*/
void initializeGLUT(int argc, char **argv) {
	glutInit(&argc, argv);                 // Initialize GLUT
	glutInitWindowSize(windowWidth, windowHeight);   // Set the window's initial width & height
	glutInitWindowPosition(100, 100); // Position the window's initial top-left corner
	glutInitDisplayMode(GLUT_DOUBLE); // Use double buffering for smoother animations
	glutCreateWindow(title); // Create a window with the given title
	glutDisplayFunc(paint); // Register display callback handler for window re-paint
	glutReshapeFunc(resize); // Register resize callback handler for window resize
	glutKeyboardFunc(keyHandler); // Register key press callback handler for normal keys (A - Z, ESC)
	glutSpecialFunc(specialKeyHandler); // Register key press callback handler for special keys (right, left, up, down, F..)
	glutTimerFunc(0, gameMain, 0); // Register timer function callback handler for game logic
	
}


/* Initialize function 
** Set initial state of game.
*/
void init() {
	int i, j;
	speedTimer = clock();
	setBackgroundColor(BLACK);
	paddleX = fieldWidth / 2 - paddleWidth;
	paddleY = fieldHeight - paddleHeight;
	srand(time(NULL));
	ballX = rand() % fieldWidth + fieldX;
	directionX = ((double)rand() / (double)RAND_MAX) * 2 - 1;
	directionY = 1;
	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < COLS; j++)
		{
			bricks[i][j] = rand() % 4 + 1;
		}
	}
}

/* Paint function
** Clear screen and redraw all entities.
*/
void paint() {
	glClear(GL_COLOR_BUFFER_BIT); // Clear screen

	/* Draw all objects here */
	
	drawBricks();
	setColor(RED);
	drawLineRect(fieldX - 5, fieldY - 5, windowWidth - fieldX - 10, windowHeight - fieldY - 10);
	drawLineRect(fieldX, fieldY, fieldWidth, fieldHeight); // Field edge
	drawLineRect(fieldX + fieldWidth + 5, fieldY, windowWidth - fieldX - fieldWidth - 25, fieldHeight); // Scoreboard
	fillScoreboard(); // Draw text in scoreboard
	drawRect(paddleX, paddleY, paddleWidth, paddleHeight); // Paddle
	setColor(BLUE);
	drawCirc(ballX, ballY, ballRadius); // Ball

	glutSwapBuffers(); // Swap front and back buffer
}

/* Resize function
** Resize viewport and clipping area to match new size.
*/
void resize(GLsizei width, GLsizei height) {
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, width, height, 0);
}

/* Game logic function
** Function is called periodically to execute game logic
** and redraw the screen.
*/
void gameMain(int value) {
	currentTime = clock(); // Get current clock
	if ((currentTime - speedTimer) / CLOCKS_PER_SEC > increaseTime) {
		speedTimer = currentTime;
		directionY += speedIncrease * sign(directionY);
	}
	moveBall();

	glutPostRedisplay(); // Redraw screen
	glutTimerFunc(msPerFrame, gameMain, 0); // Set timer to call this function again
}

/* Key handler function
** Called when a normal key is pressed.
** Normal keys include A-Z and ESC.
*/
void keyHandler(int key, int x, int y) {
	switch (key) {
	case ESC:
		exit(0);
		break;
	}
}

/* Special key handler function
** Called when a special key is pressed.
** Special keys include arrow keys.
*/
void specialKeyHandler(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_RIGHT:
		movePaddle(1);
		break;
	case GLUT_KEY_LEFT:
		movePaddle(-1);
		break;
	}
}


int main(int argc, char** argv) {
	initializeGLUT(argc, argv); // Initialize GLUT and register callbacks
	init(); // Initialize game variables
	glutMainLoop(); // Enter the event-processing loop
	return 0;
}
/* Draw Bricks with different colors by calling drawRect function
*/
void drawBricks()
{
	int i, j, brickX, brickY;
	for (i = 0; i < ROWS;i++)
	{
		for (j = 0; j < COLS; j++) {
			if (bricks[i][j] > 0) {
				switch (bricks[i][j]) {
				case 1:
					setColor(RED);
					break;
				case 2:
					setColor(GREEN);
					break;
				case 3:
					setColor(BLUE);
					break;
				case 4:
					setColor(YELLOW);
					break;
				}
				brickX = fieldX + j * (brickWidth + 15) + (i % 2) * (brickWidth + 15) / 2 + 20;
				brickY = fieldY + i * brickHeight + i * 5;
				drawRect(brickX, brickY + 1, brickWidth, brickHeight); // x+10 gives the vertical space between the bricks
			}
		}
	}

}

void fillScoreboard() {
	char temp[100];
	sprintf(temp, "Score: %d", score);
	drawStrokeText(fieldX + fieldWidth + 15, fieldY + 10, temp);
	sprintf(temp, "Lives: %d", lives);
	drawStrokeText(fieldX + fieldWidth + 15, fieldY + 30, temp);
}

int hitTest(int ballX, int ballY, int brickX, int brickY, int brickWidth, int brickHeight) {
	int circleDistanceX = abs(ballX - (brickX + brickWidth / 2));
	int circleDistanceY = abs(ballY - (brickY + brickHeight / 2));

	if (circleDistanceX > (brickWidth / 2 + ballRadius))
		return 0;
	if (circleDistanceY > (brickHeight / 2 + ballRadius))
		return 0;

	if (circleDistanceX <= (brickWidth / 2))
		return 1;
	if (circleDistanceY <= (brickHeight / 2))
		return 1;

	int cornerDistance_sq = (circleDistanceY - brickWidth / 2) ^ 2 +
		(circleDistanceY - brickHeight / 2) ^ 2;

	if (cornerDistance_sq <= (ballRadius ^ 2))
		return 1;

	return 0;
}

int hitPaddle() {
	if (hitTest(ballX + ballSpeed * directionX, ballY + ballSpeed * directionY, paddleX, paddleY, paddleWidth, paddleHeight)) {
		if (hitTest(ballX + ballSpeed * directionX, ballY, paddleX, paddleY, paddleWidth, paddleHeight)) {
			directionX = -directionX;
		}
		if (hitTest(ballX, ballY + ballSpeed * directionY, paddleX, paddleY, paddleWidth, paddleHeight)) {
			directionY = -directionY;
		}
		if (fabs(directionX) < 2.5) {
			int distance = ballX - (paddleX + paddleWidth / 2);
			directionX += distance / (double)paddleWidth;
		}
		return 1;
	}
	return 0;
}

int hitBrick() {
	int i, j, brickX, brickY;
	for (i = ROWS - 1; i >= 0; i--) {
		brickY = fieldY + i * brickHeight + i * 5 + 1;
		for (j = 0; j < COLS; j++) {
			brickX = fieldX + j * (brickWidth + 15) + (i % 2) * (brickWidth + 15) / 2 + 20;
			if (hitTest(ballX + ballSpeed * directionX, ballY + ballSpeed * directionY, brickX, brickY, brickWidth, brickHeight) && bricks[i][j] > 0) {
				bricks[i][j]--;
				if (hitTest(ballX + ballSpeed * directionX, ballY, brickX, brickY, brickWidth, brickHeight)) {
					directionX = -directionX;
				}
				if (hitTest(ballX, ballY + ballSpeed * directionY, brickX, brickY, brickWidth, brickHeight)) {
					directionY = -directionY;
				}
				return 1;
			}
		}
	}
	return 0;
}

/* Move ball in x and y direction.
** Checks if next move is outside of bounds. If that is the case
** add x and y to position ball edge at field edge and reverse direction.
** Else just move ball required amount.
*/
void moveBall() {
	if (hitBrick()) {
		score += 5;
		return;
	}
	if (hitPaddle()) {
		return;
	}

	if (ballX + (ballSpeed * directionX) - ballRadius < fieldX) {
		ballX -= fieldX - ballX - ballRadius;
		directionX = -directionX;
	}
	else if (ballX + (ballSpeed * directionX) + ballRadius > fieldX + fieldWidth) {
		ballX += fieldX + fieldWidth - ballX - ballRadius;
		directionX = -directionX;
	}
	else {
		ballX += ballSpeed * directionX;
	}

	if (ballY + (ballSpeed * directionY) - ballRadius < fieldY) {
		ballY -= fieldY - ballY - ballRadius;
		directionY = -directionY;
	}
	else if (ballY + (ballSpeed * directionY) + ballRadius > fieldY + fieldHeight) {
		if (lives == 1)
		{
			MessageBox(NULL, (LPCWSTR)L"Press OK!", (LPCWSTR)L"Game Over", MB_OK);
			exit(1);
		}
		else
		{
			// initialize ball position to over-paddle;
			// decrease life
			ballY = paddleY - paddleHeight;
			ballX = (paddleX + paddleWidth/2);
			lives--;
			char ar[100]=" ";
			itoa(lives, ar, 10);
			strcat(ar, " lives left!");

			MessageBox(0, (LPCWSTR)L"Press RETRY", (LPCWSTR)L"DEAD!", 5);

		}

		//ballY += fieldY + fieldHeight - ballY - ballRadius;
		directionY = -directionY;
	}
	else {
		ballY += ballSpeed * directionY;
	}

}

/* Move paddle in given direction. 1 for right, -1 for
** left. If next move is outside of bounds, place paddle
** on field edge.
*/
void movePaddle(int direction) {
	if (paddleX + (paddleSpeed * direction) < fieldX) {
		paddleX = fieldX;
	}
	else if (paddleX + paddleWidth + (paddleSpeed * direction) > fieldX + fieldWidth) {
		paddleX = fieldX + fieldWidth - paddleWidth;
	}
	else {
		paddleX += paddleSpeed * direction;
	}
}

int sign(int val) {
	return (0 < val) - (0 > val);
}