#pragma once

#include "stdafx.h"
#include "FiguresControl.h"
#include "LibraryDrawObject.h"
#include "SmallPaint.h"

using namespace Figures;

VOID FiguresControl::setFigure(int idFigure)
{
  objectFigures.setFigure(idFigure);
}

VOID FiguresControl::drawFigures(HDC hdc,RECT rect)
{
	if (metaFile)
		PlayEnhMetaFile(hdc, metaFile, NULL);
	for (const auto &figureInList : listFigures)
		figureInList->drawFigure(hdc,rect);
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
		currentFigure->setFillBrush(brush);
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
	if (metaFile)
		DeleteObject(metaFile);
}

void FiguresControl::setWidthLine(int value)
{
	brush.setWidthPen(value);
}

void FiguresControl::chooseLineColor()
{
	brush.setColor(getColor(brush.getColor()));
}

void FiguresControl::chooseFillColor(const bool isHollow)
{
	if (!isHollow)
		brush.setFillColor();
	else
		brush.setFillColor(getColor(brush.getFillColor()));
}

void FiguresControl::openEncFile(const char *fullPath)
{
	if (metaFile)
		DeleteEnhMetaFile(metaFile);
	listFigures.clear();
	metaFile=GetEnhMetaFile(fullPath);
}

void FiguresControl::saveEncFile(const char *fullPath, const RECT& rect)
{
	HDC hdc=CreateEnhMetaFile(NULL, fullPath, NULL, NULL);

	if (metaFile)
	{
		PlayEnhMetaFile(hdc, metaFile, NULL);
	}

	for (auto figure : listFigures)
		figure->drawFigure(hdc);

	DeleteEnhMetaFile(CloseEnhMetaFile(hdc));
}

COLORREF FiguresControl::getColor(COLORREF color)
{
	CHOOSECOLOR cc;
	COLORREF crCustColors[16];
	cc.lStructSize = sizeof(CHOOSECOLOR);
	cc.hwndOwner = NULL;
	cc.hInstance = NULL;
	cc.rgbResult = color;
	cc.lpCustColors = crCustColors;
	cc.Flags = CC_RGBINIT | CC_FULLOPEN;
	cc.lCustData = 0L;
	cc.lpfnHook = NULL;
	cc.lpTemplateName = NULL;
	if (ChooseColor(&cc))
		color = cc.rgbResult;
	return color;
}

void FiguresControl::addDefaultFigures()
{
  objectFigures.add<Lines>(IDC_ID_BUTTON_Line);
  //objectFigures.add<Triangle>(IDC_ID_BUTTON_Lin);
  objectFigures.add<PolyLine>(IDC_ID_BUTTON_Polyline);
  objectFigures.add<Rectangles>(IDC_ID_BUTTON_Rectangle);
  //objectFigures.add<RoundRectangles>(ID_BUTTON_5);
  objectFigures.add<Ellipses>(IDC_ID_BUTTON_Ellipse);
  //objectFigures.add<Chords>(ID_BUTTON_7);
  //objectFigures.add<Pies>(ID_BUTTON_8);
}

FiguresControl::FiguresControl() :isNowDrawing(false), objectFigures(), metaFile(NULL),listFigures(), currentFigure(nullptr)
{
  addDefaultFigures();
}
