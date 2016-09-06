#pragma once

#include "stdafx.h"
#include "All_Figure.h"

namespace Figures
{
  class Ellipses :public Figure
  {
    void deletePos();
  protected:
    int *x, *y;
    int size;
  public:
    Ellipses();

		~Ellipses();
    void SetSize(int);
    void SetStartPosition(int, int);
    void SetEndPosition(int, int);

    void DrawEllipses(HDC);

		const RECT& getRectZone();

    void setStartPosition(int x, int y) { SetStartPosition(x, y); }
    void setEndPosition(int x, int y) { SetEndPosition(x, y); }
		void drawFigure(HDC);

  };
}