#include <Windows.h>
#include <stdio.h>
#include "common.h"
#include "graphics.h"
#include "driver.h"
#include "game.h"

#include <thread>
#pragma warning(disable : 4996)

bool bGraphicsReady = false;

graphics *dx = 0;
game *hack = 0;
driver *drv = 0;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd)
{
	AllocConsole();
	SetConsoleTitle(L"Chrome");
	freopen("CON", "w", stdout);

	WNDCLASSEX wcex;
	wcex.cbClsExtra = 0;
	wcex.cbSize = sizeof(wcex);
	wcex.cbWndExtra = 0;
	wcex.cbClsExtra = 0;
	wcex.hbrBackground = (HBRUSH)(RGB(0, 0, 0));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hIconSm = NULL;
	wcex.hInstance = hInstance;
	wcex.lpfnWndProc = WndProc;
	wcex.lpszClassName = L"Chrome";
	wcex.lpszMenuName = NULL;
	wcex.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wcex)) return -1;

	RECT rect = { 0, 0, WIDTH, HEIGHT };
	HWND  hWnd = CreateWindowEx(
		WS_EX_LAYERED | WS_EX_TOPMOST,
		L"Chrome",
		L"",
		WS_POPUP,
		rect.left,
		rect.top,
		rect.right - rect.left,
		rect.bottom - rect.top,
		NULL,
		NULL,
		hInstance,
		NULL);
	if (!hWnd) return -1;

	SetLayeredWindowAttributes(hWnd, RGB(0, 0, 0), 0, LWA_COLORKEY);
	ShowWindow(hWnd, nShowCmd);


	dx = new graphics();
	if (!(bGraphicsReady = dx->Init(hWnd, WIDTH, HEIGHT)))
	{
		printf("[!] DX Init Failed!\r\n");
		getchar();
		return -1;
	}
	else
	{
		printf("[!] DX Init Sucess!\r\n");
	}
	//
	hack = new game();
	drv = new driver();

	thread{ [=] {
		hack->Init(drv, dx);
		hack->ScanOffset();
		hack->RefreshOffset();
		while (true)
		{
			dx->Begin();
			hack->FilterActors();
			dx->End();
			Sleep(1);
		}
	} }.detach();

	thread{ [=] {

		while (true)
		{
			hack->HotKey();
			Sleep(100);
		}

	} }.detach();

	thread{ [] 
	{
		
		while (true)
		{
			hack->Fire();
			Sleep(50);
		}
	} 
	}.detach();

	MSG msg{};
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		if (WM_QUIT != msg.message)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		Sleep(10);
	}
	delete drv;
	delete hack;
	delete dx;
	fclose(stdout);
	UnregisterClass(L"Chrome", wcex.hInstance);
	FreeConsole();
	return static_cast<int>(msg.wParam);
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CLOSE:
		getchar();
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}