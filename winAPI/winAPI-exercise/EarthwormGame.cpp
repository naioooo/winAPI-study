#include "EarthwormGame.h"

HRESULT EarthwormGame::init(void)
{
	GameNode::init();

	m_bgImage = make_shared<GImage>();
	m_bgImage->init("Resource/Images/Background/background.bmp", WINSIZE_X, WINSIZE_Y);

	double posX = 400;
	double posY = 200;
	int radious = 10;
	int speed = 1;
	m_wormBodies.push_back(WormBody(posX, posY, 0.0, -1.0, speed, radious));
	for (int i = 1; i < 50; i++)
	{
		m_wormBodies.push_back(WormBody(posX, m_wormBodies.back().getY() + (m_wormBodies.back().getRadious() * 2), 0.0f, -1.0f, speed, radious));
	}

	m_speedCnt = 0;
	m_speedTime = speed * 19;

	return S_OK;
}

void EarthwormGame::release(void)
{
	GameNode::release();
}

void EarthwormGame::update(void)
{
	input(); 
	checkCollisionMap();

	int preDx = 0;
	int preDy = 0;
	
	for (auto& wormBody : m_wormBodies)
	{
		if (wormBody.getCnt() >= 20)
		{
			if (preDx == 0 && preDy == 0)
			{
				preDx = wormBody.getDx();
				preDy = wormBody.getDy();
			}
			else
			{
				int tempX = wormBody.getDx();
				int tempY = wormBody.getDy();

				wormBody.setDx(preDx);
				wormBody.setDy(preDy);

				preDx = tempX;
				preDy = tempY;
			}
			wormBody.setCnt(0);
		}
		else
			wormBody.setCnt(wormBody.getCnt() + 1);


		wormBody.update();
	}
	GameNode::update();
}

void EarthwormGame::render(HDC hdc)
{
	// 백버퍼 가져오기
	HDC memDC = this->getBackBuffer()->getMemDC();
	// 검은색 비트맵
	PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, WHITENESS);
	m_bgImage->render(memDC, 0, 0);

	
	for (auto& wormBody : m_wormBodies)
	{
		wormBody.render(memDC);
	}

	this->getBackBuffer()->render(hdc, 0, 0);
}

void EarthwormGame::input()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		m_wormBodies[0].setDx(-1.0f);
		m_wormBodies[0].setDy(0.0f);
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		m_wormBodies[0].setDx(+1.0f);
		m_wormBodies[0].setDy(0.0f);
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		m_wormBodies[0].setDx(0.0f);
		m_wormBodies[0].setDy(-1.0f);
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		m_wormBodies[0].setDx(0.0f);
		m_wormBodies[0].setDy(+1.0f);
	}
}

void EarthwormGame::mouseInput(UINT message, LPARAM lParam)
{
}

EarthwormGame::EarthwormGame()
{
}

EarthwormGame::~EarthwormGame()
{
}

void EarthwormGame::checkCollisionMap()
{
	if (m_wormBodies[0].getX() < m_wormBodies[0].getRadious())
	{
		m_wormBodies[0].setDx(-m_wormBodies[0].getDx());
	}
	if (m_wormBodies[0].getX() > WINSIZE_X - m_wormBodies[0].getRadious())
	{
		m_wormBodies[0].setDx(-m_wormBodies[0].getDx());
	}
	if (m_wormBodies[0].getY() < m_wormBodies[0].getRadious())
	{
		m_wormBodies[0].setDy(-m_wormBodies[0].getDy());
	}
	if (m_wormBodies[0].getY() > WINSIZE_Y - m_wormBodies[0].getRadious())
	{
		m_wormBodies[0].setDy(-m_wormBodies[0].getDy());
	}
}
