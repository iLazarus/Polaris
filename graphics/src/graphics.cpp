#include "graphics.h"

using namespace std;
RECT Center = { 0, 0, 0, 0 };
RECT Position = { 0, 0, 0, 0 };


graphics::graphics()
{
	Direct3D = nullptr;
	Direct3DDevice = nullptr;
	Font = nullptr;
}


graphics::~graphics()
{

	if (Font)
	{
		Font->Release();
		Font = NULL;
	}

	if (LinePtr)
	{
		LinePtr->Release();
		LinePtr = NULL;
	}

}

bool graphics::Init(HWND hWnd, UINT iWidth, UINT iHeight)
{
	printf("[!] Graphics Tool Initalize Start\n");
	ZeroMemory(&Parameters, sizeof(Parameters));
	Parameters.EnableAutoDepthStencil = TRUE;
	Parameters.AutoDepthStencilFormat = D3DFMT_D16;
	Parameters.Windowed = TRUE;
	Parameters.BackBufferCount = 1;
	Parameters.BackBufferFormat = D3DFMT_A8R8G8B8;
	Parameters.BackBufferWidth = iWidth;
	Parameters.BackBufferHeight = iHeight;
	Parameters.MultiSampleType = D3DMULTISAMPLE_NONE;
	Parameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	Parameters.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	Parameters.hDeviceWindow = hWnd;
	Parameters.FullScreen_RefreshRateInHz = 0;
	Direct3D = Direct3DCreate9(D3D_SDK_VERSION);
	Direct3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &Parameters, &Direct3DDevice);
	D3DXCreateFont(Direct3DDevice, FONT_SIZE, 0, FW_NORMAL, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLEARTYPE_NATURAL_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"ÐÂËÎÌå", &Font);
	D3DXCreateLine(Direct3DDevice, &LinePtr);
	return true;
}

void graphics::Begin()
{
	Direct3DDevice->Clear(NULL, NULL, D3DCLEAR_TARGET, NULL, 1.0f, NULL);
	Direct3DDevice->BeginScene();
}

void graphics::End()
{
	Direct3DDevice->EndScene();
	Direct3DDevice->Present(NULL, NULL, NULL, NULL);
}

void graphics::DrawString(bool center, float x, float y, D3DCOLOR color, const char* format, ...)
{
	char Buffer[128] = {NULL};
	va_list va_alist;
	va_start(va_alist, format);
	vsprintf_s(Buffer, format, va_alist);
	va_end(va_alist);
	string buf = Buffer;
	int num = MultiByteToWideChar(CP_ACP, 0, buf.c_str(), -1, NULL, 0);
	wchar_t *wide = new wchar_t[num];
	MultiByteToWideChar(CP_ACP, 0, buf.c_str(), -1, wide, num);
	wstring ws = wstring(wide);
	delete[]wide;
	size_t len = wcslen(ws.c_str());
	if (center)
	{
		Position.left = LONG(x) - (LONG)(len * (FONT_SIZE / 4));
		Position.top = LONG(y) - (FONT_SIZE / 4);
	}
	else
	{
		Position.left = size_t(x);
		Position.top = size_t(y);
	}
	Font->DrawText(0, ws.c_str(), -1, &Position, DT_NOCLIP, color);
}


void graphics::DrawLine(float x, float y, float x2, float y2, D3DCOLOR color)
{
	D3DXVECTOR2 points[2];
	points[0] = D3DXVECTOR2(x, y);
	points[1] = D3DXVECTOR2(x2, y2);
	LinePtr->Draw(points, 2, color);
}