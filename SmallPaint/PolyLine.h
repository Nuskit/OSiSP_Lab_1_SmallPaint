#pragma once

#include "stdafx.h"
#include "AbstractDrawObject.h"

namespace Figures
{
  class PolyLine :public AbstractDrawObject
  {
  protected:
    vector<POINT> points;
		void addPoint(int, int);
  public:
		~PolyLine();
		void drawPolyLine(HDC);

		const RECT& getRectZone();
		void drawFigure(HDC);
		void setStartPosition(int x, int y);
		void setEndPosition(int x, int y);
		const bool isContinueDraw();
  };
}