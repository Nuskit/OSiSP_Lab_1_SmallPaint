#pragma once
#include "stdafx.h"
#include "Line.h"
using namespace Figures;

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

void Lines::DrawLine(HDC hdc)
{
	brush.SetPen();
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
}

void Figures::Lines::drawFigure(HDC hdc)
{
   DrawLine(hdc);
}

const RECT & Lines::getRectZone()
{
	rectZoneBuffer.bottom = (y1 > y2 ? y1 : y2) +2;
	rectZoneBuffer.left =		(x1 > x2 ? x2 : x1) -2;
	rectZoneBuffer.right =	(x1 > x2 ? x1 : x2) +2;
	rectZoneBuffer.top =		(y1 > y2 ? y2 : y1) -2;
	return rectZoneBuffer;
}
