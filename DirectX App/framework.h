#pragma once

#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <d3d9.h>
#include <iostream>
#include <chrono>
#include <timeapi.h>

#include "resource.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "winmm.lib")

inline HWND hwnd;
inline LPDIRECT3D9 d3d;
inline LPDIRECT3DDEVICE9 d3ddev;

void initD3D(HWND hWnd);
void renderFrame();
void cleanD3D();

void RenderRectProgress(float fProgress, LPDIRECT3DDEVICE9 renderDevice);
void update();
