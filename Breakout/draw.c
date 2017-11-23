#include "draw.h"
#include <windows.h>
#include <math.h>
#include <GL\glut.h>

/* Draw a rectangle of given width and height.
** x and y are the coordinates of the upper-left corner.
*/
void drawRect(int x, int y, int width, int height) {
	glPushMatrix(); // Save current state of clipping area
	glTranslatef((float)x, (float)y, 0.0f); // Translate clipping area to (x, y)
	glBegin(GL_QUADS); // Set openGL to use quads instead of triangles
	glVertex2f(0.0f, 0.0f); // Draw upper-left point
	glVertex2f((float)width, 0.0f); // Draw upper-right point
	glVertex2f((float)width, (float)height); // Draw lower-right point
	glVertex2f(0.0f, (float)height); // Draw lower-left point
	glEnd(); // End drawing
	glPopMatrix(); // Load saved state of clipping area
}

/* Draw a circle of given radius.
** x and y are the coordinates of the center.
*/
void drawCirc(int x, int y, int radius) {
	glPushMatrix(); // Save state of clipping area
	glTranslatef((float)x, (float)y, 0.0f);  // Translate to (x, y)
	glBegin(GL_TRIANGLE_FAN); // Use triangular segments to form a circle
	glVertex2f(0.0f, 0.0f); // Center of circle
	int numSegments = 30; // Number of segments to use
	GLfloat angle;
	for (int i = 0; i <= numSegments; i++) { // Last vertex same as first vertex
		angle = i * 2.0f * PI / numSegments;  // 360 deg for all segments
		glVertex2f(cos(angle) * (float)radius, sin(angle) * (float)radius);
	}
	glEnd(); // End drawing
	glPopMatrix(); // Load saved state of clipping area
}

/* Set the color to use for drawing the next elements
*/
void setColor(float r, float g, float b) {
	glColor3f(r, g, b);
}

/* Set the color to use when clearing the screen (background color)
*/
void setBackgroundColor(float r, float g, float b) {
	glClearColor(r, g, b, 1.0f);
}