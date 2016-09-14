#pragma once

#include "stdafx.h"
//#include "Singleton.h"
#include "AbstractDrawObject.h"
#include "DrawControl.h"


using namespace std;
using namespace Figures;

//May be change all metod as const and set exciptic
class FiguresControl// :public Templates::Singleton<FiguresControl>
{  
public:
	void setDrawHwnd(const HWND);
  VOID setFigure(int);
  VOID drawFigures(HDC,RECT,const HWND);
  VOID startDrawing(POINT);
  VOID endDrawing();
  VOID changeDraw(POINT);
  const bool isDrawing() const;
	const bool isMustRedraw();
  const RECT& RedrawZone() const;
  ~FiguresControl();
	void setWidthLine(int);
	void chooseLineColor();
	void chooseFillColor(const bool);
	void openEncFile(const char*);
	void saveEncFile(const char*,const HWND);
	void setMapMode(HDC, const int = MM_ISOTROPIC);

  static FiguresControl& Instance()
  {
    static FiguresControl theSingleInstance;
    return theSingleInstance;
  }

private:
	COLORREF getColor(COLORREF);
  void addDefaultFigures();
  FiguresControl();
  bool createNewFigure(POINT);
  bool saveFigure();
	void ChangeStartDrawZone();
	void ChangeEndDrawZone();

  bool isNowDrawing;
  ObjectFigure objectFigures;
	HENHMETAFILE metaFile;
  list <shared_ptr<AbstractDrawObject>> listFigures;
	shared_ptr<AbstractDrawObject> currentFigure;
  RECT drawZone[2];
	Brush brush;
	HWND hWnd;
};