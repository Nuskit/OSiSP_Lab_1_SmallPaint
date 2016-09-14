#pragma once
#include "stdafx.h"
#include "PolyLine.h"
using namespace Figures;

PolyLine::~PolyLine()
{
	points.clear();
}

void PolyLine::SetEndPosition(int next_x, int next_y)
{
	addNewPoint(next_x, next_y);
}

void PolyLine::drawPolyLine(HDC hdc)
{
	Polyline(hdc, points.data(), points.size());
}

void PolyLine::addNewPoint(int new_x, int new_y)
{
	points.push_back(POINT{ new_x,new_y });
}

const RECT& PolyLine::getRectZone()
{
	if (points.size() > 0)
	{
		rectZoneBuffer = RECT{ points[0].x,points[0].y,points[0].x,points[0].y };
		for (int i = 1; i < points.size(); i++)
		{
			if (points[i].x<rectZoneBuffer.left)
				rectZoneBuffer.left = points[i].x;
			else if (points[i].x>rectZoneBuffer.right)
				rectZoneBuffer.right = points[i].x;
			if (points[i].y<rectZoneBuffer.top)
				rectZoneBuffer.top = points[i].y;
			else if (points[i].y>rectZoneBuffer.bottom)
				rectZoneBuffer.bottom = points[i].y;
		}
	}
	else
		rectZoneBuffer = RECT{ 0,0 };
	return rectZoneBuffer;
}

void Figures::PolyLine::drawFigure(HDC hdc)
{
	drawPolyLine(hdc);
}

void PolyLine::setStartPosition(int x, int y)
{
	addNewPoint(x, y);
}

void PolyLine::setEndPosition(int x, int y)
{
	addNewPoint(x, y);
}
