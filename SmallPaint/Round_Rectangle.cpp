#pragma once
#include "stdafx.h"
#include "Round_Rectangle.h"

void RoundRectangles::DrawRoundRectangles()
{
	brush.SetPen();
	RoundRect(hdc, x[0], y[0], x[1], y[1], xEl, yEl);
}
void RoundRectangles::DrawRoundRectangles(int new_x2, int new_y2)
{
	x[1] = new_x2;
	y[1] = new_y2;
	DrawRoundRectangles();
}
void RoundRectangles::DrawRoundRectangles(int new_x1, int new_y1, int new_x2, int new_y2)
{
	SetStartPosition(new_x1, new_y1);
	DrawRoundRectangles(new_x2,new_y2);
}

void RoundRectangles::DrawRoundRectangles(int new_x1, int new_y1, int new_x2, int new_y2, int new_xEl, int new_yEl)
{
	SetStartPosition(new_x1, new_y1);
	SetEllipse(new_xEl, new_yEl);
	DrawRoundRectangles(new_x2,new_y2);
}

void RoundRectangles::SetEllipse(int new_xEl, int new_yEl)
{
	xEl = new_xEl;
	yEl = new_yEl;
}