#include "stdafx.h"
#include "ClearPen.h"
using namespace Figures;

void Figures::ClearPen::setFillBrush(const Brush & _brush)
{
	Brush *temp=new Brush(_brush);
	temp->setColor(RGB(255,255,255));
	temp->setWidthPen(ID_WIDTHLINE_8PX);
	brush.reset(temp);
}
