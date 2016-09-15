#include "stdafx.h"
#include "TextObject.h"
using namespace Figures;

void TextObject::drawText(HDC hdc)
{
	DrawText(hdc, text.data(), text.size(), &drawZone, NULL);
}

const RECT & TextObject::getRectZone()
{
	drawZone.right += rand() % 2 ? 1 : -1;
	rectZoneBuffer = drawZone;
	return rectZoneBuffer;
}

void TextObject::drawFigure(HDC hdc)
{
	//Rectangle(hdc, drawZone.left - brush->getWidthPen(), drawZone.top - brush->getWidthPen(), 
	//	drawZone.right + brush->getWidthPen(), drawZone.bottom + brush->getWidthPen());
	drawText(hdc);
}

void Figures::TextObject::setEndPosition(int x, int y)
{
	drawZone.right = x;
	drawZone.bottom = y;
}

void Figures::TextObject::setStartPosition(int x, int y)
{
	drawZone.left = drawZone.right = x;
	drawZone.bottom = drawZone.top = y;
}

void TextObject::addText(const int symvol)
{
	if (symvol == 8)
		deleteText();
	else
		text += symvol;
}

void TextObject::deleteText()
{
	if (text.size() > 0)
		text.pop_back();
}

const bool Figures::TextObject::isContinueDraw()
{
	return true;
}
