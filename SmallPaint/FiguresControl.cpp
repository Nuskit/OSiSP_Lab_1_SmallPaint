#pragma once

#include "stdafx.h"
#include "FiguresControl.h"
#include "Arr_Fig.h"

using namespace Figures;

VOID FiguresControl::setFigure(int idFigure)
{
  objectFigures.setFigure(idFigure);
}

VOID FiguresControl::drawFigures(HDC hdc,RECT rect)
{
	for (const auto &figureInList : listFigures)
	{
		if (figureInList->isInRectZone(rect))
			figureInList->drawFigure(hdc);
	}
	if (isDrawing())
		ChangeStartDrawZone();
}

VOID FiguresControl::startDrawing(POINT position)
{
  isNowDrawing = createNewFigure(position);
	ChangeStartDrawZone();
}

void FiguresControl::ChangeStartDrawZone()
{
	if (currentFigure != NULL)
		drawZone[0] = currentFigure->getRectZone();
}

void FiguresControl::ChangeEndDrawZone()
{
	if (currentFigure != NULL)
		drawZone[1] = currentFigure->getRectZone();
}

VOID FiguresControl::endDrawing()
{
  isNowDrawing = saveFigure();
}

VOID FiguresControl::changeDraw(POINT position)
{
  currentFigure->setEndPosition(position.x, position.y);
}

bool FiguresControl::createNewFigure(POINT position)
{
  currentFigure.reset(objectFigures.create());
  if (currentFigure != NULL)
  {
    currentFigure->setStartPosition(position.x, position.y);
		listFigures.push_back(currentFigure);
  }
  return currentFigure == NULL ? false : true;
}

bool FiguresControl::saveFigure()
{
  currentFigure = NULL;
  return false;
}

const bool FiguresControl::isDrawing() const
{
  return isNowDrawing;
}

const bool FiguresControl::isMustRedraw()
{
	ChangeEndDrawZone();
	return !EqualRect(&drawZone[0], &drawZone[1]); 
}

const RECT& FiguresControl::RedrawZone() const
{
  static RECT rect;
  UnionRect(&rect, &drawZone[0], &drawZone[1]);
  return rect;
}

FiguresControl::~FiguresControl()
{
  listFigures.clear();
}

void FiguresControl::addDefaultFigures()
{
  objectFigures.add<Lines>(IDC_ID_BUTTON_Line);
  //objectFigures.add<Triangle>(IDC_ID_BUTTON_Lin);
  //objectFigures.add<PolyLine>(ID_BUTTON_3);
  objectFigures.add<Rectangles>(IDC_ID_BUTTON_Rectangle);
  //objectFigures.add<RoundRectangles>(ID_BUTTON_5);
  objectFigures.add<Ellipses>(IDC_ID_BUTTON_Ellipse);
  //objectFigures.add<Chords>(ID_BUTTON_7);
  //objectFigures.add<Pies>(ID_BUTTON_8);
}

FiguresControl::FiguresControl() :isNowDrawing(false), objectFigures(), listFigures(), currentFigure(nullptr)
{
  addDefaultFigures();
}
