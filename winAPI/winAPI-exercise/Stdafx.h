#pragma once
#pragma warning(disable : 4005) // ��ũ�� ������ ��� �����ϰڴ�

using namespace std;

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

//������ ����
#define RND RandomFunction::getSingleton()

// ��ũ��
#define WINNAME     (LPSTR)(TEXT("WindowAPI"))
#define WINSTART_X   200
#define WINSTART_Y   200
#define WINSIZE_X    800
#define WINSIZE_Y    800
#define WINSTYLE     WS_CAPTION | WS_SYSMENU

#define M_PI 3.14592f

// �⺻ ���� ��ũ�� ����
#define COLOR_BLACK      RGB(0, 0, 0)      // ������
#define COLOR_WHITE      RGB(255, 255, 255) // ���
#define COLOR_RED        RGB(255, 0, 0)    // ������
#define COLOR_GREEN      RGB(0, 255, 0)    // ���
#define COLOR_BLUE       RGB(0, 0, 255)    // �Ķ���
#define COLOR_YELLOW     RGB(255, 255, 0)  // �����
#define COLOR_CYAN       RGB(0, 255, 255)  // û�ϻ�
#define COLOR_MAGENTA    RGB(255, 0, 255)  // ����Ÿ��
#define COLOR_GRAY       RGB(128, 128, 128) // ȸ��
#define COLOR_DARK_RED   RGB(128, 0, 0)    // ��ο� ������
#define COLOR_DARK_GREEN RGB(0, 128, 0)    // ��ο� ���
#define COLOR_DARK_BLUE  RGB(0, 0, 128)    // ��ο� �Ķ���
#define COLOR_BODY       RGB(255, 235, 203) // ���

// ��ũ�� �Լ�
#define SAFE_DELETE(p)         {if(p) {delete (p); (p) = nullptr}}
#define SAFE_DELETE_ARRAY(p)   {if(p) {delete[] (p); (p) = nullptr}}
#define SAFE_RELEASE(p)        {if(p) {(p) -> release(); (p) = nullptr}}

// �������� extern�� �̳��� ������ �ִٰ� ������ִ� ��
extern HINSTANCE _hInstance;
extern HWND      _hWnd;
extern POINT     _ptMouse;



