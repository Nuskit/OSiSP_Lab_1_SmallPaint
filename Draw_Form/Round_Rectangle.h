#pragma once
#include "Rectangle.h"

class RoundRectangles :protected Rectangles, public virtual Figure
{
protected:
	int xEl, yEl;
public:
	RoundRectangles() :Rectangles(){ xEl = yEl = 50; }
	void DrawRoundRectangles();
	void SetEllipse(int, int);
	void DrawRoundRectangles(int, int);
	void DrawRoundRectangles(int, int, int, int);
	void DrawRoundRectangles(int, int, int, int, int, int);

	void Draw_figure(){ DrawRoundRectangles(); }
	void Draw_figure(int x, int y){ DrawRoundRectangles(x, y); }
};