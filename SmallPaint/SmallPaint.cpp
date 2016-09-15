// SmallPaint.cpp: определяет точку входа для приложения.
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

// Глобальные переменные:
HINSTANCE hInst;								// текущий экземпляр
TCHAR szTitle[MAX_LOADSTRING];					// Текст строки заголовка
TCHAR szWindowClass[MAX_LOADSTRING];			// имя класса главного окна
TCHAR szWindowClassPaint[MAX_LOADSTRING];
TCHAR szWindowClassFigures[MAX_LOADSTRING];

// Отправить объявления функций, включенных в этот модуль кода:
ATOM				MyRegisterClass(HINSTANCE hInstance);
ATOM        RegisterChildClass(WNDCLASSEX);
ATOM        RegisterControlPanel(WNDCLASSEX);
ATOM        RegisterPaintZone(WNDCLASSEX);

BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
VOID createControlPanels(HWND,HINSTANCE);
VOID workWithPanelCommand(HWND ,WPARAM);

static bool isText = false;
static bool isWriteText = false;

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
  _In_opt_ HINSTANCE hPrevInstance,
  _In_ LPTSTR    lpCmdLine,
  _In_ int       nCmdShow)
{
  UNREFERENCED_PARAMETER(hPrevInstance);
  UNREFERENCED_PARAMETER(lpCmdLine);

  // TODO: разместите код здесь.
  MSG msg;
  HACCEL hAccelTable;

  // Инициализация глобальных строк
  LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
  LoadString(hInstance, IDC_SmallPaint, szWindowClass, MAX_LOADSTRING);
  MyRegisterClass(hInstance);

  // Выполнить инициализацию приложения:
  if (!InitInstance(hInstance, nCmdShow))
  {
    return FALSE;
  }

  hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SmallPaint));

  // Цикл основного сообщения:
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
//  ФУНКЦИЯ: MyRegisterClass()
//
//  НАЗНАЧЕНИЕ: регистрирует класс окна.
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
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
  wcex.lpszMenuName = MAKEINTRESOURCE(IDC_SmallPaint);
  wcex.lpszClassName = szWindowClass;
  wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

  RegisterChildClass(wcex);
  return RegisterClassEx(&wcex);
}



//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   НАЗНАЧЕНИЕ: сохраняет обработку экземпляра и создает главное окно.
//
//   КОММЕНТАРИИ:
//
//        В данной функции дескриптор экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится на экран главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
  hInst = hInstance; // Сохранить дескриптор экземпляра в глобальной переменной

  HWND hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW| WS_MAXIMIZE,
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
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  НАЗНАЧЕНИЕ:  обрабатывает сообщения в главном окне.
//
//  WM_COMMAND	- обработка меню приложения
//  WM_PAINT	-Закрасить главное окно
//  WM_DESTROY	 - ввести сообщение о выходе и вернуться.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND paintZone;
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
		paintZone=CreateWindow(szWindowClassPaint, NULL, WS_CHILDWINDOW | WS_VISIBLE,
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
	case WM_MOUSEWHEEL:
	{
		PostMessage(paintZone, message, wParam, lParam);
	}
	break;
  case WM_KEYDOWN:
    switch (wParam)
    {
    case VK_ESCAPE:
      SendMessage(hWnd, WM_CLOSE, 0, 0);
      break;
    case VK_BACK:
			if (!isWriteText)
				SendMessage(paintZone, WM_USER, NULL, NULL);
      break;
    }
    break;

	case WM_COMMAND:
		workWithPanelCommand(hWnd,wParam);
		break;
	case WM_CHAR:
		if (isText)
			SendMessage(paintZone, message, wParam, lParam);
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
    break;
  case WM_COMMAND:
		isWriteText = false;
		isText = wParam == IDC_ID_BUTTON_Text ? true : false;
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
	static float scale = 1;
	static int xPosition=0,xStartPositon=0, yStartPositon=0,yPosition = 0;
	static bool isWheel = false;
  switch (message)
  {
	case WM_CREATE:
		FiguresControl::Instance().setDrawHwnd(hWnd);
		break;
	case WM_USER:
		SendMessage(hWnd, WM_LBUTTONUP, NULL, NULL);
		FiguresControl::Instance().deleteLastFigure();
		InvalidateRect(hWnd, NULL, true);
		UpdateWindow(hWnd);
		break;

	case WM_MBUTTONDOWN:
		SetCapture(hWnd);
		SetCursor(LoadCursor(NULL, IDC_SIZEALL));
		isWheel = true;
		xPosition=xStartPositon = LOWORD(lParam);
		yPosition=yStartPositon = HIWORD(lParam);
		SetTimer(hWnd, IDC_TIMER_REDRAW, TIMER_PAINT_RATE, NULL);
		break;
	case WM_MBUTTONUP:
		isWheel = false;
		scale = 1;
		xStartPositon = yStartPositon = xPosition = yPosition = 0;
		ReleaseCapture();
		KillTimer(hWnd, IDC_TIMER_REDRAW);
	case WM_MOUSEWHEEL:
	{
		SendMessage(hWnd, WM_LBUTTONUP, NULL, NULL);
		int wheel = GET_WHEEL_DELTA_WPARAM(wParam);
		if (wheel > 0 && scale < 5)
			scale += 0.2;
		else if (wheel<0 && scale>0.3)
			scale -= 0.10;

		InvalidateRect(hWnd, NULL, true);
		UpdateWindow(hWnd);
	}

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
    FiguresControl::Instance().drawFigures(hdcOld, ps.rcPaint, hWnd);
		static float i = 1;
		FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 1));
		StretchBlt(hdc, 0, 0, rect.right*scale, rect.bottom*scale, hdcOld, xStartPositon- xPosition, yStartPositon- yPosition, rect.right, rect.bottom, SRCCOPY);
//		BitBlt(hdc, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, hdcOld1, 0, 0, SRCCOPY);
		i += 0.05;
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
		if (isText)
		{
			FiguresControl::Instance().clearCurrentFigure();
			isWriteText = true;
		}
    FiguresControl::Instance().startDrawing(getCurrentCursorPosisiton(hWnd));
		if (FiguresControl::Instance().isDrawing())
		{
			scale = 1;
			xStartPositon = yStartPositon = xPosition = yPosition = 0;
			InvalidateRect(hWnd, NULL, true);
			UpdateWindow(hWnd);
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
			//if (isText)
			//{
			//	TEXTMETRIC tm;
			//	HDC hdc = GetDC(hWnd);
			//	GetTextMetrics(hdc, &tm);
			//	LONG cxChar = tm.tmAveCharWidth;
			//	LONG cyChar = tm.tmHeight;
			//	ReleaseDC(hWnd,hdc);
			//	CreateCaret(hWnd, NULL, cxChar, cyChar);
			//	SetCaretPos(LOWORD(lParam) * cxChar, HIWORD(lParam) * cyChar);
			//	ShowCaret(hWnd);
			//}
    }
  }
  break;
  case WM_MOUSEMOVE:
    if (FiguresControl::Instance().isDrawing())
      FiguresControl::Instance().changeDraw(getCurrentCursorPosisiton(hWnd));
		else if (isWheel)
		{
			xPosition = LOWORD(lParam);
			yPosition = HIWORD(lParam);
		}
    break;
  case WM_TIMER:
		switch (wParam)
		{
		case IDC_TIMER_REDRAW:
			InvalidateRect(hWnd, NULL, true);
			UpdateWindow(hWnd);
			break;
		case IDC_TIMER_PAINT:
			PaintTimerRedraw(hWnd);
			break;
		}
    break;
	case WM_CHAR:
		if (isWriteText)
		{
			FiguresControl::Instance().addText(wParam);
			PaintTimerRedraw(hWnd);
		}
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
		FiguresControl::Instance().saveEncFile(WindowControl::Instance().saveFile(hWnd), hWnd);
		break;
	}
}