#pragma once
#include "PolyLine.h"

class Triangle :protected PolyLine, public virtual Figure
{
protected:
	void SetThirdPosition();
public:
	Triangle() : PolyLine(){
		size = 3;
		SetSize(size);
	}
	void SetPosition(int, int, int, int);
	void DrawTriangle();
	void DrawTriangle(int, int, int, int);
	void DrawTriangle(int, int, int, int, int, int);
	void AddNewPoint(int, int);

	void Draw_figure(){ DrawTriangle(); }
	void Set_Start_Position(int, int);
	void Set_End_Position(int, int);
	void Add_New_Point(int x, int y){ AddNewPoint(x, y); };

};