#pragma once
#include "stdafx.h"
#include "SmallPaint.h"
using namespace std;

namespace Figures
{
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
		RECT rectZoneBuffer;
  public:
    virtual void drawFigure(HDC) = 0;
    virtual void setStartPosition(int, int) = 0;
    virtual void setEndPosition(int, int) = 0;
		virtual const RECT& getRectZone() = 0;
		virtual const bool isInRectZone(const RECT&);
    virtual void addNewPoint(int, int) {};
    virtual ~Figure() {};
  };


  class AbstractFigure
  {
  public:
    virtual Figure* create() = 0;
  };

  template <typename T>
  class FigureCreator : public AbstractFigure
  {
  public:
    Figure* create() { return new T(); }
  };

  class ObjectFigure
  {
  protected:
    typedef std::map<int, std::unique_ptr<AbstractFigure>> FactoryMap;
    FactoryMap mapFigure;
    int idCurrentFigure;
  public:
    ~ObjectFigure() { mapFigure.clear(); }

    template<typename T>
    void add(const int id)
    {
      FactoryMap::iterator iteratorPosition = mapFigure.find(id);
      if (iteratorPosition == mapFigure.end())
        mapFigure[id] = unique_ptr<AbstractFigure>(new FigureCreator < T >());
    }

    Figure *create()
    {
      FactoryMap::iterator iteratorPosition = mapFigure.find(idCurrentFigure);
      if (iteratorPosition != mapFigure.end())
        return iteratorPosition->second->create();
      else
        return NULL;
    }

    void setFigure(int idNewFigure)
    {
      idCurrentFigure = idNewFigure;
    }
  };
}