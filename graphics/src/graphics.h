#pragma once 
#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdio.h>
#include <iostream>
#include <dwmapi.h> 
#include <d3d9.h>
#include "d3dx9.h"

#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "dwmapi.lib")

#define M_PI 3.1415926535897932384
#define RED  D3DCOLOR_ARGB(255, 150, 0, 0)
#define BLUE  D3DCOLOR_ARGB(255, 45, 45, 255)
#define ORIGEN  D3DCOLOR_ARGB(255, 255, 128, 0)
#define GREEN  D3DCOLOR_ARGB(255, 0, 255, 0)
#define PURPLE  D3DCOLOR_ARGB(255, 255, 0, 255)
#define LIGHTBLUE  D3DCOLOR_ARGB(255, 130, 190, 220)
#define WHITE  D3DCOLOR_ARGB(255, 255, 255, 255)
#define VISUAL  D3DCOLOR_ARGB(170, 0, 250, 0)
#define UNVISUAL  D3DCOLOR_ARGB(255, 255, 255, 0)
#define FONT_SIZE 14

class graphics
{
public:
	graphics();
	~graphics();


	ID3DXFont*				Font;
	ID3DXLine*				LinePtr;
	IDirect3D9*				Direct3D;
	IDirect3DDevice9*		Direct3DDevice;
	D3DPRESENT_PARAMETERS	Parameters;
	D3DVIEWPORT9			Viewport;

	bool Init(HWND hWnd, UINT iWidth, UINT iHeight);
	void Begin();
	void End();
	void DrawString(bool center, float x, float y, D3DCOLOR color, const char* format, ...);
	void DrawLine(float x, float y, float x2, float y2, D3DCOLOR color);
};



#endif // !GRAPHICS_H