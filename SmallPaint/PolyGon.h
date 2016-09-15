#pragma once

#include "stdafx.h"
#include "PolyLine.h"

namespace Figures
{
	class PolyGon :public PolyLine
	{
		void drawPolyGon(HDC);

		const RECT& getRectZone();
		void drawFigure(HDC);
	};
}