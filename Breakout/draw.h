#pragma once

#define RED 1.0f, 0.0f, 0.0f
#define GREEN 0.0f, 1.0f, 0.0f
#define BLUE 0.0f, 0.0f, 1.0f
#define YELLOW 1.0f, 1.0f, 0.0f
#define PURPLE 1.0f, 0.0f, 1.0f
#define WHITE 1.0f, 1.0f, 1.0f
#define BLACK 0.0f, 0.0f, 0.0f

#define PI 3.14159265f

void drawRect(float x, float y, float width, float height);
void drawCirc(float x, float y, float radius);
void setColor(float r, float g, float b);
void setBackgroundColor(float r, float g, float b);