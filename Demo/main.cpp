#include <Windows.h>
#include"Line.h"
#include"Circle.h"

#include <iostream>

using namespace std;


LRESULT WINAPI MyWndProc(HWND hwnd, UINT mcode, WPARAM wp, LPARAM lp)
{
	HDC hdc;
	switch (mcode)
	{
	case WM_LBUTTONDOWN:
		hdc = GetDC(hwnd);
		//DDALine(hdc, 120, 80, 500, 400, RGB(210, 25 , 205));
		//BresenhamLine(hdc, 120, 80, 500, 400, RGB(210, 25 , 205));
		//BresenhamLine(hdc, 500, 400, 120, 80, RGB(210, 25 , 205));
		//PolarCircle(hdc, 120, 200, 100, RGB(210, 25 , 205));
		DirectCircle(hdc, 120, 200, 100, RGB(210, 25 , 205));
		ReleaseDC(hwnd, hdc);
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default: return DefWindowProc(hwnd, mcode, wp, lp);
	}
	return 0;
}
int APIENTRY WinMain(HINSTANCE hinst, HINSTANCE pinst, LPSTR cmd, int nsh)
{
	WNDCLASS wc;

	wc.cbClsExtra = wc.cbWndExtra = 0;
    //Change the background of window to be white.
	wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
    //Change the shape of the mouse.
	wc.hCursor = LoadCursor(NULL, IDC_CROSS);

	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);


	wc.hInstance = hinst;

	wc.lpfnWndProc = MyWndProc;

	wc.lpszClassName = "MyClass";

	wc.lpszMenuName = NULL;

	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wc);

	HWND hwnd = CreateWindow("MyClass", "My First Window", WS_OVERLAPPEDWINDOW, 0, 0, 800, 600, NULL, NULL, hinst, 0);

	ShowWindow(hwnd, nsh);

	UpdateWindow(hwnd);

	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}
