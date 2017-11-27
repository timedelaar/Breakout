#include "draw.h"
#include <windows.h>
#include <math.h>
#include <string.h>
#include <GL\glut.h>
#include <time.h>

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

/* Draw a unfilled rectangle of given width and height.
** x and y are the coordinates of the upper-left corner.
*/
void drawLineRect(int x, int y, int width, int height) {
	glPushMatrix(); // Save current state of clipping area
	glTranslatef((float)x, (float)y, 0.0f); // Translate clipping area to (x, y)
	glBegin(GL_LINES); // Set openGL to use lines
	glVertex2f(0.0f, 0.0f); // Draw upper-left point
	glVertex2f((float)width + 1, 0.0f); // Draw upper-right point
	glVertex2f((float)width, 0.0f); // Draw upper-right point
	glVertex2f((float)width, (float)height); // Draw lower-right point
	glVertex2f((float)width, (float)height); // Draw lower-right point
	glVertex2f(0.0f, (float)height); // Draw lower-left point
	glVertex2f(0.0f, (float)height); // Draw lower-left point
	glVertex2f(0.0f, 0.0f); // Draw upper-left point
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

/* Draw text at the give coordinates.
** x and y are the top left corner of the first character.
*/
void drawStrokeText(int x, int y, char *string) {
	int len = strlen(string);
	glPushMatrix();
	glTranslatef((float)x, (float)y + 10.0f, 0.0f);
	glScalef(0.1f, -0.1f, 0.0f);

	for (int i = 0; i < len; i++)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, string[i]);
	}
	glPopMatrix();
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


/* Draw Bricks with different colors by calling drawRect function
*/
void drawBricks()
{
	int x; // x coordinate of  starting point of a brick
	int y = 0; // y coordinate of starting point of a brick

	for (int i = 0; i < 7; i++)
	{
		// if statement gives the zig-zag pattern for bricks placement
		if (i % 2 == 0) x = 0;
		else x = 30;

		setColor(i%3+1, i%2, i%1); // sets different colors for lines

		for (; x < 900; x += 70)
			drawRect(x + 10, y + 2, 60, 20); // x+10 gives the vertical space between the bricks
		y += 20;
		y += 5; // horizontal space between lines 
	}

}