#pragma once

/* Define color macros for easy use */
#define RED 1.0f, 0.0f, 0.0f
#define GREEN 0.0f, 1.0f, 0.0f
#define BLUE 0.0f, 0.0f, 1.0f
#define YELLOW 1.0f, 1.0f, 0.0f
#define PURPLE 1.0f, 0.0f, 1.0f
#define WHITE 1.0f, 1.0f, 1.0f
#define BLACK 0.0f, 0.0f, 0.0f

/* Define PI for use by drawCirc */
#define PI 3.14159265f

void drawRect(int x, int y, int width, int height);
void drawLineRect(int x, int y, int width, int height);
void drawCirc(int x, int y, int radius);
void drawStrokeText(int x, int y, char* string);
void setColor(float r, float g, float b);
void setBackgroundColor(float r, float g, float b);
void drawBricks();