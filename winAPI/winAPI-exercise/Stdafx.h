#pragma once
#pragma warning(disable : 4005) // ��ũ�� ������ ��� �����ϰڴ�

// �ڵ� �� ��� �� ���� OS �������� ����
#include <SDKDDKVer.h>

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����
#include <windows.h>
// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h> 
#include <memory.h>
//memcpy() / memset()
#include <stdio.h>
#include <tchar.h>
#include <assert.h>

// C++ ��Ÿ�� ��� �����Դϴ�.
#include <iostream>
// stl �پ��� ��� // ���е��� ����
// OS �� ���������� ������ �Ѵ�
#include <chrono> 
#include <string> 
#include <random>
#include <vector>
#include <map>
// �Ϲ����� ��Ȳ���� �ؽø� ����� �˻��ϱ⿡ map���� ������
// �ߺ������͸� ������� �ʱ� �����̴�
// ���絥���Ͱ� ���ٸ� �ؽ� �浹 �߻� ���ΰ� �׻� �����Ѵ�
#include <unordered_map>
#include <bitset>
#include <cassert>

using namespace std;
//using std::vector;
//using std::string;
//using std::wstring;

//
//#include <D2D1.h>
//#include <d2d1helper.h>
//#include <d3dx9.h>
//#include <D3DX11.h>
//#include <d3d11shader.h>
//#include <dinput.h>
//
//#pragma comment(lib, "D2D1.h")
//#pragma comment(lib, "d2d1helper.h")
//#pragma comment(lib, "d3dx9.h")
//#pragma comment(lib, "D3DX11.h")
//#pragma comment(lib, "d3d11shader.h")
//#pragma comment(lib, "dinput.h")
//
//ID2D1Factory* _ID2D1Factory = nullptr;
//ID2D1HwndRenderTarget* _ID2D1HwndRenderTarget = nullptr;

//���� ���� ��� �ʸ�����
#include "CommonMacroFunction.h"
#include "RandomFunction.h"
#include "KeyManager.h"

//������ ����
#define RND RandomFunction::getSingleton()
#define KEYMANAGER KeyManager::getSingleton()

// ��ũ��
#define WINNAME     (LPSTR)(TEXT("WindowAPI"))
#define WINSTART_X   100
#define WINSTART_Y   100
#define WINSIZE_X    800
#define WINSIZE_Y    800
#define WINSTYLE     WS_CAPTION | WS_SYSMENU

// ���� ��ũ�� ����
#define COLOR_RED       RGB(255, 0, 0)
#define COLOR_GREEN     RGB(0, 255, 0)
#define COLOR_BLUE      RGB(0, 0, 255)
#define COLOR_YELLOW    RGB(255, 255, 0)
#define COLOR_CYAN      RGB(0, 255, 255)
#define COLOR_MAGENTA   RGB(255, 0, 144)
#define COLOR_WHITE     RGB(255, 255, 255)
#define COLOR_BLACK     RGB(0, 0, 0)
#define COLOR_GRAY      RGB(128, 128, 128)
#define COLOR_DARKGRAY  RGB(64, 64, 64)
#define COLOR_LIGHTGRAY RGB(192, 192, 192)

// ��ũ�� �Լ�
#define SAFE_DELETE(p)         {if(p) {delete (p); (p) = nullptr;}}
#define SAFE_DELETE_ARRAY(p)   {if(p) {delete[] (p); (p) = nullptr;}}
#define SAFE_RELEASE(p)        {if(p) {(p) -> release(); (p) = nullptr;}}

// �������� extern�� �̳��� ������ �ִٰ� ������ִ� ��
extern HINSTANCE _hInstance;
extern HWND      _hWnd;
extern POINT     _ptMouse;



