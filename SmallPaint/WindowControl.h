#pragma once

#include "stdafx.h"
#include "SmallPaint.h"
#include "Singleton.h"

class WindowControl/*:public Templates::Singleton<WindowControl>*/
{
public:
  VOID createControlPanel(HWND) const;
	const char* openFile(HWND);
	const char* saveFile(HWND);

	static WindowControl& Instance()
	{
		static WindowControl theSingleInstance;
		return theSingleInstance;
	}

private:
	void workWithFile(OPENFILENAME&, HWND);
  HWND createGroupBox(const HWND, const char*, int, int, int) const;
  VOID createPanelFigures(HWND) const;
  HWND createPanelFiguresParent(HWND) const;
  VOID createPanelFiguresButtons(HWND) const;
  HWND createButton(const HWND, const char*, int, int, int) const;
};
