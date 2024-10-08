#pragma once
#include "GameNode.h"
#include "Stdafx.h"

GameNode::GameNode()
{
}

GameNode::~GameNode()
{
}

void GameNode::setBackBuffer()
{
    _backBuffer = new GImage;
    _backBuffer->init(WINSIZE_X, WINSIZE_Y);
}

HRESULT GameNode::init(void)
{
    SetTimer(_hWnd, 1, 10, NULL);

    RND->init();
    KEYMANAGER->init();   
    setBackBuffer();

    return S_OK;
}

void GameNode::release(void)
{
    KillTimer(_hWnd, 1);

    RND->releaseSingleton();
    KEYMANAGER->releaseSingleton();
    SAFE_DELETE(_backBuffer);
}

void GameNode::update(void)
{
    InvalidateRect(_hWnd, NULL, false);
}

void GameNode::render(HDC hdc)
{
    // �ϴ°� ����
}

void GameNode::input()
{
}

LRESULT GameNode::MainProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;

    switch (message)
    {
    case WM_TIMER:
        this->update();
        break;
    case WM_CREATE:
        break;
    case WM_PAINT:
    {
        hdc = BeginPaint(hwnd, &ps);
        this->render(hdc);
        EndPaint(hwnd, &ps);
    }
    break;
    case WM_MOUSEMOVE:
        _ptMouse.x = LOWORD(lParam);
        _ptMouse.y = HIWORD(lParam);
        break;
    case WM_KEYDOWN:
    case WM_KEYUP:
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }

    return DefWindowProc(hwnd, message, wParam, lParam);
}
