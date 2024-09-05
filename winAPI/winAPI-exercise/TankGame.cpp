#include "TankGame.h"

HRESULT TankGame::init(void)
{
	GameNode::init();

	m_bgImage = make_shared<GImage>();
	m_bgImage->init("Resource/Images/Background/background.bmp", WINSIZE_X, WINSIZE_Y);

	m_tankImage = make_shared<GImage>();
	m_tankImage->init("Resource/Images/Object/tank.bmp", 450, 56);
		
	m_tankSprite = make_shared<GImage>();
	m_tankSprite->init(WINSIZE_X / 2, WINSIZE_Y / 2, 450, 56 * 2, 6, 2, true, COLOR_MAGENTA);

	StretchBlt
	(
		m_tankSprite->getMemDC(),
		0, 0,
		450, 56,
		m_tankImage->getMemDC(),
		0, 0,
		450, 56,
		SRCCOPY
	);
	StretchBlt
	(
		m_tankSprite->getMemDC(),
		0, 56,
		450, 56,
		m_tankImage->getMemDC(),
		449, 0,
		-450, 56,
		SRCCOPY
	);


	m_count = 0;
	m_index = 0;
	m_isLeft = false;

	return S_OK;
}

void TankGame::release(void)
{
	GameNode::release();
}

void TankGame::update(void)
{
	input();

	if (!m_isLeft)
	{
		m_count++;
		m_tankSprite->setFrameY(1);
		if (m_count % 5 == 0)
		{
			m_index--;

			if (m_index < 0)
			{
				m_index = m_tankSprite->getMaxFrameX();
			}

			m_tankSprite->setFrameX(m_index);
		}
	}
	else
	{
		m_count++;
		m_tankSprite->setFrameY(0);
		if (m_count % 5 == 0)
		{
			m_index++;

			if (m_index > m_tankSprite->getMaxFrameX())
			{
				m_index = 0;
			}

			m_tankSprite->setFrameX(m_index);
		}
	}

	GameNode::update();
}

void TankGame::render(HDC hdc)
{
	// 백버퍼 가져오기
	HDC memDC = this->getBackBuffer()->getMemDC();
	// 검은색 비트맵
	PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, WHITENESS);
	m_bgImage->render(memDC, 0, 0);

	m_tankSprite->frameRender(memDC, m_tankSprite->getX(), m_tankSprite->getY());
	m_tankSprite->render(memDC, 0, 0);

	this->getBackBuffer()->render(hdc, 0, 0);
}

void TankGame::input()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		m_isLeft = true;
		m_tankSprite->setX(m_tankSprite->getX() - 2.f);
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		m_isLeft = false;
		m_tankSprite->setX(m_tankSprite->getX() + 2.f);
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		m_tankSprite->setY(m_tankSprite->getY() - 2.f);
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		m_tankSprite->setY(m_tankSprite->getY() + 2.f);
	}

	
}

void TankGame::mouseInput(UINT message, LPARAM lParam)
{
}

TankGame::TankGame()
{
}

TankGame::~TankGame()
{
}

