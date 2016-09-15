#pragma once
#include "stdafx.h"
#include "Brush.h"

using namespace std;

class Brush;

namespace Figures
{
  class AbstractDrawObject
  {
  protected:
    shared_ptr<Brush> brush;
		RECT rectZoneBuffer;
  public:
		virtual void drawFigure(HDC) {};
		void drawFigure(HDC, const RECT&);
    virtual void setStartPosition(int, int) = 0;
    virtual void setEndPosition(int, int) = 0;
		virtual const RECT& getRectZone() = 0;
		const bool isInRectZone(const RECT&);
    virtual void addNewPoint(int, int) {};
    virtual ~AbstractDrawObject();
		void setFillBrush(const Brush&);
		virtual const bool isContinueDraw();
		AbstractDrawObject();
  };


  class AbstractFigure
  {
  public:
    virtual AbstractDrawObject* create() = 0;
  };

  template <typename T>
  class FigureCreator : public AbstractFigure
  {
  public:
    AbstractDrawObject* create() { return new T(); }
  };

  class ObjectFigure
  {
  protected:
    typedef map<int, unique_ptr<AbstractFigure>> FactoryMap;
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

    AbstractDrawObject *create()
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