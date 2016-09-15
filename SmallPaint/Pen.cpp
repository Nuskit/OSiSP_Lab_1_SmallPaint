#include "stdafx.h"
#include "Pen.h"
using namespace Figures;

void Pen::addNewPoint(int x, int y)
{
	addPoint(x, y);
}

void Figures::Pen::setEndPosition(int x, int y)
{
	addNewPoint(x,y);
}
