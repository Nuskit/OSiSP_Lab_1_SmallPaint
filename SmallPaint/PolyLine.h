#pragma once

#include "All_Figure.h"

class PolyLine :public virtual Figure
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
	~PolyLine(){ deletePos(); }
	void SetSize(int);
	void SetStartPosition(int, int);
	void SetEndPosition(int, int);
	void DrawPolyLine();
	void DrawPolyLine(int,int);
	void AddNewPoint(int, int);

	void Draw_figure(int x, int y){ DrawPolyLine(x, y); }

	void Draw_figure(){ DrawPolyLine(); }
	void Set_Start_Position(int x, int y){ SetStartPosition(x, y); }
	void Set_End_Position(int x, int y){ SetEndPosition(x, y); }
	void Add_New_Point(int x, int y){ AddNewPoint(x, y); };
};