// Draw_Form.cpp: определяет точку входа для приложения.
//

#include "stdafx.h"
#include "Draw_Form.h"
#include "Arr_Fig.h"
#include <list>

VOID Create_Button(char *, int, int, int);
void Clear_Holst();
void  AddFigire_in_map();
POINT Get_Current_Cursor_Pos();

using namespace std;

// Глобальные переменные:
HINSTANCE hInst;								// текущий экземпляр
TCHAR szTitle[MAX_LOADSTRING];					// Текст строки заголовка
TCHAR szWindowClass[MAX_LOADSTRING];			// имя класса главного окна
HWND hWnd;
HDC hdc;
HBRUSH hBrush;
ObjectFigure ObjectFigures;
Figure *CurrentFigure=NULL;
list <Figure*> List_Figure;

BOOL Cur_Drawing = false;

// Отправить объявления функций, включенных в этот модуль кода:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

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
	LoadString(hInstance, IDC_DRAW_FORM, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Выполнить инициализацию приложения:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DRAW_FORM));

	// Цикл основного сообщения:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
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

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DRAW_FORM));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   char *NameButton[Number_Button] = { "Отрезок", "Треугольник", "Многоугольник", "Прямоугольник", "Окр. прямоугольник", "Эллипс", "Сегмент", "Сектор" };
   int ID_Button[Number_Button] = { ID_BUTTON_1, ID_BUTTON_2, ID_BUTTON_3, ID_BUTTON_4, ID_BUTTON_5, ID_BUTTON_6, ID_BUTTON_7, ID_BUTTON_8 };
   for (int i = 0; i < Number_Button; i++)
   {
	   Create_Button(NameButton[i], 10, 10 + HEIGH_BUTTON * i, ID_Button[i]);
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
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		switch (wParam)
		{
		default:
			ObjectFigures.SetFigure(wParam);
			SetFocus(hWnd);
			break;
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		for (Figure* List_fig:List_Figure)
		{
			List_fig->Draw_figure();
		}
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		List_Figure.clear();
		DeleteBrush(hBrush);
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			SendMessage(hWnd, WM_CLOSE, 0, 0);
			break;
		case VK_BACK:
			if (!List_Figure.empty() && !Cur_Drawing)
			{
				List_Figure.pop_back();
				Clear_Holst();
			}
			break;
		}
		break;
	case WM_LBUTTONDOWN:
	{
		POINT  pt = Get_Current_Cursor_Pos();
		if (pt.x > WIDTH_BUTTON + 25)
			if (!Cur_Drawing)
			{
			CurrentFigure = ObjectFigures.create();
			if (CurrentFigure != NULL)
			{
				CurrentFigure->Set_Start_Position(pt.x, pt.y);
				Cur_Drawing = true;
				List_Figure.push_back(CurrentFigure);
			}
			}
			else if (CurrentFigure != NULL)
			{
				CurrentFigure->Set_End_Position(pt.x, pt.y);
				Cur_Drawing = false;
			}

	}
	break;

	case WM_RBUTTONDOWN:
		if (CurrentFigure != NULL&&Cur_Drawing)
		{
			POINT  pt = Get_Current_Cursor_Pos();
			if (pt.x > WIDTH_BUTTON + 25)
				CurrentFigure->Add_New_Point(pt.x, pt.y);
		}
		break;
	case WM_MBUTTONDOWN:
		Cur_Drawing = false;
		break;
	case WM_MOUSEMOVE:
		if (CurrentFigure != NULL&&Cur_Drawing)
		{
			POINT  pt = Get_Current_Cursor_Pos();			
			if (pt.x > WIDTH_BUTTON + 25)
				CurrentFigure->Set_End_Position(pt.x, pt.y);
		}
		break;
	case WM_TIMER:
		if (Cur_Drawing)
		{
			Clear_Holst();
		}
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	int a=sizeof(char);
	return 0;
}

VOID Create_Button(char *Text_on_button, int start_x, int start_y, int ID_MENU)
{
	CreateWindow(
		"BUTTON",   // predefined class 
		Text_on_button,       // button text 
		WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // styles 
		// Size and position values are given explicitly, because 
		// the CW_USEDEFAULT constant gives zero values for buttons. 
		start_x,         // starting x position 
		start_y,         // starting y position 
		WIDTH_BUTTON,        // button width 
		HEIGH_BUTTON,        // button height 
		hWnd,       // parent window 
		(HMENU)ID_MENU,       // No menu 
		(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
		NULL);      // pointer not needed
}


void Clear_Holst()
{
	static RECT rect;
	GetClientRect(hWnd, &rect);

	rect.left += WIDTH_BUTTON + 15;

	InvalidateRect(hWnd, &rect, true);
}

POINT Get_Current_Cursor_Pos()
{
	POINT  pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	
	pt.y += 29;
	pt.x += 8;
	return pt;
}

void  AddFigire_in_map()
{
	ObjectFigures.add<Lines>(ID_BUTTON_1);
	ObjectFigures.add<Triangle>(ID_BUTTON_2);
	ObjectFigures.add<PolyLine>(ID_BUTTON_3);
	ObjectFigures.add<Rectangles>(ID_BUTTON_4);
	ObjectFigures.add<RoundRectangles>(ID_BUTTON_5);
	ObjectFigures.add<Ellipses>(ID_BUTTON_6);
	ObjectFigures.add<Chords>(ID_BUTTON_7);
	ObjectFigures.add<Pies>(ID_BUTTON_8);
}