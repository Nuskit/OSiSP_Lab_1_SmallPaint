// SmallPaint.cpp: ���������� ����� ����� ��� ����������.
//

#include "stdafx.h"
#include <list>
#include "SmallPaint.h"
#include "LibraryDrawObject.h"
#include "WindowControl.h"
#include "FiguresControl.h"

enum
{
  HEIGH_CONTROL_PANEL = 100
};

POINT getCurrentCursorPosisiton(HWND);
void PaintTimerRedraw(HWND);

using namespace std;
using namespace Figures;

// ���������� ����������:
HINSTANCE hInst;								// ������� ���������
TCHAR szTitle[MAX_LOADSTRING];					// ����� ������ ���������
TCHAR szWindowClass[MAX_LOADSTRING];			// ��� ������ �������� ����
TCHAR szWindowClassPaint[MAX_LOADSTRING];
TCHAR szWindowClassFigures[MAX_LOADSTRING];

// ��������� ���������� �������, ���������� � ���� ������ ����:
ATOM				MyRegisterClass(HINSTANCE hInstance);
ATOM        RegisterChildClass(WNDCLASSEX);
ATOM        RegisterControlPanel(WNDCLASSEX);
ATOM        RegisterPaintZone(WNDCLASSEX);

BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
VOID createControlPanels(HWND,HINSTANCE);
VOID workWithPanelCommand(HWND ,WPARAM);


int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
  _In_opt_ HINSTANCE hPrevInstance,
  _In_ LPTSTR    lpCmdLine,
  _In_ int       nCmdShow)
{
  UNREFERENCED_PARAMETER(hPrevInstance);
  UNREFERENCED_PARAMETER(lpCmdLine);

  // TODO: ���������� ��� �����.
  MSG msg;
  HACCEL hAccelTable;

  // ������������� ���������� �����
  LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
  LoadString(hInstance, IDC_SmallPaint, szWindowClass, MAX_LOADSTRING);
  MyRegisterClass(hInstance);

  // ��������� ������������� ����������:
  if (!InitInstance(hInstance, nCmdShow))
  {
    return FALSE;
  }

  hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SmallPaint));

  // ���� ��������� ���������:
  while (GetMessage(&msg, NULL, 0, 0))
  {
    if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
    {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }

  return (int)msg.wParam;
}



//
//  �������: MyRegisterClass()
//
//  ����������: ������������ ����� ����.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
  WNDCLASSEX wcex;

  wcex.cbSize = sizeof(WNDCLASSEX);

  wcex.style = CS_HREDRAW | CS_VREDRAW;
  wcex.lpfnWndProc = WndProc;
  wcex.cbClsExtra = 0;
  wcex.cbWndExtra = 0;
  wcex.hInstance = hInstance;
  wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SmallPaint));
  wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = NULL;// (HBRUSH)(COLOR_WINDOW + 1);
  wcex.lpszMenuName = MAKEINTRESOURCE(IDC_SmallPaint);
  wcex.lpszClassName = szWindowClass;
  wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

  RegisterChildClass(wcex);
  return RegisterClassEx(&wcex);
}



//
//   �������: InitInstance(HINSTANCE, int)
//
//   ����������: ��������� ��������� ���������� � ������� ������� ����.
//
//   �����������:
//
//        � ������ ������� ���������� ���������� ����������� � ���������� ����������, � �����
//        ��������� � ��������� �� ����� ������� ���� ���������.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
  hInst = hInstance; // ��������� ���������� ���������� � ���������� ����������

  HWND hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

  if (!hWnd)
  {
    return FALSE;
  }

  ShowWindow(hWnd, nCmdShow);
  UpdateWindow(hWnd);

  return TRUE;
}

//
//  �������: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ����������:  ������������ ��������� � ������� ����.
//
//  WM_COMMAND	- ��������� ���� ����������
//  WM_PAINT	-��������� ������� ����
//  WM_DESTROY	 - ������ ��������� � ������ � ���������.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  switch (message)
  {
  case WM_CREATE:
  {
    RECT windowRect;
    GetClientRect(hWnd, &windowRect);
    CreateWindow(szWindowClassFigures, NULL, WS_CHILDWINDOW | WS_VISIBLE,
      windowRect.left, 0, windowRect.right, HEIGH_CONTROL_PANEL, hWnd, NULL,
      (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), 
      NULL);

    CreateWindow(szWindowClassPaint, NULL, WS_CHILDWINDOW | WS_VISIBLE,
      windowRect.left, HEIGH_CONTROL_PANEL, windowRect.right, windowRect.bottom-HEIGH_CONTROL_PANEL, hWnd, NULL,
      (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
      NULL);
  }
  break;
  case WM_DESTROY:
  {
    PostQuitMessage(0);
  }
    break;
  break;
  case WM_KEYDOWN:
    switch (wParam)
    {
    case VK_ESCAPE:
      SendMessage(hWnd, WM_CLOSE, 0, 0);
      break;
    case VK_BACK:
      //if (!List_Figure.empty() && !Cur_Drawing)
      //{
      //  List_Figure.pop_back();
      //  Clear_Holst();
      //}
      break;
    }
    break;

	case WM_COMMAND:
		workWithPanelCommand(hWnd,wParam);
		break;
  default:
    return DefWindowProc(hWnd, message, wParam, lParam);
  }
  return 0;
}

LRESULT CALLBACK WndChildControlPanelProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  switch (message)
  {
  case WM_CREATE:
  {
    WindowControl::Instance().createControlPanel(hWnd);
  }
  break;
  case WM_PAINT:
  {
    PAINTSTRUCT ps;
    HDC hdc;
    hdc = BeginPaint(hWnd, &ps);
    EndPaint(hWnd, &ps);
  }
    break;
  case WM_COMMAND:
    switch (wParam)
    {
    default:
      FiguresControl::Instance().setFigure(wParam);
      SetFocus(GetParent(hWnd));
      break;
    }
    break;
  default:
    return DefWindowProc(hWnd, message, wParam, lParam);
  }
  return 0;
}

LRESULT CALLBACK WndChildPaintZoneProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  switch (message)
  {
  case WM_PAINT:
  {
    PAINTSTRUCT ps;
    HDC hdc,hdcOld;
    hdc = BeginPaint(hWnd, &ps);
		hdcOld = CreateCompatibleDC(hdc);
		RECT rect;
		GetClientRect(hWnd, &rect);
		HBITMAP hBitmap = CreateCompatibleBitmap(hdc, rect.right-rect.left, rect.bottom-rect.top);
		SelectObject(hdcOld, hBitmap);

		SetBkMode(hdcOld, TRANSPARENT);
		FillRect(hdcOld, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW+1));
    FiguresControl::Instance().drawFigures(hdcOld,ps.rcPaint);
		BitBlt(hdc, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, hdcOld, 0, 0, SRCCOPY);
		SelectObject(hdc, hdcOld);
		DeleteDC(hdcOld);
		DeleteObject(hBitmap);
		EndPaint(hWnd, &ps);
  }
  break;
	case WM_ERASEBKGND:
		return 1;
  case WM_SETFOCUS:
  {
    SetFocus(GetParent(hWnd));
  }
  break;
  case WM_LBUTTONDOWN:
  {
    FiguresControl::Instance().startDrawing(getCurrentCursorPosisiton(hWnd));
		if (FiguresControl::Instance().isDrawing())
		{
			SetCapture(hWnd);
			SetCursor(LoadCursor(NULL,IDC_CROSS));
			SetTimer(hWnd, IDC_TIMER_PAINT, TIMER_PAINT_RATE, NULL);
		}
  }
  break;
  case WM_LBUTTONUP:
  {
    if (FiguresControl::Instance().isDrawing())
    {
      ReleaseCapture();
			KillTimer(hWnd, IDC_TIMER_PAINT);
			PaintTimerRedraw(hWnd);
			FiguresControl::Instance().endDrawing();
    }
  }
  break;
  case WM_MOUSEMOVE:
    if (FiguresControl::Instance().isDrawing())
      FiguresControl::Instance().changeDraw(getCurrentCursorPosisiton(hWnd));
    break;
  case WM_TIMER:
		PaintTimerRedraw(hWnd);
    break;

  default:
    return DefWindowProc(hWnd, message, wParam, lParam);
  }
  return 0;
}

POINT getCurrentCursorPosisiton(HWND hWnd)
{
  POINT  pt;
  GetCursorPos(&pt);
  ScreenToClient(hWnd, &pt);
  return pt;
}

void  AddFigire_in_map()
{
  //ObjectFigures.add<Lines>(ID_BUTTON_1);
  //ObjectFigures.add<Triangle>(ID_BUTTON_2);
  //ObjectFigures.add<PolyLine>(ID_BUTTON_3);
  //ObjectFigures.add<Rectangles>(ID_BUTTON_4);
  //ObjectFigures.add<RoundRectangles>(ID_BUTTON_5);
  //ObjectFigures.add<Ellipses>(ID_BUTTON_6);
  //ObjectFigures.add<Chords>(ID_BUTTON_7);
  //ObjectFigures.add<Pies>(ID_BUTTON_8);
}

ATOM RegisterChildClass(WNDCLASSEX wndclass)
{
	//wndclass.lpszMenuName = NULL;
  wndclass.hIconSm = NULL;
  wndclass.hIcon = NULL;
  RegisterControlPanel(wndclass);
  RegisterPaintZone(wndclass);
  return RegisterClassEx(&wndclass);
}

ATOM RegisterControlPanel(WNDCLASSEX wndclass)
{
  LoadString(wndclass.hInstance, IDS_ChildFigures, szWindowClassFigures, MAX_LOADSTRING);
  wndclass.lpfnWndProc = WndChildControlPanelProc;
  wndclass.lpszClassName = szWindowClassFigures;
  return RegisterClassEx(&wndclass);
}

ATOM RegisterPaintZone(WNDCLASSEX wndclass)
{
  LoadString(wndclass.hInstance, IDS_ChildPaint, szWindowClassPaint, MAX_LOADSTRING);
  wndclass.lpfnWndProc = WndChildPaintZoneProc;
  wndclass.lpszClassName = szWindowClassPaint;
  return RegisterClassEx(&wndclass);
}

void PaintTimerRedraw(HWND hWnd)
{
	if (FiguresControl::Instance().isMustRedraw())
	{
		InvalidateRect(hWnd, &FiguresControl::Instance().RedrawZone(), true);
		UpdateWindow(hWnd);
	}
}

VOID workWithPanelCommand(HWND hWnd,WPARAM wParam)
{
	int wmId = LOWORD(wParam);
	int wmEvent = HIWORD(wParam);
	switch (wmId)
	{
	case ID_WIDTHLINE_1PX:
	case ID_WIDTHLINE_2PX:
	case ID_WIDTHLINE_3PX:
	case ID_WIDTHLINE_4PX:
		FiguresControl::Instance().setWidthLine(wmId);
		break;
	case ID_OPTIONS_LINECOLOR:
		FiguresControl::Instance().chooseLineColor();
		break;
	case ID_FILLCOLOR_NONE:
		FiguresControl::Instance().chooseFillColor(false);
		break;
	case ID_FILLCOLOR_BRUSH:
		FiguresControl::Instance().chooseFillColor(true);
		break;
	case IDM_OPEN:
		FiguresControl::Instance().openEncFile(WindowControl::Instance().openFile(hWnd));
		InvalidateRect(hWnd, NULL, true);
		UpdateWindow(hWnd);
		break;
	case IDM_Save:
		RECT rect;
		GetClientRect(hWnd, &rect);
		FiguresControl::Instance().saveEncFile(WindowControl::Instance().saveFile(hWnd), rect);
		break;
	}
}