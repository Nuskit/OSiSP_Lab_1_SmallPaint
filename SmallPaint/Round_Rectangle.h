#pragma once

#include "stdafx.h"
#include "Rectangle.h"

namespace Figures
{
	class RoundRectangles :public Rectangles
	{
	protected:
		int xEl, yEl;
	public:
		RoundRectangles();
		void DrawRoundRectangles(HDC);
		void SetEllipse(int, int);

		void drawFigure(HDC);
	};
}