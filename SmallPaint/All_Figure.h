#pragma once
#include "stdafx.h"
#include "SmallPaint.h"

class Brush
{
protected:
	int Type_Pen, Size;
	COLORREF Current_Color;
	HPEN hpen;
	void Reuse_HPEN();
public:
	Brush();
	Brush(int, int, COLORREF);
	~Brush();
	HPEN GetHPEN();
	void SetColor(COLORREF);
	void SetTypePen(int);
	void SetPen();
};


class Figure
{
protected:
	Brush brush;
public:
	virtual void Draw_figure(int, int)=0;

	virtual void Draw_figure()=0;
	virtual void Set_Start_Position(int, int)=0;
	virtual void Set_End_Position(int, int)=0;
	virtual void Add_New_Point(int, int){};
  virtual ~Figure() {};
};

class AbstractFigure
{
public:
	virtual Figure* Create()=0;
};

template <class C>
class FigureCreator : public AbstractFigure
{
public:
	Figure* Create() { return new C(); }
};


class ObjectFigure
{
protected:
	typedef std::map<int, AbstractFigure*> FactoryMap;
	FactoryMap Map_Figure;
	int Current_id;

public:
	~ObjectFigure(){ Map_Figure.clear(); }

	template<class C>
	void add(const int id)
	{
		FactoryMap::iterator Current_Position_it = Map_Figure.find(id);
		if (Current_Position_it == Map_Figure.end())
			Map_Figure[id] = new FigureCreator < C >() ;
	}

	Figure *create()
	{
		FactoryMap::iterator Current_Position_it = Map_Figure.find(Current_id);
		if (Current_Position_it != Map_Figure.end())
			return Current_Position_it->second->Create();
		else
			return NULL;
	}
	void SetFigure(int set_id)
	{
		Current_id = set_id;
	}
};