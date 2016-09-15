#pragma once

#include "stdafx.h"
#include "Pen.h"
using namespace Figures;

namespace Figures
{
	class ClearPen :public Pen
	{
	public:
		void setFillBrush(const Brush&);
	};
}