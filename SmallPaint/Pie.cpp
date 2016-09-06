#pragma once
#include "stdafx.h"
#include "Pie.h"
using namespace Figures;

void Pies::DrawPies()
{
	brush.SetPen();
	Pie(hdc, x[0], y[0], x[1], y[1], xEl1, yEl1, xEl2, yEl2);
}
void Pies::DrawPies(int new_x2, int new_y2)
{
	x[1] = new_x2;
	y[1] = new_y2;
	DrawPies();
}
void Pies::DrawPies(int new_x1, int new_y1, int new_x2, int new_y2)
{
	SetStartPosition(new_x1, new_y1);
	DrawPies(new_x2,new_y2);
}

void Pies::DrawPies(int new_x1, int new_y1, int new_x2, int new_y2, int new_xEl1, int new_yEl1, int new_xEl2, int new_yEl2)
{
	SetStartPosition(new_x1, new_y1);
	SetEll(new_xEl1, new_yEl1, new_xEl2, new_yEl2);
	DrawPies(new_x2,new_y2);
}