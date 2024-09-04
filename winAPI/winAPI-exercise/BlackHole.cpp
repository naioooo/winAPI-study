#include "BlackHole.h"

HRESULT BlackHole::init(void)
{
	GameNode::init();

	m_bgImage = make_shared<GImage>();
	m_bgImage->init("Resource/Images/Background/background.bmp", WINSIZE_X, WINSIZE_Y);

	m_genCnt = 0;
	m_genTime = 50;

	m_hole.pos = { WINSIZE_X / 2, WINSIZE_Y / 2 };
	m_hole.radious = 100;

	return S_OK;
}

void BlackHole::release(void)
{
	GameNode::release();
}

void BlackHole::update(void)
{
	input();

	generateDust();

	for (auto& dust : m_dusts)
	{
		double posX = dust.getX();
		double posY = dust.getY();

		double dx = m_hole.pos.x - posX;
		double dy = m_hole.pos.y - posY;

		dust.setDx(dx / sqrt(dx * dx + dy * dy));
		dust.setDy(dy / sqrt(dx * dx + dy * dy));

		dust.update();
	}

	auto newEnd = std::remove_if
	(
		m_dusts.begin(),
		m_dusts.end(),
		[](Dust& dust) { return !dust.getAlive(); }
	);

	m_dusts.erase(newEnd, m_dusts.end());

	GameNode::update();
}

void BlackHole::render(HDC hdc)
{
	// 백버퍼 가져오기
	HDC memDC = this->getBackBuffer()->getMemDC();
	// 검은색 비트맵
	PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, WHITENESS);
	m_bgImage->render(memDC, 0, 0);

	DrawEllipseCenter(memDC, m_hole.pos.x, m_hole.pos.y, m_hole.radious, m_hole.radious);	

	for (auto& dust : m_dusts)
	{
		dust.render(memDC);
	}

	this->getBackBuffer()->render(hdc, 0, 0);
}

void BlackHole::input()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		m_hole.pos.x -= 3;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		m_hole.pos.x += 3;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		m_hole.pos.y -= 3;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		m_hole.pos.y += 3;
	}
}

void BlackHole::mouseInput(UINT message, LPARAM lParam)
{
}

BlackHole::BlackHole()
{
}

BlackHole::~BlackHole()
{
}

void BlackHole::generateDust()
{
	if (m_genCnt > m_genTime)
	{
		int cnt = 0;
		int max = RND->getFromIntTo(10, 20);

		while (true)
		{
			if (cnt > max)
			{
				break;
			}

			int posX = RND->getFromIntTo(100, 700);
			int posY = RND->getFromIntTo(100, 700);

			m_dusts.push_back(Dust(posX, posY, 0, 0, 1));

			cnt++;
		}

		m_genCnt = 0;
	}
	m_genCnt++;
}
