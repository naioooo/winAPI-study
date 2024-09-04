#pragma once
#include "Stdafx.h"
#include "WhackAChikorita.h"
#include "ClayPigeonShooting.h"
#include "SliceGame.h"
#include "MakeMiniMap.h"
#include "WhirlwindBullet.h"
#include "BlackHole.h"
#include "EarthwormGame.h"


// 전역 변수:

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowSize(int x, int y, int width, int height);

HINSTANCE _hInstance;
HWND      _hWnd;
POINT     _ptMouse;

WhackAChikorita*    _whackAChikorita;
ClayPigeonShooting* _clayPigeonShooting;
SliceGame*          _sliceGame;
MakeMiniMap*        _makeMiniMap;
WhirlwindBullet*    _whirlwindBullet;
BlackHole*          _blackHole;
EarthwormGame*      _earthwormGame;
 
int APIENTRY WinMain(_In_     HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_     LPSTR,
    _In_     int       nCmdShow)
{
    _whackAChikorita = new WhackAChikorita();
    _clayPigeonShooting = new ClayPigeonShooting();
    _sliceGame = new SliceGame();
    _makeMiniMap = new MakeMiniMap();
    _whirlwindBullet = new WhirlwindBullet();
    _blackHole = new BlackHole();
    _earthwormGame = new EarthwormGame();

    _hInstance = hInstance;

    WNDCLASS wndClass{};

    wndClass.cbClsExtra = 0; //클래스 여분 메모리
    wndClass.cbWndExtra = 0; //윈도우 여분 메모리
    wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW); // 백그라운드
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW); // 커서
    wndClass.hIcon = LoadIcon(hInstance, IDI_APPLICATION); // 아이콘
    wndClass.hInstance = _hInstance; // 식별자
    wndClass.lpfnWndProc = WndProc; // 롱포인트 펑션 윈도우 프로시져
    wndClass.lpszClassName = WINNAME; // 클래스 이름
    wndClass.lpszMenuName = NULL; // 메뉴이름
    wndClass.style = CS_HREDRAW | CS_VREDRAW; // 윈도우 스타일

    RegisterClass(&wndClass);

    _hWnd = CreateWindow
    (
        WINNAME, // 클래스 식별자
        WINNAME, // 윈도우 타이틀 바 이름
        WINSTYLE, // 윈도우 스타일
        WINSTART_X, //X
        WINSTART_Y, //Y
        WINSIZE_X, //너비
        WINSIZE_Y, // 높이
        NULL, // 부모윈도우
        (HMENU)NULL, // 메뉴핸들
        _hInstance, // 인스턴스 지정
        NULL // 자식윈도우를 생성하면 지정
    );

    if (!_hWnd) // 생성 실패시 종료
    {
        return false;
    }

    if (FAILED(_whackAChikorita->init()))
    {
        return 0;
    }
    if (FAILED(_clayPigeonShooting->init()))
    {
        return 0;
    }
    if (FAILED(_sliceGame->init()))
    {
        return 0;
    }
    if (FAILED(_makeMiniMap->init()))
    {
        return 0;
    }
    if (FAILED(_whirlwindBullet->init()))
    {
        return 0;
    }
    if (FAILED(_blackHole->init()))
    {
        return 0;
    }
    if (FAILED(_earthwormGame->init()))
    {
        return 0;
    }

    //setWindowSize(WINSTART_X, WINSTART_Y, WINSIZE_X, WINSIZE_Y);

    ShowWindow(_hWnd, nCmdShow);

    MSG message;

    while (GetMessage(&message, NULL, 0, 0))
    {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }

    _whackAChikorita->release();
    _clayPigeonShooting->release();
    _sliceGame->release();
    _makeMiniMap->release();
    _whirlwindBullet->release();
    _blackHole->release();
    _earthwormGame->release();
    UnregisterClass(WINNAME, hInstance);
    return (int)message.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    //return _whackAChikorita->MainProc(hwnd, message, wParam, lParam);
    //return _clayPigeonShooting->MainProc(hwnd, message, wParam, lParam);
    //return _sliceGame->MainProc(hwnd, message, wParam, lParam);
    //return _makeMiniMap->MainProc(hwnd, message, wParam, lParam);
    //return _whirlwindBullet->MainProc(hwnd, message, wParam, lParam);
    //return _blackHole->MainProc(hwnd, message, wParam, lParam);
    return _earthwormGame->MainProc(hwnd, message, wParam, lParam);
}

void setWindowSize(int x, int y, int width, int height)
{
    RECT rc = { 0, 0, width, height };

    //윈도우 크기조정
    AdjustWindowRect(&rc, WINSTYLE, false);

    //사각형의 정보를 윈도우 사이즈로 지정
    SetWindowPos(_hWnd, NULL,
        x, y,
        (rc.right - rc.left),
        (rc.bottom - rc.top),
        SWP_NOZORDER | SWP_NOMOVE);
}