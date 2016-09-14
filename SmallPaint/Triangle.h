#pragma once

#include "stdafx.h"
#include "PolyLine.h"

namespace Figures
{
  class Triangle :public PolyLine
  {
  public:
		Triangle();
    void SetPosition(int, int, int, int);
    void DrawTriangle(HDC);
    void AddNewPoint(int, int);

		void drawFigure(HDC);
    void setStartPosition(int, int);
    void setEndPosition(int, int);
    void addNewPoint(int x, int y) { AddNewPoint(x, y); };

  };
}