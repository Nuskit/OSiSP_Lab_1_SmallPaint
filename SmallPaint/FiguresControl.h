#pragma once

#include "stdafx.h"
//#include "Singleton.h"
#include "All_Figure.h"
#include "DrawControl.h"


using namespace std;
using namespace Figures;

//May be change all metod as const and set exciptic
class FiguresControl// :public Templates::Singleton<FiguresControl>
{  
public:
  VOID setFigure(int);
  VOID drawFigures(HDC,RECT);
  VOID startDrawing(POINT);
  VOID endDrawing();
  VOID changeDraw(POINT);
  const bool isDrawing() const;
	const bool isMustRedraw();
  const RECT& RedrawZone() const;
  ~FiguresControl();


  static FiguresControl& Instance()
  {
    static FiguresControl theSingleInstance;
    return theSingleInstance;
  }

private:
  void addDefaultFigures();
  FiguresControl();
  bool createNewFigure(POINT);
  bool saveFigure();
	void ChangeStartDrawZone();
	void ChangeEndDrawZone();

  bool isNowDrawing;
  ObjectFigure objectFigures;
  list <shared_ptr<Figure>> listFigures;
	shared_ptr<Figure> currentFigure;
  RECT drawZone[2];
};