#pragma once

#include "stdafx.h"
#include "Ellipse.h"

namespace Figures
{
  class Chords :public Ellipses
  {
  protected:
    int xEl1, yEl1, xEl2, yEl2;
    bool Set_Rectangle;
  public:
    Chords() :Ellipses() { xEl1 = yEl1 = xEl2 = yEl2 = 0; Set_Rectangle = false; }
    void SetEll(int, int, int, int);
    void DrawChords();
    void DrawChords(int, int);
    void DrawChords(int, int, int, int);
    void DrawChords(int, int, int, int, int, int, int, int);
    void AddNewPoint(int, int);


    void drawFigure(int x, int y) { DrawChords(x, y); }

    void drawFigure() { DrawChords(); }
    void setStartPosition(int, int);
    void setEndPosition(int, int);
    void addNewPoint(int x, int y) { AddNewPoint(x, y); };
  };
}