#pragma once

#include "stdafx.h"
#include "AbstractDrawObject.h"

namespace Figures
{
  class Lines :public AbstractDrawObject
  {
  protected:
    int x1, y1, x2, y2;
  public:
    Lines() { x1 = y1 = x2 = y2 = 0; }
    void SetStartPosition(int, int);
    void GetStartPosition(int&, int &);
    void SetEndPosition(int, int);
    void GetEndPosition(int &, int &);
    void DrawLine(HDC);

    void drawFigure(HDC);
		const RECT& getRectZone();
    void setStartPosition(int x, int y) { SetStartPosition(x, y); }
    void setEndPosition(int x, int y) { SetEndPosition(x, y); }
  };
}