#pragma once
#pragma warning(disable : 4005) // 매크로 관련한 경고를 무시하겠다

// 코드 및 상수 및 제어 OS 레벨에서 관리
#include <SDKDDKVer.h>

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h> 
#include <memory.h>
//memcpy() / memset()
#include <stdio.h>
#include <tchar.h>
#include <assert.h>

// C++ 런타임 헤더 파일입니다.
#include <iostream>
// stl 다양한 기능 // 정밀도가 높다
// OS 와 독립적으로 동작을 한다
#include <chrono> 
#include <string> 
#include <random>
#include <vector>
#include <map>
// 일반적인 상황에선 해시를 사용해 검색하기에 map보다 빠르다
// 중복데이터를 허용하지 않기 때문이다
// 유사데이터가 많다면 해시 충돌 발생 여부가 항상 존재한다
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

//내가 만든 헤더 너를위해
#include "CommonMacroFunction.h"
#include "RandomFunction.h"
#include "KeyManager.h"

//디자인 패턴
#define RND RandomFunction::getSingleton()
#define KEYMANAGER KeyManager::getSingleton()

// 매크로
#define WINNAME     (LPSTR)(TEXT("WindowAPI"))
#define WINSTART_X   100
#define WINSTART_Y   100
#define WINSIZE_X    800
#define WINSIZE_Y    800
#define WINSTYLE     WS_CAPTION | WS_SYSMENU

// 매크로 함수
#define SAFE_DELETE(p)         {if(p) {delete (p); (p) = nullptr}}
#define SAFE_DELETE_ARRAY(p)   {if(p) {delete[] (p); (p) = nullptr}}
#define SAFE_RELEASE(p)        {if(p) {(p) -> release(); (p) = nullptr}}

// 전역변수 extern은 이놈이 전역에 있다고 명시해주는 것
extern HINSTANCE _hInstance;
extern HWND      _hWnd;
extern POINT     _ptMouse;



