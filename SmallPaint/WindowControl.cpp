#pragma once

#include "stdafx.h"
#include "WindowControl.h"

VOID WindowControl::createControlPanel(HWND hWnd) const
{
  createPanelFigures(hWnd);
}


HWND WindowControl::createGroupBox(const HWND hWnd, const char* name, int idButton=0, int positionX=0, int positionY=0) const
{
  RECT panelRect;
  GetClientRect(hWnd, &panelRect);
  return CreateWindow(
    "BUTTON",   // predefined class 
    name,       // button text 
    WS_VISIBLE | WS_CHILD | BS_GROUPBOX,  // styles 
    positionX,         // starting x position 
    positionY,         // starting y position 
    panelRect.right-positionX,        // button width 
    100,        // button height 
    hWnd,       // parent window 
    NULL,       // No menu 
    (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
    NULL);      // pointer not needed
}

VOID WindowControl::createPanelFigures(HWND hWnd) const
{
  createPanelFiguresParent(hWnd);
  createPanelFiguresButtons(hWnd);
}

HWND WindowControl::createPanelFiguresParent(HWND hWnd) const
{
  TCHAR nameGroupBox[MAX_LOADSTRING];
  LoadString((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), IDS_GroupFigures, nameGroupBox, MAX_LOADSTRING);
  return createGroupBox(hWnd, nameGroupBox);
}

VOID WindowControl::createPanelFiguresButtons(HWND hWnd) const
{
  std::list<int> allButtonsID{
    IDC_ID_BUTTON_Pen, IDC_ID_BUTTON_Line, IDC_ID_BUTTON_Rectangle,
    IDC_ID_BUTTON_Ellipse, IDC_ID_BUTTON_Text };
  TCHAR nameButton[MAX_LOADSTRING];
  int i = 0;
  for (auto &idButton : allButtonsID)
  {
    LoadString((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), idButton, nameButton, MAX_LOADSTRING);
    createButton(hWnd, nameButton, idButton, 10+((WIDTH_BUTTON+10) * i++), 20);
  }
}

HWND WindowControl::createButton(const HWND hWnd, const char* name, int idButton, int positionX, int positionY) const
{
  return CreateWindow(
    "BUTTON",   // predefined class 
    name,       // button text 
    WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // styles 
    // Size and position values are given explicitly, because 
    // the CW_USEDEFAULT constant gives zero values for buttons. 
    positionX,         // starting x position 
    positionY,         // starting y position 
    WIDTH_BUTTON,        // button width 
    HEIGH_BUTTON,        // button height 
    hWnd,       // parent window 
    (HMENU)idButton,       // No menu 
    (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
    NULL);      // pointer not needed
}
