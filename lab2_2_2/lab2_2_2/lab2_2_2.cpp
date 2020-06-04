// lab2_2_2.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "lab2_2_2.h"
#include <string>
#include <iostream>
#include <Windows.h>
#include <tchar.h>
#include <ctime>
using namespace std;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
TCHAR WinName1[] = _T("MainFrame1");
TCHAR WinName2[] = _T("MainFrame2");

int WINAPI wWinMain(HINSTANCE This,		 // Дескриптор текущего приложения 
	HINSTANCE Prev, 	// В современных системах всегда 0 
	LPTSTR cmd, 		// Командная строка 
	int mode) 		// Режим отображения окна
{
	HWND hWnd;		// Дескриптор главного окна программы 
	MSG msg; 		// Структура для хранения сообщения 
	WNDCLASS wc; 	// Класс окна
	// Определение класса окна 
	wc.hInstance = This;
	wc.lpszClassName = WinName2; 				// Имя класса окна 
	wc.lpfnWndProc = WndProc; 					// Функция окна 
	wc.style = CS_HREDRAW | CS_VREDRAW; 			// Стиль окна 
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); 		// Стандартная иконка 
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); 		// Стандартный курсор 
	wc.lpszMenuName = NULL; 					// Нет меню 
	wc.cbClsExtra = 0; 						// Нет дополнительных данных класса 
	wc.cbWndExtra = 0; 						// Нет дополнительных данных окна 
	wc.hbrBackground = (HBRUSH)(CreateSolidBrush(RGB(255, 255, 200)));	// Заполнение окна белым цветом 


	// Регистрация класса окна
	if (!RegisterClass(&wc)) return 0;

	// Создание окна 
	hWnd = CreateWindow(WinName2,			// Имя класса окна 
		_T("Окно 2"), 		// Заголовок окна 
		WS_OVERLAPPEDWINDOW, 		// Стиль окна 
		70,				// x 
		0, 				// y	 Размеры окна 
		400, 				// width 
		500, 				// Height 
		HWND_DESKTOP, 				// Дескриптор родительского окна 
		NULL, 						// Нет меню 
		This, 						// Дескриптор приложения 
		NULL); 					// Дополнительной информации нет 

	ShowWindow(hWnd, mode); 				// Показать окно

	// Цикл обработки сообщений 
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg); 		// Функция трансляции кодов нажатой клавиши 
		DispatchMessage(&msg); 		// Посылает сообщение функции WndProc() 
	}
	return 0;
}

// Оконная функция вызывается операционной системой
// и получает сообщения из очереди для данного приложения

int i = 0;
RECT r;
int b = 3;
HDC ps;
int leftmouse = 0;
int checkcount = 0;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HWND des;
	des = FindWindow(WinName1, NULL);
	int a = int(des);
	static HWND hWnd2 = NULL;
	static LPCWSTR textt = NULL;

	switch (message)		 // Обработчик сообщений
	{
	
	case WM_USER + 1:
	{
		hWnd2 = FindWindow(WinName1, NULL);
		leftmouse = 1;
		InvalidateRect(hWnd, NULL, TRUE);

					   break;
	}
	
	case WM_TIMER:
	{
		srand(time(0));
		HBRUSH greenBrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
		SetClassLong(hWnd, GCL_HBRBACKGROUND, (LONG)greenBrush);
		InvalidateRect(hWnd, NULL, TRUE);
		KillTimer(hWnd, 1);
		break;
	}
	case WM_USER + 2:
	{
		checkcount = 1;
		i++;
		SetTimer(hWnd, 1, 5000, (TIMERPROC)NULL);
		InvalidateRect(hWnd, NULL, TRUE);
		//KillTimer(hWnd, 1);
		break;
		
	}
	//KillTimer(hWnd, 1);
	case WM_PAINT:
	{
		WCHAR textz[9];
		HDC hdc = GetDC(hWnd);
		PAINTSTRUCT ps;
		hdc = BeginPaint(hWnd, &ps);
		if (leftmouse == 1)
		{
			
			size_t sizehwnd = GetWindowTextLength(hWnd2) + 1;
			char output[20];
			_i64toa_s(int(hWnd2), output, sizehwnd, 16);
			textz[0] = output[0];
			for (int i = 8; i != 0; --i)
			{
				textz[8 - i] = output[8 - i];
			}
			textt = textz;
			if (checkcount == 1) {
				SetTextColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
				SetBkColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
				TextOut(hdc, 10, 10, textt, 8);
				
			}
			else {
				TextOut(hdc, 10, 10, textt, 8);
			}
			
		}
		
		
		
		
		//PAINTSTRUCT ps;
		//hdc = BeginPaint(hWnd, &ps);
		if (leftmouse == 1)
		{
			size_t sizehwnd = GetWindowTextLength(hWnd2) + 1;
			char output[20];
			_i64toa_s(int(hWnd), output, sizehwnd, 16);
			textz[0] = output[0];
			for (int i = 8; i != 0; --i)
			{
				textz[8 - i] = output[8 - i];
			}
			textt = textz;
			if (checkcount == 1) {
				SetTextColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
				TextOut(hdc, 10, 30, textt, 8);
				checkcount--;
			}
			else {
				TextOut(hdc, 10, 30, textt, 8);
			}
		}
		EndPage(hdc);
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
		break; 			// Завершение программы 
	default: 			// Обработка сообщения по умолчанию 
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}