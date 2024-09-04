#pragma once
#include "Stdafx.h"

class Dust
{
private:
	double   m_x;
	double   m_y;
	double   m_dx;
	double   m_dy;
	int   m_speed;

	bool m_alive;

public:
	void init(void);
	void release(void);
	void update();
	void render(HDC hdc);

	Dust();
	Dust(double x, double y, double dx, double dy, int speed);
	~Dust();


	bool getAlive() { return m_alive; }
	double getX() { return m_x; }
	double getY() { return m_y; }
	void setDx(double dx) { m_dx = dx; }
	void setDy(double dy) { m_dy = dy; }

};

