#pragma once

#include "stdafx.h"
#include "PolyLine.h"

namespace Figures
{
  class Triangle :public PolyLine
  {
  protected:
    void SetThirdPosition();
  public:
    Triangle() : PolyLine() {
      size = 3;
      SetSize(size);
    }
    void SetPosition(int, int, int, int);
    void DrawTriangle();
    void DrawTriangle(int, int, int, int);
    void DrawTriangle(int, int, int, int, int, int);
    void AddNewPoint(int, int);

    void drawFigure() { DrawTriangle(); }
    void setStartPosition(int, int);
    void setEndPosition(int, int);
    void addNewPoint(int x, int y) { AddNewPoint(x, y); };

  };
}