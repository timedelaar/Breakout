#include <windows.h>
#include <GL\glut.h>
#include "draw.h"

#define ESC 27

#define FPS 60

const char *title = "Breakout";
const int windowWidth = 960;
const int windowHeight = 480;
const int msPerFrame = 1000 / FPS;

int paddleWidth = 50;
int paddlePos = 200;
int paddleSpeed = 15;

int ballSpeedX = 2;
int ballSpeedY = 2;
int ballX = 200;
int ballY = 300;

void initializeGLUT(int argc, char **argv);
void init();
void paint();
void resize(GLsizei width, GLsizei height);
void gameMain(int value);
void keyHandler(int key, int x, int y);
void specialKeyHandler(int key, int x, int y);

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
}

/* Paint function
** Clear screen and redraw all entities.
*/
void paint() {
	glClear(GL_COLOR_BUFFER_BIT); // Clear screen

	/* Draw all objects here */
	setColor(RED);
	drawRect(paddlePos, 400, paddleWidth, 20);
	setColor(BLUE);
	drawCirc(ballX, ballY, 5);

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

	if (ballX + ballSpeedX > windowWidth || ballX + ballSpeedX < 0)
		ballSpeedX = -ballSpeedX;
	ballX += ballSpeedX;
	if (ballY + ballSpeedY > windowHeight || ballY + ballSpeedY < 0)
		ballSpeedY = -ballSpeedY;
	ballY += ballSpeedY;


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
		if (paddlePos + paddleWidth < windowWidth)
			paddlePos += paddleSpeed;
		break;
	case GLUT_KEY_LEFT:
		if (paddlePos > 0)
			paddlePos -= paddleSpeed;
		break;
	}
}


int main(int argc, char** argv) {
	initializeGLUT(argc, argv); // Initialize GLUT and register callbacks
	init(); // Initialize game variables
	glutMainLoop(); // Enter the event-processing loop
	return 0;
}