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
    RoundRectangles() :Rectangles() { xEl = yEl = 50; }
    void DrawRoundRectangles();
    void SetEllipse(int, int);
    void DrawRoundRectangles(int, int);
    void DrawRoundRectangles(int, int, int, int);
    void DrawRoundRectangles(int, int, int, int, int, int);

    void drawFigure() { DrawRoundRectangles(); }
    void drawFigure(int x, int y) { DrawRoundRectangles(x, y); }
  };
}