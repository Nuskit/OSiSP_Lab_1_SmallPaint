#pragma once

#include "stdafx.h"
#include "All_Figure.h"

namespace Figures
{
  class PolyLine :public Figure
  {
    void deletePos();
  protected:
    int *x, *y;
    int size;
  public:
    PolyLine() {
      size = 0;
      x = y = NULL;
    }
    ~PolyLine() { deletePos(); }
    void SetSize(int);
    void SetStartPosition(int, int);
    void SetEndPosition(int, int);
    void DrawPolyLine();
    void DrawPolyLine(int, int);
    void AddNewPoint(int, int);

    void drawFigure(int x, int y) { DrawPolyLine(x, y); }
		const RECT& getRectZone() { return RECT(); }
    void drawFigure() { DrawPolyLine(); }
    void setStartPosition(int x, int y) { SetStartPosition(x, y); }
    void setEndPosition(int x, int y) { SetEndPosition(x, y); }
    void addNewPoint(int x, int y) { AddNewPoint(x, y); };
  };
}