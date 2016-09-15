#pragma once
#include "stdafx.h"
#include "PolyLine.h"
using namespace Figures;

void PolyLine::addPoint(int new_x, int new_y)
{
	points.push_back(POINT{ new_x,new_y });
}

PolyLine::~PolyLine()
{
	points.clear();
}

void PolyLine::drawPolyLine(HDC hdc)
{
	Polyline(hdc, points.data(), points.size());
}

const RECT& PolyLine::getRectZone()
{
	if (points.size() > 0)
	{
		int size = points.size();
		rectZoneBuffer.bottom = (points[size-2].y > points[size-1].y ? points[size-2].y : points[size-1].y) + brush->getWidthPen();
		rectZoneBuffer.left = (points[size-2].x > points[size-1].x ? points[size-1].x : points[size-2].x) - brush->getWidthPen();
		rectZoneBuffer.right = (points[size-2].x > points[size-1].x ? points[size-2].x : points[size-1].x) + brush->getWidthPen();
		rectZoneBuffer.top = (points[size-2].y > points[size-1].y ? points[size-1].y : points[size-2].y) - brush->getWidthPen();
	}
	else
		rectZoneBuffer = RECT{ 0,0 };
	return rectZoneBuffer;
}

void PolyLine::drawFigure(HDC hdc)
{
	drawPolyLine(hdc);
}

void PolyLine::setStartPosition(int x, int y)
{
	if (points.size() == 0)
		addPoint(x, y);
	addPoint(x, y);
}

void PolyLine::setEndPosition(int x, int y)
{
	points.pop_back();
	addPoint(x, y);
}

const bool PolyLine::isContinueDraw()
{
	return true;
}
