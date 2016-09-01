#pragma once
#include "All_Figure.h"

class Ellipses :public virtual Figure
{
	void deletePos();
protected:
	int *x,*y;
	int size;
public:
	Ellipses();

	~Ellipses(){ deletePos(); }
	void SetSize(int);
	void SetStartPosition(int, int);
	void SetEndPosition(int, int);

	void DrawEllipses();
	void DrawEllipses(int, int);
	void DrawEllipses(int, int, int, int);

	void Draw_figure(int x, int y){ DrawEllipses(x, y); }

	void Set_Start_Position(int x, int y){ SetStartPosition(x, y); }
	void Set_End_Position(int x, int y){ SetEndPosition(x, y); }
	void Draw_figure(){ DrawEllipses(); }

};