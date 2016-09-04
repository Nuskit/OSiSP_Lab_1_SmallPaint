#pragma once
#include "Ellipse.h"

class Chords :protected Ellipses, public virtual Figure
{
protected:
	int xEl1,yEl1,xEl2, yEl2;
	bool Set_Rectangle;
public:
	Chords() :Ellipses(){ xEl1 = yEl1 = xEl2 = yEl2 = 0; Set_Rectangle = false; }
	void SetEll(int, int, int, int);
	void DrawChords();
	void DrawChords(int, int);
	void DrawChords(int, int, int, int);
	void DrawChords(int, int, int, int, int, int, int, int);
	void AddNewPoint(int, int);


	void Draw_figure(int x, int y){ DrawChords(x, y); }

	void Draw_figure(){ DrawChords(); }
	void Set_Start_Position(int, int);
	void Set_End_Position(int, int);
	void Add_New_Point(int x, int y){ AddNewPoint(x, y); };
};