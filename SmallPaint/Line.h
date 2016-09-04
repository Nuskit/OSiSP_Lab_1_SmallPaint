#pragma once

#include "All_Figure.h"

class Lines :public virtual Figure
{
protected:
	int x1, y1, x2, y2;
public:
	Lines() { x1 = y1 = x2 = y2 = 0; }
	void SetStartPosition(int, int);
	void GetStartPosition(int&, int &);
	void SetEndPosition(int, int);
	void GetEndPosition(int &, int &);
	void DrawLine();
	void DrawLine(int, int);
	void DrawLine(int, int, int, int);

	void Draw_figure(int x, int y){ DrawLine(x, y); }

	void Draw_figure(){ DrawLine(); }
	void Set_Start_Position(int x, int y){ SetStartPosition(x, y); }
	void Set_End_Position(int x, int y){ SetEndPosition(x, y); }
};