#pragma once
#include "stdafx.h"
#include "Rectangle.h"
using namespace Figures;

Rectangles::Rectangles()
{
	points.resize(2);
}

void Rectangles::drawRectangles(HDC hdc)
{
	Rectangle(hdc, points[0].x, points[0].y, points[1].x, points[1].y);
}

void Rectangles::drawFigure(HDC hdc)
{
  drawRectangles(hdc);
}

void Rectangles::setEndPosition(int new_x2, int new_y2)
{
	points[1].x = new_x2;
	points[1].y = new_y2;
}

void Rectangles::setStartPosition(int x, int y)
{
	points[0].x= points[1].x = x;
	points[0].y= points[1].y = y;
}

const RECT& Rectangles::getRectZone()
{
	rectZoneBuffer.bottom = (points[0].y > points[1].y ? points[0].y : points[1].y) + brush->getWidthPen();
	rectZoneBuffer.left = (points[0].x > points[1].x ? points[1].x : points[0].x) - brush->getWidthPen();
	rectZoneBuffer.right = (points[0].x > points[1].x ? points[0].x : points[1].x) + brush->getWidthPen();
	rectZoneBuffer.top = (points[0].y > points[1].y ? points[1].y : points[0].y) - brush->getWidthPen();
	return rectZoneBuffer;
}