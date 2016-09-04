#pragma once
#include "PolyLine.h"

class Rectangles :protected PolyLine,public virtual Figure
{
public:
	Rectangles();
	void DrawRectangles();
	void DrawRectangles(int, int);
	void DrawRectangles(int, int, int, int);

	void Draw_figure(){ DrawRectangles(); }
	void Draw_figure(int x,int y){ DrawRectangles(x, y); }
	void Set_End_Position(int, int);
};