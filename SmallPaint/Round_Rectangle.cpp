#pragma once
#include "stdafx.h"
#include "Round_Rectangle.h"

using namespace Figures;

void RoundRectangles::DrawRoundRectangles(HDC hdc)
{
	brush->setPen(hdc);
	RoundRect(hdc, points[0].x, points[0].y, points[1].x, points[1].y, xEl, yEl);
}

RoundRectangles::RoundRectangles(): Rectangles(),xEl(50),yEl(50)
{
}

void RoundRectangles::SetEllipse(int new_xEl, int new_yEl)
{
	xEl = new_xEl;
	yEl = new_yEl;
}

void RoundRectangles::drawFigure(HDC hdc)
{
	DrawRoundRectangles(hdc);
}
