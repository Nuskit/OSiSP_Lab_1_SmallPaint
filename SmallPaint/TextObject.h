#pragma once

#include "stdafx.h"
#include "AbstractDrawObject.h"

namespace Figures
{
	class TextObject :public AbstractDrawObject
	{
	protected:
		std::string text;
		RECT drawZone;
	public:
		void drawText(HDC);

		const RECT& getRectZone();
		void drawFigure(HDC);
		void setEndPosition(int, int);
		void setStartPosition(int, int);
		void addText(const int );
		const bool isContinueDraw();
	private:
		void deleteText();
	};
}
