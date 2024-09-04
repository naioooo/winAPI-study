#include "Bullet.h"

Bullet::Bullet()
	: m_x(0), m_y(0), m_dx(0), m_dy(0), m_speed(0), m_alive(true)
{
}

Bullet::Bullet(double x, double y, double dx, double dy, int speed)
	: m_x(x), m_y(y), m_dx(dx), m_dy(dy), m_speed(speed), m_alive(true)
{
}

Bullet::~Bullet()
{
}

void Bullet::init(void)
{
}

void Bullet::release(void)
{
}

void Bullet::update()
{
	if (m_alive)
	{
		m_x += m_dx * m_speed;
		m_y += m_dy * m_speed;
	}

	if (m_x > 820 || m_x < -20 || m_y > 820 || m_y < -20)
	{
		m_alive = false;
	}
}

void Bullet::render(HDC hdc)
{
	if (m_alive)
	{
		DrawEllipseCenter(hdc, m_x, m_y, 20, 20);
	}
}
