// SmallPaint.cpp: определяет точку входа для приложения.
//

#include "stdafx.h"
#include <list>
#include "SmallPaint.h"
#include "Arr_Fig.h"
#include "WindowControl.h"
#include "FiguresControl.h"

enum
{
  HEIGH_CONTROL_PANEL = 100
};

void Clear_Holst();
void  AddFigire_in_map();
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
HWND hWnd;
HDC hdc;
HBRUSH hBrush;
//ObjectFigure ObjectFigures;
//Figure *CurrentFigure = NULL;
//list <unique_ptr<Figure>> List_Figure;

BOOL Cur_Drawing = false;

// Отправить объявления функций, включенных в этот модуль кода:
ATOM				MyRegisterClass(HINSTANCE hInstance);
ATOM        RegisterChildClass(WNDCLASSEX);
ATOM        RegisterControlPanel(WNDCLASSEX);
ATOM        RegisterPaintZone(WNDCLASSEX);

BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
VOID createControlPanels(HWND,HINSTANCE);

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
  wcex.lpszMenuName = NULL;
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

  hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

  if (!hWnd)
  {
    return FALSE;
  }

  hdc = GetWindowDC(hWnd);

  hBrush = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
  SelectObject(hdc, hBrush);

  AddFigire_in_map();


  SetTimer(hWnd, 1, 40, NULL);
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

  case WM_PAINT:
    PAINTSTRUCT ps;
    HDC hdc;
    hdc = BeginPaint(hWnd, &ps);
    EndPaint(hWnd, &ps);
    break;
  case WM_DESTROY:
  {
    //List_Figure.clear();
    DeleteBrush(hBrush);
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
      //ObjectFigures.setFigure(wParam);
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
    HDC hdc/*,hdcOld*/;
	/*	HBITMAP hBitmap;*/
    hdc = BeginPaint(hWnd, &ps);
		//hdcOld = CreateCompatibleDC(hdc);
		//hBitmap = CreateCompatibleBitmap(hdc,
		//	ps.rcPaint.right - ps.rcPaint.left,
		//	ps.rcPaint.bottom - ps.rcPaint.top);
		//SelectObject(hdcOld, hBitmap);

		//SetBkMode(hdcOld, TRANSPARENT);
		//FillRect(hdc, &ps.rcPaint, (HBRUSH)COLOR_WINDOW);
    FiguresControl::Instance().drawFigures(hdc,ps.rcPaint);
		
		//DeleteDC(hdcOld);
		//DeleteObject(hBitmap);
		EndPaint(hWnd, &ps);
  }
  break;
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
      FiguresControl::Instance().endDrawing();
			PaintTimerRedraw(hWnd);
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

void Clear_Holst()
{
  static RECT rect;
  GetClientRect(hWnd, &rect);

  rect.left += WIDTH_BUTTON + 15;

  InvalidateRect(hWnd, &rect, true);
  UpdateWindow(hWnd);
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