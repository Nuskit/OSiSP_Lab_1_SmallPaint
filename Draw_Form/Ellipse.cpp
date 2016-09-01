#pragma once
#include "stdafx.h"
#include "Ellipse.h"

Ellipses::Ellipses()
{
	size = 2;
	x = y = NULL;
	SetSize(size);
}


void Ellipses::DrawEllipses()
{
	brush.SetPen();
	Ellipse(hdc, x[0], y[0], x[1], y[1]);
}
void Ellipses::DrawEllipses(int new_x2, int new_y2)
{
	x[1] = new_x2;
	y[1] = new_y2;
	DrawEllipses();
}
void Ellipses::DrawEllipses(int new_x1, int new_y1, int new_x2, int new_y2)
{
	SetStartPosition(new_x1, new_y1);
	DrawEllipses();
}

void Ellipses::deletePos()
{
	if (x != NULL)
		delete[]x;
	x = NULL;
	if (y != NULL)
		delete[]y;
	y = NULL;
}

void Ellipses::SetSize(int new_size)
{
	size = new_size;
	deletePos();
	x = new int[size];
	y = new int[size];
}

void Ellipses::SetStartPosition(int new_x, int new_y)
{
	SetSize(2);
	x[0] = x[1] = new_x;
	y[0] = y[1] = new_y;
}

void Ellipses::SetEndPosition(int next_x, int next_y)
{
	x[size - 1] = next_x;
	y[size - 1] = next_y;
}