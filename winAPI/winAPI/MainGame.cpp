#pragma once
#include "stdafx.h"
#include "MainGame.h"

HRESULT MainGame::init(void)
{
	GameNode::init();

	_bgImage = new GImage;
	_bgImage->init("Resource/Images/Background/background.jpg", WINSIZE_X, WINSIZE_Y);
	_plImage = new GImage;
	_plImage->init("Resource/Images/Object/thief.png", WINSIZE_X, WINSIZE_Y);

	_rc = RectMakeCenter(WINSIZE_X / 2 - 500, WINSIZE_Y / 2 + 200, 40, 40);

	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();
	SAFE_DELETE(_bgImage);
	SAFE_DELETE(_plImage);
	// 동적할당해제
}

void MainGame::update(void)
{
	input();
	GameNode::update();
}

void MainGame::render(HDC hdc)
{
	// 백버퍼 가져오기
	HDC memDC = this->getBackBuffer()->getMemDC();
	// 검은색 비트맵
	PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	_bgImage->render(memDC, 0, 0);

	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		DrawRect(memDC, _rc);
	}

	_plImage->render(memDC, _rc.left, _rc.top);

	this->getBackBuffer()->render(hdc, 0, 0);
}

void MainGame::input()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_rc.left -= 3;
		_rc.right -= 3;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_rc.left += 3;
		_rc.right += 3;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_rc.top -= 3;
		_rc.bottom -= 3;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_rc.top += 3;
		_rc.bottom += 3;
	}
}

MainGame::MainGame()
{
}

MainGame::~MainGame()
{
}

/*
API 프레임워크짜기
키매니저까지
*/