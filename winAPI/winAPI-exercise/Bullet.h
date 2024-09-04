#pragma once
#include "stdafx.h"

class Bullet
{
private:
	double   m_x;
	double   m_y;
	double   m_dx;
	double   m_dy;
	int   m_speed;

	bool m_alive;
public:
	Bullet();
	Bullet(double x, double y, double dx, double dy, int speed);
	~Bullet();

	void init(void);
	void release(void);
	void update();
	void render(HDC hdc);

	bool getAlive() { return m_alive; }
};

