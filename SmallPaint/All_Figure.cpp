#pragma once
#include "stdafx.h"
#include "All_figure.h"
using namespace Figures;

Brush::~Brush()
{
	DeletePen(hpen);
}

Brush::Brush()
{
	Type_Pen = BS_SOLID;
	Size = 1;
	Current_Color = RGB(0, 255, 0);
}

Brush::Brush(int Type_Pensil, int Size_line, COLORREF Color)
{
	Current_Color = Color;
	Type_Pen = Type_Pensil;
	Size = Size_line;
	hpen = CreatePen(Type_Pen, Size, Color);
}

void Brush::SetColor(COLORREF New_Color)
{
	Current_Color = New_Color;
	Reuse_HPEN();
}

void Brush::Reuse_HPEN()
{
	DeletePen(hpen);
	hpen = CreatePen(Type_Pen, Size, Current_Color);
}

void Brush::SetTypePen(int New_Type)
{
	Type_Pen = New_Type;
	Reuse_HPEN();
}

void Brush::SetPen()
{
	SelectPen(hdc, hpen);
}

HPEN Brush::GetHPEN()
{
	return hpen;
}

const bool Figure::isInRectZone(const RECT& rect)
{
	return UnionRect(&rectZoneBuffer, &rect, &getRectZone());
}
