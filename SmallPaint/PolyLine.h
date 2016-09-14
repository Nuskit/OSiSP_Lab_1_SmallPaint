#pragma once

#include "stdafx.h"
#include "AbstractDrawObject.h"

namespace Figures
{
  class PolyLine :public AbstractDrawObject
  {
  protected:
    vector<POINT> points;
  public:
		~PolyLine();
    void SetEndPosition(int, int);
		void drawPolyLine(HDC);
    void addNewPoint(int, int);

		const RECT& getRectZone();
		void drawFigure(HDC);
		void setStartPosition(int x, int y);
		void setEndPosition(int x, int y);
  };
}