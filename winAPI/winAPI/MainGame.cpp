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

	_nine = new GImage;
	_nine->init("Resource/Images/Background/background.bmp",
		WINSIZE_X / 2 - 200, WINSIZE_Y / 2- 200,
		3940, 586,
		10, 2,
		true, COLOR_MAGENTA
	);

	_count = 0;
	_index = 0;
	_isLeft = false;

	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();
	SAFE_DELETE(_bgImage);
	SAFE_DELETE(_plImage);
	SAFE_DELETE(_nine);
	// �����Ҵ�����
}

void MainGame::update(void)
{
	input();
	GameNode::update();
}

void MainGame::render(HDC hdc)
{
	// ����� ��������
	HDC memDC = this->getBackBuffer()->getMemDC();
	// ������ ��Ʈ��
	PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	_bgImage->render(memDC, 0, 0);
	//_bgImage->alphaRender(memDC, _alphaA);

	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		DrawRect(memDC, _rc);
	}

	_plImage->render(memDC, _rc.left, _rc.top);
	_plImage->alphaRender(memDC, _rc.left, _rc.top, _alphaA);

	_nine->frameRender(memDC, _nine->getX(), _nine->getY());

	this->getBackBuffer()->render(hdc, 0, 0);
}

void MainGame::input()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_isLeft = true;
		_nine->setX(_nine->getX() - 8.0f);

		_rc.left -= 3;
		_rc.right -= 3;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_isLeft = false;
		_nine->setX(_nine->getX() + 8.0f);

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


	if (_isLeft)
	{
		_count++;
		_nine->setFrameY(1);
		if (_count % 3 == 0)
		{
			_index--;
			if (_index < 0)
			{
				_index = 10;
			}

			_nine->setFrameX(_index);
		}
	}
	else
	{
		_count++;
		_nine->setFrameY(0);
		if (_count % 3 == 0)
		{
			_index++;
			if (_index > 10)
			{
				_index = 0;
			}

			_nine->setFrameX(_index);
		}
	}
}

MainGame::MainGame()
{
}

MainGame::~MainGame()
{
}

/*
����

1. �����̽� ����
 ġƮ �ʼ�
  1. 1���� ������ �����ϰ� �������� ����
  2. �÷��̾ ���� 1���� ���߸鼭 ����Ǵ¹���

  ȭ�� ���ʿ��� �������� ��� -> ȭ�� �����ʿ��� 9��е� �̹��� ����Ұ�
  9��е� �̹��� ���� �Ʒ� ������ĭ�� ����ĭ
  ������ �ϼ��Ǹ� ���ĺ��� ȿ���� �̹��� �߾ӿ��� ��Ÿ���� ó�� �� ��

2. �̴ϸ� �����
 �ΰ��� �������� �����
  1. ȭ������ ǥ�õǴ� GUI ������ ���� �̴ϸ�
  2. ȭ������ �׷����� ������ ���� ��üȭ�� �̴ϸ�

 �÷��̾��� �������� �̴ϸʿ����� Ȯ�� �� �� �յ���

3. ȸ���� �Ѿ� ����
 Ŭ���̾�Ʈ ������ �������� 360�� ȸ���� �ϸ� �߻��ϴ� �Ѿ��� ������ ��
 ��� ����

4. ��Ȧ
 ������ �����Ǵ� ������Ʈ ��ü
 �ֺ� ������Ʈ�� ���Ƶ��̴� ��Ȧ ����
 ������Ʈ�� ������ ��ġ�� �˱� ���� ���


��������
 ������ �����
  �����̴� ������ ������ ���� �̾����� ���¸� ��� �ִ�
   �� �������� ��ȣ�� ǥ��
  �����̴� ȭ����� ������ ��ġ���� ����
  ���� Ư���� Ű �Է��� ��� �����̴� ȭ�� �ȿ��� �����δ�
  ���� �ε����� �ðܾ� �ϰ� ���ʿ����� ����Ű�� ������ �����ؾ��Ѵ�

  ������� ������ �Ӹ��� ������ ư�ٰ� ���� Ʋ�� �ȵǰ� �Ӹ��� �ִ� ��ġ���� �̵��� �Ŀ� ������ȯ
  ������ ���۵ǰ� 10���Ŀ� ������ ���ڰ� ǥ�õ� �������� ������ �߰��ǰ� �����̰� �������� ������
  �ش��ϴ� ��ȣ�� ������ ������ Ŀ����

  �󸶳� �ڿ���������


����

�̹��� ������ ����
a. ��ũ
 �����̴� �ִϸ��̼� ����
 �����̱� �����ϰ� �������� ���⶧ �ڿ��������� �ٽ�

b. ĳ���� (Ű����)
 ���� �� + ���� ��
 ���� �� -> �Ʒ��� �̹����� GUIȭ ����(Ȥ�� ��ưȭ) �����Ų�� 
 ������ �̹��� : ���, ���, �̵� (�¿�), ��� (�¿�), �밢�� ���, ���� ���, �� ������, �¸� ����(�ʴ�����), ��ų Ŭ���̸��� ����





*/