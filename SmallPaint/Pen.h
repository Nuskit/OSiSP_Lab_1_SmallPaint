#pragma once

#include "stdafx.h"
#include "PolyLine.h"
using namespace Figures;

namespace Figures
{
	class Pen :public PolyLine
	{
	public:
		void addNewPoint(int, int);
		void setEndPosition(int, int);
	};
}