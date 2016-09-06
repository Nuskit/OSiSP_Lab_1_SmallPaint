#pragma once
#include "stdafx.h"
#include "Ellipse.h"
using namespace Figures;

Ellipses::Ellipses()
{
	size = 2;
	x = y = NULL;
	SetSize(size);
}

void Ellipses::DrawEllipses(HDC hdc)
{
	brush.SetPen();
	HGDIOBJ lastBrush=SelectObject(hdc, GetStockObject(HOLLOW_BRUSH));
	Ellipse(hdc, x[0], y[0], x[1], y[1]);
	SelectObject(hdc, lastBrush);
}

void Figures::Ellipses::drawFigure(HDC hdc)
{
	DrawEllipses(hdc);
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

Figures::Ellipses::~Ellipses()
{
	deletePos();
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

const RECT& Ellipses::getRectZone()
{
	rectZoneBuffer.bottom = (y[0] > y[1] ? y[0] : y[1]) + 2;
	rectZoneBuffer.left = (x[0] > x[1] ? x[1] : x[0]) - 2;
	rectZoneBuffer.right = (x[0] > x[1] ? x[0] : x[1]) + 2;
	rectZoneBuffer.top = (y[0] > y[1] ? y[1] : y[0]) - 2;
	return rectZoneBuffer;
}