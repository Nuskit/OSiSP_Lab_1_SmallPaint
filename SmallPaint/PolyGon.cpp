#include "stdafx.h"
#include "Polygon.h"
using namespace Figures;

void PolyGon::drawPolyGon(HDC hdc)
{
	Polygon(hdc, points.data(), points.size());
}

const RECT & Figures::PolyGon::getRectZone()
{
	if (points.size() > 0)
	{
		int size = points.size();
		//check last point with prelast
		//rectZoneBuffer.bottom = (points[size - 2].y > points[size - 1].y ? points[size - 2].y : points[size - 1].y) + brush->getWidthPen();
		//rectZoneBuffer.left = (points[size - 2].x > points[size - 1].x ? points[size - 1].x : points[size - 2].x) - brush->getWidthPen();
		//rectZoneBuffer.right = (points[size - 2].x > points[size - 1].x ? points[size - 2].x : points[size - 1].x) + brush->getWidthPen();
		//rectZoneBuffer.top = (points[size - 2].y > points[size - 1].y ? points[size - 1].y : points[size - 2].y) - brush->getWidthPen();

		//include in zone start point
		rectZoneBuffer.bottom = (rectZoneBuffer.bottom > points[0].y ? rectZoneBuffer.bottom : points[0].y) + brush->getWidthPen();
		rectZoneBuffer.left = (rectZoneBuffer.left > points[0].x ? points[0].x : rectZoneBuffer.left) - brush->getWidthPen();
		rectZoneBuffer.right = (rectZoneBuffer.right > points[0].x ? rectZoneBuffer.right : points[0].x) +brush->getWidthPen();
		rectZoneBuffer.top = (rectZoneBuffer.top > points[0].y ? points[0].y : rectZoneBuffer.top) -brush->getWidthPen();
	}
	return rectZoneBuffer;
}

void PolyGon::drawFigure(HDC hdc)
{
	drawPolyGon(hdc);
}
