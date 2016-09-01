#pragma once
#include "stdafx.h"
#include "Line.h"

void Lines::SetStartPosition(int x, int y)
{
	x1 = x;
	y1 = y;
	x2 = x;
	y2 = y;
}

void Lines::GetStartPosition(int &x, int &y)
{
	x = x1;
	y = y1;
}

void Lines::SetEndPosition(int x, int y)
{
	x2 = x;
	y2 = y;
}

void Lines::GetEndPosition(int &x, int &y)
{
	x = x2;
	y = y2;
}

void Lines::DrawLine()
{
	brush.SetPen();
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
}
void Lines::DrawLine(int next_x2, int next_y2)
{
	brush.SetPen();
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, next_x2, next_y2);
}


void Lines::DrawLine(int new_x1, int new_y1, int new_x2, int new_y2)
{
	brush.SetPen();
	MoveToEx(hdc, new_x1, new_y1, NULL);
	LineTo(hdc, new_x2, new_y2);
}