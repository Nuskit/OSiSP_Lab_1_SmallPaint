#pragma once
#include "stdafx.h"
#include "Triangle.h"
using namespace Figures;

Triangle::Triangle():PolyLine()
{
}

//void Triangle::SetPosition(int new_x2, int new_y2, int new_x3, int new_y3)
//{
//	x[1] = new_x2;
//	y[1] = new_y2;
//	x[2] = new_x3;
//	y[2] = new_y3;
//}
//
//void Triangle::DrawTriangle(HDC hdc)
//{
//	brush->setPen(hdc);
//	MoveToEx(hdc, x[0], y[0], NULL);
//	LineTo(hdc, x[1], y[1]);
//	LineTo(hdc, x[2], y[2]);
//	LineTo(hdc, x[0], y[0]);
//}
//
//void Triangle::setEndPosition(int new_x2, int new_y2)
//{
//	x[1] = new_x2;
//	y[1] = new_y2;
//	x[2] = x[0] - (x[1] - x[0]);
//	y[2] = y[1];
//}
//
//void Figures::Triangle::drawFigure(HDC hdc)
//{
//	DrawTriangle(hdc);
//}
//
//void Triangle::setStartPosition(int new_x, int new_y)
//{
//	SetStartPosition(new_x, new_y);
//	x[2] = new_x;
//	y[2] = new_y;
//}
//
//void Triangle::AddNewPoint(int new_x, int new_y)
//{
//	x[0] = new_x;
//	y[0] = new_y;
//}