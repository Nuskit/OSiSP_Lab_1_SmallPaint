#pragma once

#include "stdafx.h"
#include "Chord.h"

namespace Figures
{
  class Pies :public Chords
  {
  public:
    Pies() :Chords() {  }
    void DrawPies();
    void DrawPies(int, int);
    void DrawPies(int, int, int, int);
    void DrawPies(int, int, int, int, int, int, int, int);

    void drawFigure() { DrawPies(); }
    void drawFigure(int x, int y) { DrawPies(x, y); }
  };
}