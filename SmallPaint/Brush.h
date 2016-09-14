#pragma once

#include "stdafx.h"
#include <map>
#include "SmallPaint.h"

using namespace std;

class Brush
{
protected:
	typedef std::pair<int, int> widthPair;
	const map<int, int> lineWidth{ widthPair{ ID_WIDTHLINE_1PX ,1 }, widthPair{ID_WIDTHLINE_2PX, 2},
		widthPair{ID_WIDTHLINE_3PX, 3}, widthPair {ID_WIDTHLINE_4PX, 4} };
	int typePen, widthLine;
	COLORREF colorLine,colorFill;
	HPEN hpen;
	HBRUSH fillBrush;
	void reuseHPEN();
public:
	Brush();
	Brush(const Brush&);
	Brush(int, int, COLORREF);
	~Brush();
public:
	HPEN getHPEN();
	void setColor(COLORREF);
	COLORREF getColor();
	void setTypePen(int);
	void setPen(HDC);
	void setBrush(HDC);
	void setWidthPen(int);
	int getWidthPen();
	void setFillColor(COLORREF color = HOLLOW_BRUSH);
	COLORREF getFillColor();
};