#pragma once
#include "stdafx.h"
#include "PolyLine.h"

void PolyLine::deletePos()
{
	if (x != NULL)
		delete[]x;
	x = NULL;
	if (y != NULL)
		delete[]y;
	y = NULL;
}

void PolyLine::SetSize(int new_size)
{
	size = new_size;
	deletePos();
	x = new int[size];
	y = new int[size];
}

void PolyLine::SetStartPosition(int new_x, int new_y)
{
	SetSize(2);
	x[0] =x[1]= new_x;
	y[0] =y[1]= new_y;
}

void PolyLine::SetEndPosition(int next_x, int next_y)
{
	x[size - 1] = next_x;
	y[size - 1] = next_y;
}

void PolyLine::DrawPolyLine()
{
	if (size > 0)
	{
		brush.SetPen();
		MoveToEx(hdc, x[0], y[0], NULL);
		for (int i = 0; i < size; i++)
			LineTo(hdc, x[i], y[i]);
		LineTo(hdc, x[0], y[0]);
	}
}

void PolyLine::DrawPolyLine(int next_x, int next_y)
{
	SetEndPosition(next_x, next_y);

	DrawPolyLine();
}

void PolyLine::AddNewPoint(int new_x, int new_y)
{
	int *old_x = new int[size];
	int *old_y = new int[size];
	for (int i = 0; i < size; i++)
	{
		old_x[i] = x[i];
		old_y[i] = y[i];
	}
	SetSize(++size);

	for (int i = 0; i < size - 1; i++)
	{
		x[i] = old_x[i];
		y[i] = old_y[i];
	}
	x[size - 1] = new_x;
	y[size - 1] = new_y;

	delete[]old_x;
	delete[]old_y;
}