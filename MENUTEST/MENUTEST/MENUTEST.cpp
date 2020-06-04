// MENUTEST.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "MENUTEST.h"
#include<ctime>
#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MENUTEST, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MENUTEST));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
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
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MENUTEST));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(CreateSolidBrush(RGB(0, 0, 0)));
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MENUTEST);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      0, 0, 600, 600, nullptr, nullptr, hInstance, nullptr);

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
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
int x = 0;
int y = 50;
HWND hEdit1;
HWND hEdit2;
int test = 0;
HDC hdc;
PAINTSTRUCT ps;
int frequency = 3000;
int font = 0;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//HMENU hMenu = CreateMenu();
	
    switch (message)
    {
		hdc = BeginPaint(hWnd, &ps);
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Разобрать выбор в меню:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_TEST_TEST1:
			test = 1;
			SendMessage(hWnd, WM_PAINT, WPARAM(hWnd), NULL);
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case ID_TEST_TEST2:
			test = 2;
			SendMessage(hWnd, WM_PAINT, WPARAM(hWnd), NULL);
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case ID_TEST_TEST3:
			test = 0;
			//SendMessage(hWnd, WM_PAINT, WPARAM(hWnd), NULL);
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case ID_Frequency1:
			frequency = 100;
			KillTimer(hWnd, 3);
			KillTimer(hWnd, 2);
			SetTimer(hWnd, 1, 300, (TIMERPROC)NULL);
			//SendMessage(hWnd, WM_CREATE, NULL, NULL);
			InvalidateRect(hWnd, NULL, TRUE);
			KillTimer(hWnd, 3);
			break;
		case ID_Frequency2:
			KillTimer(hWnd, 3);
			KillTimer(hWnd, 1);
			frequency = 1000;
			SetTimer(hWnd, 2, 1000, (TIMERPROC)NULL);
			//SendMessage(hWnd, WM_CREATE, NULL, NULL);
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case ID_Frequency3:
			KillTimer(hWnd, 1);
			KillTimer(hWnd, 2);
			frequency = 3000;
			SetTimer(hWnd, 3, 3000, (TIMERPROC)NULL);
			//SendMessage(hWnd, WM_CREATE, WPARAM(hWnd), NULL);
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case IDM_FONT:
			if (font == 0) {
				font = 1;
			}
			else
			{
				font = 0;
			}
			SendMessage(hWnd, WM_PAINT, WPARAM(hWnd), NULL);
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	}
	case WM_CREATE:
	{
			SetTimer(hWnd, 3, 3000, (TIMERPROC)NULL);
			break;
	}
	case WM_PAINT:
	{
		switch (test)
		{
		case(1):
			if (font == 1) {
				hdc = BeginPaint(hWnd, &ps);
				static LOGFONT lf; //создаём экземпляр LOGFONT
				lf.lfCharSet = DEFAULT_CHARSET; //значение по умолчанию
				lf.lfPitchAndFamily = DEFAULT_PITCH; //значения по умолчанию
				strcpy_s(lf.lfFaceName, "Times New Roman"); //копируем в строку название шрифта
				lf.lfHeight = 20; //высота
				lf.lfWidth = 10; //ширина
				lf.lfWeight = 40; //толщина
				lf.lfEscapement = 0; //шрифт без поворота
				HFONT hFont = CreateFontIndirect(&lf);
				SelectObject(hdc, hFont);
				srand(time(0));
				SetBkMode(hdc, TRANSPARENT);
				SetTextColor(hdc, RGB(255, 255, 255));
				TextOut(hdc, x, y, "Жидков Егор", 12);
				//EndPaint(hWnd, &ps);
				//InvalidateRect(hWnd, NULL, TRUE);
				EndPaint(hWnd, &ps);
				break;
			}
			else 
			{
				hdc = BeginPaint(hWnd, &ps);
				srand(time(0));
				SetBkMode(hdc, TRANSPARENT);
				SetTextColor(hdc, RGB(255, 255, 255));
				TextOut(hdc, x, y, "Жидков Егор", 12);
				//EndPaint(hWnd, &ps);
				//InvalidateRect(hWnd, NULL, TRUE);
				EndPaint(hWnd, &ps);
				break;
			}
		case(2):
			if (font == 1) {
				//hdc = BeginPaint(hWnd, &ps);
				hdc = BeginPaint(hWnd, &ps);
				static LOGFONT lf; //создаём экземпляр LOGFONT
				lf.lfCharSet = DEFAULT_CHARSET; //значение по умолчанию
				lf.lfPitchAndFamily = DEFAULT_PITCH; //значения по умолчанию
				strcpy_s(lf.lfFaceName, "Times New Roman"); //копируем в строку название шрифта
				lf.lfHeight = 20; //высота
				lf.lfWidth = 10; //ширина
				lf.lfWeight = 40; //толщина
				lf.lfEscapement = 0; //шрифт без поворота
				HFONT hFont = CreateFontIndirect(&lf);
				SelectObject(hdc, hFont);
				srand(time(0));
				SetBkMode(hdc, TRANSPARENT);
				SetTextColor(hdc, RGB(102, 255, 0));
				TextOut(hdc, x, y, "Жидков Егор", 12);
				//EndPaint(hWnd, &ps);
				//InvalidateRect(hWnd, NULL, TRUE);
				EndPaint(hWnd, &ps);
				break;
			}
			else
			{
				hdc = BeginPaint(hWnd, &ps);
				srand(time(0));
				SetBkMode(hdc, TRANSPARENT);
				SetTextColor(hdc, RGB(102, 255, 0));
				TextOut(hdc, x, y, "Жидков Егор", 12);
				//EndPaint(hWnd, &ps);
				//InvalidateRect(hWnd, NULL, TRUE);
				EndPaint(hWnd, &ps);
				break;
			}
		case(0):
			if (font == 1) {
				hdc = BeginPaint(hWnd, &ps);
				static LOGFONT lf; //создаём экземпляр LOGFONT
				lf.lfCharSet = DEFAULT_CHARSET; //значение по умолчанию
				lf.lfPitchAndFamily = DEFAULT_PITCH; //значения по умолчанию
				strcpy_s(lf.lfFaceName, "Times New Roman"); //копируем в строку название шрифта
				lf.lfHeight = 20; //высота
				lf.lfWidth = 10; //ширина
				lf.lfWeight = 40; //толщина
				lf.lfEscapement = 0; //шрифт без поворота
				HFONT hFont = CreateFontIndirect(&lf);
				SelectObject(hdc, hFont);
				srand(time(0));
				SetBkMode(hdc, TRANSPARENT);
				SetTextColor(hdc, RGB(242, 22, 0));
				TextOut(hdc, x, y, "Жидков Егор", 12);
				//EndPaint(hWnd, &ps);
				//InvalidateRect(hWnd, NULL, TRUE);
				EndPaint(hWnd, &ps);
				break;
			}
			else
			{
				hdc = BeginPaint(hWnd, &ps);
				srand(time(0));
				SetBkMode(hdc, TRANSPARENT);
				SetTextColor(hdc, RGB(242, 22, 0));
				TextOut(hdc, x, y, "Жидков Егор", 12);
				//EndPaint(hWnd, &ps);
				//InvalidateRect(hWnd, NULL, TRUE);
				EndPaint(hWnd, &ps);
				break;
			}
		}
		break;
	}

	case WM_TIMER:
		x = x + 25;
		if (x == 600) {
			x = 0;
		}
		InvalidateRect(hWnd, NULL, TRUE);
		break;
   
		//break;
    case WM_DESTROY:
		KillTimer(hWnd, 1);
		KillTimer(hWnd, 2);
		KillTimer(hWnd, 3);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
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


