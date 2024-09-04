#include "Dust.h"

Dust::Dust()
	: m_x(0), m_y(0), m_dx(0), m_dy(0), m_speed(0), m_alive(true)
{
}

Dust::Dust(double x, double y, double dx, double dy, int speed)
	: m_x(x), m_y(y), m_dx(dx), m_dy(dy), m_speed(speed), m_alive(true)
{
}

Dust::~Dust()
{
}

void Dust::init(void)
{
}

void Dust::release(void)
{
}

void Dust::update()
{
	if (m_alive)
	{
		m_x += m_dx * m_speed;
		m_y += m_dy * m_speed;
	}

	if (m_x > 805 || m_x < -5 || m_y > 805 || m_y < -5)
	{
		m_alive = false;
	}
}

void Dust::render(HDC hdc)
{
	if (m_alive)
	{
		DrawEllipseCenter(hdc, m_x, m_y, 10, 10);
	}
}
