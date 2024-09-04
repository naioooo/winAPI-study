#pragma once
#include "Stdafx.h"
#include "WhackAChikorita.h"
#include "ClayPigeonShooting.h"
#include "SliceGame.h"
#include "MakeMiniMap.h"
#include "WhirlwindBullet.h"
#include "BlackHole.h"
#include "EarthwormGame.h"


// ���� ����:

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

    wndClass.cbClsExtra = 0; //Ŭ���� ���� �޸�
    wndClass.cbWndExtra = 0; //������ ���� �޸�
    wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW); // ��׶���
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW); // Ŀ��
    wndClass.hIcon = LoadIcon(hInstance, IDI_APPLICATION); // ������
    wndClass.hInstance = _hInstance; // �ĺ���
    wndClass.lpfnWndProc = WndProc; // ������Ʈ ��� ������ ���ν���
    wndClass.lpszClassName = WINNAME; // Ŭ���� �̸�
    wndClass.lpszMenuName = NULL; // �޴��̸�
    wndClass.style = CS_HREDRAW | CS_VREDRAW; // ������ ��Ÿ��

    RegisterClass(&wndClass);

    _hWnd = CreateWindow
    (
        WINNAME, // Ŭ���� �ĺ���
        WINNAME, // ������ Ÿ��Ʋ �� �̸�
        WINSTYLE, // ������ ��Ÿ��
        WINSTART_X, //X
        WINSTART_Y, //Y
        WINSIZE_X, //�ʺ�
        WINSIZE_Y, // ����
        NULL, // �θ�������
        (HMENU)NULL, // �޴��ڵ�
        _hInstance, // �ν��Ͻ� ����
        NULL // �ڽ������츦 �����ϸ� ����
    );

    if (!_hWnd) // ���� ���н� ����
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

    //������ ũ������
    AdjustWindowRect(&rc, WINSTYLE, false);

    //�簢���� ������ ������ ������� ����
    SetWindowPos(_hWnd, NULL,
        x, y,
        (rc.right - rc.left),
        (rc.bottom - rc.top),
        SWP_NOZORDER | SWP_NOMOVE);
}