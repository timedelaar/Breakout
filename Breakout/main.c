#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <GL\glut.h>
#include "draw.h"

#define FPS 30

const int msPerFrame = 1000 / FPS;

void init();
void paint();
void resize(GLsizei width, GLsizei height);
void gameMain(int value);

void init() {
	setBackgroundColor(BLACK);
}

void paint() {
	glClear(GL_COLOR_BUFFER_BIT);

	/* Draw all objects here */
	setColor(RED);
	drawRect(100.0f, 100.0f, 50.0f, 20.0f);

	glutSwapBuffers();
}

void resize(GLsizei width, GLsizei height) {
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, width, height, 0);
}

void gameMain(int value) {
	/* Input game logic here */

	glutPostRedisplay();
	glutTimerFunc(msPerFrame, gameMain, 0);
}




int main(int argc, char** argv) {
	glutInit(&argc, argv);                 // Initialize GLUT
	glutInitWindowSize(960, 480);   // Set the window's initial width & height
	glutInitWindowPosition(100, 100); // Position the window's initial top-left corner
	glutInitDisplayMode(GLUT_DOUBLE); // Use double buffering for smoother animations
	glutCreateWindow("Breakout"); // Create a window with the given title
	glutDisplayFunc(paint); // Register display callback handler for window re-paint
	glutReshapeFunc(resize);
	glutTimerFunc(0, gameMain, 0);
	init();
	glutMainLoop();           // Enter the event-processing loop
	return 0;
}