#pragma once
#include "stdafx.h"
#include "Rectangle.h"

Rectangles::Rectangles()
{
	size = 2;
	x = y = NULL;
	SetSize(size);
}

void Rectangles::DrawRectangles()
{
	brush.SetPen();
	Rectangle(hdc, x[0], y[0], x[1], y[1]);
}
void Rectangles::DrawRectangles(int new_x2, int new_y2)
{
	x[1] = new_x2;
	y[1] = new_y2;
	DrawRectangles();
}
void Rectangles::DrawRectangles(int new_x1, int new_y1, int new_x2, int new_y2)
{
	SetStartPosition(new_x1, new_y1);
	DrawRectangles(new_x2,new_y2);
}

void Rectangles::Set_End_Position(int new_x2, int new_y2)
{
	x[1] = new_x2;
	y[1] = new_y2;
}