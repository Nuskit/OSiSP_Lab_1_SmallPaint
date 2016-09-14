#pragma once

#include "stdafx.h"
#include "Brush.h"

Brush::~Brush()
{
	if (hpen)
		DeletePen(hpen);
	if (fillBrush)
		DeleteBrush(fillBrush);
}

Brush::Brush():typePen(BS_SOLID),widthLine(1),colorLine(RGB(0,0,0)),hpen(NULL),fillBrush(NULL)
{
	reuseHPEN();
	setFillColor();
}

Brush::Brush(const Brush &newBrush)
{
	typePen = newBrush.typePen;
	widthLine = newBrush.widthLine;
	colorLine = newBrush.colorLine;
	colorFill = newBrush.colorFill;
	reuseHPEN();
	setFillColor(colorFill);
}

Brush::Brush(int Type_Pensil, int Size_line, COLORREF Color)
{
	setColor(Color);
	setTypePen(Type_Pensil);
	setWidthPen(Size_line);
	reuseHPEN();
}

void Brush::setColor(COLORREF New_Color)
{
	colorLine = New_Color;
	reuseHPEN();
}

COLORREF Brush::getColor()
{
	return colorLine;
}

void Brush::reuseHPEN()
{
	if (hpen)
		DeletePen(hpen);
	hpen = CreatePen(typePen, widthLine, colorLine);
}

void Brush::setTypePen(int New_Type)
{
	typePen = New_Type;
	reuseHPEN();
}

void Brush::setPen(HDC hdc)
{
	SelectPen(hdc, hpen);
}

void Brush::setBrush(HDC hdc)
{
	SelectBrush(hdc, fillBrush);
}

void Brush::setWidthPen(int value)
{
	widthLine = lineWidth.at(value);
	reuseHPEN();
}

int Brush::getWidthPen()
{
	return widthLine;
}

void Brush::setFillColor(COLORREF color)
{
	if (fillBrush)
		DeleteBrush(fillBrush);
	if (color==HOLLOW_BRUSH)
		fillBrush=(HBRUSH)GetStockObject(color);
	else
		fillBrush = CreateSolidBrush(color);
	colorFill = color;
}

COLORREF Brush::getFillColor()
{
	return colorFill;
}

HPEN Brush::getHPEN()
{
	return hpen;
}