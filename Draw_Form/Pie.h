#pragma once
#include "Chord.h"

class Pies :protected Chords, public virtual Figure
{
public:
	Pies() :Chords(){  }
	void DrawPies();
	void DrawPies(int, int);
	void DrawPies(int, int, int, int);
	void DrawPies(int, int, int, int, int, int, int, int);

	void Draw_figure(){ DrawPies(); }
	void Draw_figure(int x,int y){ DrawPies(x, y); }
};