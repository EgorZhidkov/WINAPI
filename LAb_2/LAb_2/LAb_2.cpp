// LAb_2.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "LAb_2.h"

#define MAX_LOADSTRING 100

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
	wc.lpszClassName = WinName1; 				// Имя класса окна 
	wc.lpfnWndProc = WndProc; 					// Функция окна 
	wc.style = CS_HREDRAW | CS_VREDRAW; 			// Стиль окна 
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); 		// Стандартная иконка 
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); 		// Стандартный курсор 
	wc.lpszMenuName = NULL; 					// Нет меню 
	wc.cbClsExtra = 0; 						// Нет дополнительных данных класса 
	wc.cbWndExtra = 0; 						// Нет дополнительных данных окна 
	wc.hbrBackground = (HBRUSH)(CreateSolidBrush(RGB(255, 240, 240)));	// Заполнение окна белым цветом 


	// Регистрация класса окна
	if (!RegisterClass(&wc)) return 0;

	// Создание окна 
	hWnd = CreateWindow(WinName1,			// Имя класса окна 
		_T("Окно 1"), 		// Заголовок окна 
		WS_OVERLAPPEDWINDOW, 		// Стиль окна 
		820,				// x 
		100, 				// y	 Размеры окна 
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

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND hWnd2 = NULL;
	static LPCWSTR textt = NULL;
	switch (message)		 // Обработчик сообщений
	{
	case WM_LBUTTONDOWN:
		hWnd2 = FindWindow(WinName2, NULL);
		if (hWnd2 == NULL)
			MessageBox(hWnd, _T("Окно 2 не найдено!"), _T("Не найдено"), MB_OK);
		else
		{
			MessageBox(hWnd, _T("Окно 2 найдено! Сообщение что окна откртыто отправлено."), _T("Найдено"), MB_OK);
			SendMessage(hWnd2, WM_USER + 1, WPARAM(hWnd), NULL);
			
		}
		return DefWindowProc(hWnd, message, wParam, lParam);
	case WM_RBUTTONDOWN:
		hWnd2 = FindWindow(WinName2, NULL);
		if (hWnd2 == NULL)
			MessageBox(hWnd, _T("Окно 2 не найдено!"), _T("Не найдено"), MB_OK);
		else
		{
			MessageBox(hWnd, _T("Окно 2 найдено! Сообщение  отправлено."), _T("Найдено"), MB_OK);
			SendMessage(hWnd2, WM_USER + 2, WPARAM(hWnd), NULL);
		}
		return DefWindowProc(hWnd, message, wParam, lParam);
	case WM_DESTROY:
		PostQuitMessage(0);
		break; 			// Завершение программы 
	default: 			// Обработка сообщения по умолчанию 
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}