#pragma once
#include "stdafx.h"
#include "Rectangle.h"
using namespace Figures;

Rectangles::Rectangles()
{
	size = 2;
	x = y = NULL;
	SetSize(size);
}

void Rectangles::drawRectangles(HDC hdc)
{
	brush.SetPen();
	HGDIOBJ lastBrush = SelectObject(hdc, GetStockObject(HOLLOW_BRUSH));
	Rectangle(hdc, x[0], y[0], x[1], y[1]);
	SelectObject(hdc, lastBrush);
}

void Figures::Rectangles::drawFigure(HDC hdc)
{
  drawRectangles(hdc);
}

  void Rectangles::setEndPosition(int new_x2, int new_y2)
{
	x[1] = new_x2;
	y[1] = new_y2;
}

	const RECT& Rectangles::getRectZone()
	{
		rectZoneBuffer.bottom = (y[0] > y[1] ? y[0] : y[1]) + 2;
		rectZoneBuffer.left = (x[0] > x[1] ? x[1] : x[0]) - 2;
		rectZoneBuffer.right = (x[0] > x[1] ? x[0] : x[1]) + 2;
		rectZoneBuffer.top = (y[0] > y[1] ? y[1] : y[0]) - 2;
		return rectZoneBuffer;
	}