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

void saveScreen(HWND);

LRESULT CALLBACK WndChildPaintZoneProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
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

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
// ��������� ���������� �������, ���������� � ���� ������ ����:
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
static bool isScreen = false;

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
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
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
		isScreen = false;
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
		if (!isScreen)
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
				SetCursor(LoadCursor(NULL, IDC_CROSS));
				SetTimer(hWnd, IDC_TIMER_PAINT, TIMER_PAINT_RATE, NULL);
			}
		}
		else
		{
			FiguresControl::Instance().startScreen(getCurrentCursorPosisiton(hWnd));
			SetCapture(hWnd);
			SetCursor(LoadCursor(NULL, IDC_CROSS));
			SetTimer(hWnd, IDC_TIMER_PAINT, TIMER_PAINT_RATE, NULL);
		}
	}
  break;
  case WM_LBUTTONUP:
  {
		if (!isScreen)
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
		else
		{
			saveScreen(hWnd);
			FiguresControl::Instance().endDrawing();
			ReleaseCapture();
			KillTimer(hWnd, IDC_TIMER_PAINT);
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

inline int GetFilePointer(HANDLE FileHandle) {
	return SetFilePointer(FileHandle, 0, 0, FILE_CURRENT);
}

bool SaveBMPFile(char *filename, HBITMAP bitmap, HDC bitmapDC, int width, int height) {
	bool Success = 0;
	HDC SurfDC = NULL;
	HBITMAP OffscrBmp = NULL;
	HDC OffscrDC = NULL;
	LPBITMAPINFO lpbi = NULL;
	LPVOID lpvBits = NULL;
	HANDLE BmpFile = INVALID_HANDLE_VALUE;
	BITMAPFILEHEADER bmfh;
	if ((OffscrBmp = CreateCompatibleBitmap(bitmapDC, width, height)) == NULL)
		return 0;
	if ((OffscrDC = CreateCompatibleDC(bitmapDC)) == NULL)
		return 0;
	HBITMAP OldBmp = (HBITMAP)SelectObject(OffscrDC, OffscrBmp);
	BitBlt(OffscrDC, 0, 0, width, height, bitmapDC, 0, 0, SRCCOPY);
	if ((lpbi = (LPBITMAPINFO)(new char[sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD)])) == NULL)
		return 0;
	ZeroMemory(&lpbi->bmiHeader, sizeof(BITMAPINFOHEADER));
	lpbi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	SelectObject(OffscrDC, OldBmp);
	if (!GetDIBits(OffscrDC, OffscrBmp, 0, height, NULL, lpbi, DIB_RGB_COLORS))
		return 0;
	if ((lpvBits = new char[lpbi->bmiHeader.biSizeImage]) == NULL)
		return 0;
	if (!GetDIBits(OffscrDC, OffscrBmp, 0, height, lpvBits, lpbi, DIB_RGB_COLORS))
		return 0;
	if ((BmpFile = CreateFile(filename,
		GENERIC_WRITE,
		0, NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL)) == INVALID_HANDLE_VALUE)
		return 0;
	DWORD Written;
	bmfh.bfType = 19778;
	bmfh.bfReserved1 = bmfh.bfReserved2 = 0;
	if (!WriteFile(BmpFile, &bmfh, sizeof(bmfh), &Written, NULL))
		return 0;
	if (Written < sizeof(bmfh))
		return 0;
	if (!WriteFile(BmpFile, &lpbi->bmiHeader, sizeof(BITMAPINFOHEADER), &Written, NULL))
		return 0;
	if (Written < sizeof(BITMAPINFOHEADER))
		return 0;
	int PalEntries;
	if (lpbi->bmiHeader.biCompression == BI_BITFIELDS)
		PalEntries = 3;
	else PalEntries = (lpbi->bmiHeader.biBitCount <= 8) ?
		(int)(1 << lpbi->bmiHeader.biBitCount) : 0;
	if (lpbi->bmiHeader.biClrUsed)
		PalEntries = lpbi->bmiHeader.biClrUsed;
	if (PalEntries) {
		if (!WriteFile(BmpFile, &lpbi->bmiColors, PalEntries * sizeof(RGBQUAD), &Written, NULL))
			return 0;
		if (Written < PalEntries * sizeof(RGBQUAD))
			return 0;
	}
	bmfh.bfOffBits = GetFilePointer(BmpFile);
	if (!WriteFile(BmpFile, lpvBits, lpbi->bmiHeader.biSizeImage, &Written, NULL))
		return 0;
	if (Written < lpbi->bmiHeader.biSizeImage)
		return 0;
	bmfh.bfSize = GetFilePointer(BmpFile);
	SetFilePointer(BmpFile, 0, 0, FILE_BEGIN);
	if (!WriteFile(BmpFile, &bmfh, sizeof(bmfh), &Written, NULL))
		return 0;
	if (Written < sizeof(bmfh))
		return 0;
	CloseHandle(BmpFile);
	return 1;
}

bool ScreenCapture(HWND hWnd,int x, int y, int width, int height, char *filename) {
	HDC hdc1 = GetDC(hWnd);
	HDC hDc = CreateCompatibleDC(hdc1);
	HBITMAP hBmp = CreateCompatibleBitmap(hdc1, width, height);
	SelectObject(hDc, hBmp);
	BitBlt(hDc, 0, 0, width, height, hdc1, x, y, SRCCOPY);
	bool ret = SaveBMPFile(filename, hBmp, hDc, width, height);
	DeleteBitmap(hBmp);
	DeleteDC(hDc);
	DeleteDC(hdc1);
	return ret;
}

void saveScreen(HWND hWnd)
{
	RECT rect = FiguresControl::Instance().getScreen();
	InvalidateRect(hWnd, NULL, true);
	UpdateWindow(hWnd);
	const char *path=WindowControl::Instance().saveFile(hWnd);
	if (path)
	{
		ScreenCapture(hWnd,rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, const_cast<char*>(path));
	}
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
	case IDM_ABOUT:
		DialogBox((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
		break;
	case ID_FILE_EXIT:
		DestroyWindow(hWnd);
		break;
		SendMessage(hWnd, WM_CLOSE, NULL, NULL);
	case ID_PRINT:
		isScreen = true;
		break;
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

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
