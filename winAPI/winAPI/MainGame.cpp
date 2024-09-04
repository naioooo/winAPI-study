#pragma once
#include "stdafx.h"
#include "MainGame.h"

HRESULT MainGame::init(void)
{
	GameNode::init();

	_bgImage = new GImage;
	_bgImage->init("Resource/Images/Background/background.bmp", WINSIZE_X, WINSIZE_Y);
	_plImage = new GImage;
	_plImage->init("Resource/Images/Object/Cyndaquil.bmp", WINSIZE_X, WINSIZE_Y);

	_rc = RectMakeCenter(WINSIZE_X / 2 - 500, WINSIZE_Y / 2 + 200, 40, 40);

	_countA = 0;
	_countB = 0;
	_alphaA = 0;
	_alphaB = 0;

    _isAlphaIncrease = false;

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
	//_bgImage->alphaRender(memDC, _alphaA);

	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		DrawRect(memDC, _rc);
	}

	_plImage->render(memDC, _rc.left, _rc.top);

	_plImage->alphaRender(memDC, _rc.left, _rc.top, _alphaA);

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

	_countA++;
	if (_countA % 3 == 0)
	{
		_alphaA++;
		if (_alphaA >= 255) _alphaA = 0;
	}

	_countB++;
	if (_countB % 3 == 0)
	{
		_alphaB += 5;
		if (_alphaB >= 255) _alphaB = 0;
	}
}

MainGame::MainGame()
{
}

MainGame::~MainGame()
{
}

/*
과제

1. 슬라이스 게임
 치트 필수
  1. 1개의 퍼즐을 제외하고 나머지는 정렬
  2. 플레이어가 남은 1개를 맞추면서 종료되는버전

  화면 왼쪽에는 원본사진 출력 -> 화면 오른쪽에는 9등분된 이미지 출력할것
  9등분된 이미지 제일 아래 오른쪽칸이 시작칸
  퍼즐이 완성되면 알파블랜딩 효과로 이미지 중앙에서 나타나게 처리 할 것

2. 미니맵 만들기
 두가지 버전으로 만들기
  1. 화면위에 표시되는 GUI 형태의 작은 미니맵
  2. 화면위에 그려지는 투명도를 가진 전체화면 미니맵

 플레이어의 움직임을 미니맵에서도 확인 할 수 잇도록

3. 회오리 총알 구현
 클라이언트 중점을 기준으로 360도 회전을 하며 발사하는 총알을 구현할 것
 양식 자유

4. 블랙홀
 무작위 생성되는 오브젝트 객체
 주변 오브젝트를 빨아들이는 블랙홀 구현
 오브젝트는 생성된 위치를 알기 쉽게 출력


도전과제
 지렁이 만들기
  지렁이는 구슬에 꼬리를 물고 이어지는 형태를 띄고 있다
   각 구슬마다 번호를 표기
  지렁이는 화면밖의 무작위 위치에서 등장
  또한 특별한 키 입력이 없어도 지렁이는 화면 안에서 움직인다
  벽에 부딪히면 팅겨야 하고 왼쪽오른쪽 방향키로 조종이 가능해야한다

  따라오는 구슬은 머리가 방향을 튼다고 같이 틀면 안되고 머리가 있던 위치까지 이동한 후에 방향전환
  게임이 시작되고 10초후에 임의의 숫자가 표시된 아이템이 게임이 추가되고 지렁이가 아이템을 먹으면
  해당하는 번호의 지렁이 구슬이 커진다

  얼마나 자연스러운지
*/