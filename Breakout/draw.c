#include "draw.h"
#include <windows.h>
#include <math.h>
#include <GL\glut.h>

void drawRect(float x, float y, float width, float height) {
	glPushMatrix();
	glTranslatef(x, y, 0.0f);
	glBegin(GL_QUADS);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(width, 0.0f);
	glVertex2f(width, height);
	glVertex2f(0.0f, height);
	glEnd();
	glPopMatrix();
}

void drawCirc(float x, float y, float radius) {
	glPushMatrix();
	glTranslatef(x, y, 0.0f);  // Translate to (xPos, yPos)
							   // Use triangular segments to form a circle
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0.0f, 0.0f);       // Center of circle
	int numSegments = 50;
	GLfloat angle;
	for (int i = 0; i <= numSegments; i++) { // Last vertex same as first vertex
		angle = i * 2.0f * PI / numSegments;  // 360 deg for all segments
		glVertex2f(cos(angle) * radius, sin(angle) * radius);
	}
	glEnd();
	glPopMatrix();
}

void setColor(float r, float g, float b) {
	glColor3f(r, g, b);
}

void setBackgroundColor(float r, float g, float b) {
	glClearColor(r, g, b, 1.0f);
}