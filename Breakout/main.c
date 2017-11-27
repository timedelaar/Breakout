#include <string.h>
#include <stdio.h>
#include <windows.h>
#include <GL\glut.h>
#include "draw.h"

#define ESC 27

#define FPS 60

const char *title = "Breakout";
const int windowWidth = 960;
const int windowHeight = 480;

const int fieldX = 20;
const int fieldY = 20;
const int fieldWidth = 700;
const int fieldHeight = 440;

const int msPerFrame = 1000 / FPS;

int paddleWidth = 50;
int paddlePos = 200;
int paddleSpeed = 15;

int ballRadius = 5;
int ballSpeed = 4;
float directionX = 0.5;
float directionY = 0.5;
int ballX = 200;
int ballY = 300;

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
void moveBall();
void movePaddle(int direction);

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
	setBackgroundColor(BLACK);
	/* TODO: Start with random ball position and direction? */
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
	drawRect(paddlePos, 400, paddleWidth, 20); // Paddle
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
	/* Input game logic here */

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
	int fieldX=20; // x coordinate of  starting point of a brick
	int fieldY=20; // y coordinate of starting point of a brick

	for (int i = 0; i < 7;i++)
	{
		// if statement gives the zig-zag pattern for bricks placement
		if (i % 2 == 0) fieldX = 0;
		else fieldX = 20;

		setColor(i % 3 + 1, i % 2, i % 1); // sets different colors for lines

		for (; fieldX < 700; fieldX += 70)
			drawRect((fieldX )+ 20, (fieldY) +2, 50, 20); // x+10 gives the vertical space between the bricks
		fieldY += 20;
	fieldX += 5; // horizontal space between lines 
	}

}
void fillScoreboard() {
	char temp[100];
	sprintf(temp, "Score: %d", score);
	drawStrokeText(fieldX + fieldWidth + 15, fieldY + 10, temp);
	sprintf(temp, "Lives: %d", lives);
	drawStrokeText(fieldX + fieldWidth + 15, fieldY + 30, temp);
}

/* Move ball in x and y direction.
** Checks if next move is outside of bounds. If that is the case
** add x and y to position ball edge at field edge and reverse direction.
** Else just move ball required amount.
*/
void moveBall() {
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
		/* TODO: Bottom edge lose life and insert new ball */
		ballY += fieldY + fieldHeight - ballY - ballRadius;
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
	if (paddlePos + (paddleSpeed * direction) < fieldX) {
		paddlePos = fieldX;
	}
	else if (paddlePos + paddleWidth + (paddleSpeed * direction) > fieldX + fieldWidth) {
		paddlePos = fieldX + fieldWidth - paddleWidth;
	}
	else {
		paddlePos += paddleSpeed * direction;
	}
}