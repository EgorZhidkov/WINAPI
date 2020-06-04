// WindowsProject1.cpp : Определяет точку входа для приложения.
//
#include <iostream>
#include <ctime>
#include "framework.h"
#include "WindowsProject1.h"
using namespace std;
#define MAX_LOADSTRING 100

const double PI = 3.141592653;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
char szClassName[] = "CG_WAPI_Template";
void coordinate(RECT &r, int right, int left, int bottom, int top) {
	right = r.right;
	left = r.left;
	bottom = r.bottom;
	top = r.top;
	
}
////////////////////////////////////////////////////////////////////////////////////////////////////
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd;
	MSG lpMsg;
	WNDCLASS wc;

	// Заполняем структуру класса окна
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject((RGB(0, 0, 255)));
	wc.lpszMenuName = NULL;
	wc.lpszClassName = (LPCSTR)szClassName;

	// Регистрируем класс окна
	if (!RegisterClass(&wc))
	{
		MessageBox(NULL, (LPCSTR)"Не могу зарегистрировать класс окна!", (LPCSTR)"Ошибка", MB_OK);
		return 0;
	}

	// Создаем основное окно приложения
	hWnd = CreateWindow(
		(LPCSTR)szClassName, // Имя класса 
		"Шаблон WinAPI приложения", // Текст заголовка
		WS_OVERLAPPEDWINDOW, // Стиль окна 
		0, 0,  // Позиция левого верхнего угла 
		800, 800, // Ширина и высота окна 
		(HWND)NULL, // Указатель на родительское окно NULL 
		(HMENU)NULL, // Используется меню класса окна 
		(HINSTANCE)hInstance, // Указатель на текущее приложение
		NULL); // Передается в качестве lParam в событие WM_CREATE

	if (!hWnd)
	{
		MessageBox(NULL, (LPCSTR)"Не удается создать главное окно!", (LPCSTR)"Ошибка", MB_OK);
		return 0;
	}

	// Показываем наше окно
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// Выполняем цикл обработки сообщений до закрытия приложения
	while (GetMessage(&lpMsg, NULL, 0, 0))
	{
		TranslateMessage(&lpMsg);
		DispatchMessage(&lpMsg);
	}
	return (lpMsg.wParam);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
int left_ = 350, right_ = 450, top_ = 350, bottom_ = 450;
int state = 0;
int red, g, b, red_, g_, b_;
LRESULT CALLBACK WndProc(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam)
{
	static RECT Rect, r;
	

	switch (messg)
	{
		static PAINTSTRUCT ps;
		RECT Rect;
		static HDC hdc, hCmpDC;
		static HBITMAP hBmp;
		
	case WM_LBUTTONDOWN:
	{
		right_ += 50;
		left_ -= 50;
		top_ -= 50;
		bottom_ += 50;
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	}
	case WM_RBUTTONDOWN:
		if (state == 0) {
			state = 1;
		}else{
			state = 0;
		}
		InvalidateRect(hWnd, NULL, TRUE);
		break;

	case WM_PAINT:
	{
		GetClientRect(hWnd, &Rect);
		hdc = BeginPaint(hWnd, &ps);

		// Создание теневого контекста для двойной буферизации
		hCmpDC = CreateCompatibleDC(hdc);
		hBmp = CreateCompatibleBitmap(hdc, Rect.right - Rect.left, Rect.bottom - Rect.top);
		SelectObject(hCmpDC, hBmp);

		// Закраска фоновым цветом
		LOGBRUSH br;
		br.lbStyle = BS_SOLID;
		br.lbColor = (RGB(0, 0, 255));
		HBRUSH brush;
		brush = CreateBrushIndirect(&br);
		FillRect(hCmpDC, &Rect, brush);
		DeleteObject(brush);


		// Здесь рисуем на контексте hCmpDC
		srand(time(0));
		HBRUSH hBrush;
		r.left = left_;
		r.right = right_;
		r.bottom = bottom_;
		r.top = top_;
		hBrush = CreateHatchBrush(HS_FDIAGONAL, RGB(0, 255, 0));
		SelectObject(hdc, hBrush);
		Rectangle(hCmpDC, r.left, r.top, r.right, r.bottom); //эллипс будет заштрихован
		red = rand() % 256;
		b = rand() % 256;
		g = rand() % 256;
		red_ = red;
		b_ = b;
		g_ = g;
		FillRect(hCmpDC, &r, (HBRUSH)CreateSolidBrush(RGB(255, 0, 207)));
		if (state == 1) {
			FillRect(hCmpDC, &r, (HBRUSH)CreateSolidBrush(RGB(red, b, g)));
			state = 0;
		}
		//FillRect(hCmpDC, &r, (HBRUSH)CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256)));
		//FillRect(hCmpDC, &r, (HBRUSH)CreateSolidBrush(RGB(252, 15, 192)));


		//обновляем окно

	//	ValidateRect(hWnd, NULL);

		// Копируем изображение из теневого контекста на экран
		SetStretchBltMode(hdc, COLORONCOLOR);
		BitBlt(hdc, 0, 0, Rect.right - Rect.left, Rect.bottom - Rect.top, hCmpDC, 0, 0, SRCCOPY);

		// Удаляем ненужные системные объекты
		DeleteDC(hCmpDC);
		DeleteObject(hBmp);
		hCmpDC = NULL;

		EndPaint(hWnd, &ps);
		break;
	}
	case WM_DESTROY:

		PostQuitMessage(0);
		break;

	default:
		return (DefWindowProc(hWnd, messg, wParam, lParam));
	}
	return (0);
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