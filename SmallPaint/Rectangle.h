#pragma once

#include "stdafx.h"
#include "PolyLine.h"

namespace Figures
{
  class Rectangles :public PolyLine
  {
  public:
    Rectangles();
    void drawRectangles(HDC);

		const RECT& getRectZone();
    void drawFigure(HDC);
    void setEndPosition(int, int);
  };
}