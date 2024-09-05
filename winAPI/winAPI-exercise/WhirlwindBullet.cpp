#include "WhirlwindBullet.h"

HRESULT WhirlwindBullet::init(void)
{
	GameNode::init();

	m_bgImage = make_shared<GImage>();
	m_bgImage->init("Resource/Images/Background/background.bmp", WINSIZE_X, WINSIZE_Y);

	m_genCnt = 0;
	m_genTime = 3.f;
	m_shootAngle = 0;

	return S_OK;
}

void WhirlwindBullet::release(void)
{
	GameNode::release();
}

void WhirlwindBullet::update(void)
{
	generateBullet();

	for (auto& bullet : m_bullets)
	{
		bullet.update();
	}

	auto newEnd = std::remove_if
	(
		m_bullets.begin(),
		m_bullets.end(),
		[](Bullet& bullet)	{ return !bullet.getAlive();}
	);

	m_bullets.erase(newEnd, m_bullets.end());

	input();
	GameNode::update();
}

void WhirlwindBullet::render(HDC hdc)
{
	// 백버퍼 가져오기
	HDC memDC = this->getBackBuffer()->getMemDC();
	// 검은색 비트맵
	PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, WHITENESS);
	m_bgImage->render(memDC, 0, 0);

	for (auto& bullet : m_bullets)
	{
		bullet.render(memDC);
	}

	this->getBackBuffer()->render(hdc, 0, 0);
}

void WhirlwindBullet::input()
{
}

void WhirlwindBullet::mouseInput(UINT message, LPARAM lParam)
{
	_ptMouse.x = LOWORD(lParam);
	_ptMouse.y = HIWORD(lParam);

	switch (message)
	{
	case WM_LBUTTONDOWN:
		break;
	case WM_RBUTTONDOWN:
		break;
	case WM_LBUTTONUP:
		break;
	case WM_RBUTTONUP:

		break;
	case WM_MOUSEMOVE:
		break;
	}
}

WhirlwindBullet::WhirlwindBullet()
{
}

WhirlwindBullet::~WhirlwindBullet()
{
}

void WhirlwindBullet::generateBullet()
{
	if (m_genCnt > m_genTime)
	{
		POINT pos = { WINSIZE_X / 2, WINSIZE_Y / 2 };


		double dx = cos(m_shootAngle);
		double dy = sin(m_shootAngle);
		int speed = 1;

		m_bullets.push_back(Bullet(pos.x, pos.y, dx, dy, speed));

		m_genCnt = 0;

	}

	m_shootAngle += .3f;
	if (m_shootAngle >= 2 * 3.14592f) m_shootAngle = 0;

	m_genCnt++;
}
