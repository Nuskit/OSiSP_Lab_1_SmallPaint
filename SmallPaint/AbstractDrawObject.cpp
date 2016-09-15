#pragma once
#include "stdafx.h"
#include "AbstractDrawObject.h"
using namespace Figures;

void Figures::AbstractDrawObject::drawFigure(HDC hdc, const RECT &rect)
{
	if (isInRectZone(rect))
	{
		setBrush(hdc);
		drawFigure(hdc);
	}
}

const bool AbstractDrawObject::isInRectZone(const RECT& rect)
{
	return UnionRect(&rectZoneBuffer, &rect, &getRectZone());
}

AbstractDrawObject::~AbstractDrawObject()
{
}

void AbstractDrawObject::setFillBrush(const Brush &_brush)
{
	brush.reset(new Brush(_brush));
}

const bool Figures::AbstractDrawObject::isContinueDraw()
{
	return false;
}

void AbstractDrawObject::setBrush(HDC hdc)
{
	brush->setPen(hdc);
	brush->setBrush(hdc);
}

AbstractDrawObject::AbstractDrawObject():brush(new Brush())
{
}