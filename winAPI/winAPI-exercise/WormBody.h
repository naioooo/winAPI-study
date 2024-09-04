#pragma once
#include "Stdafx.h"

struct Slope
{
	double dx;
	double dy;
};

class WormBody
{
private:
	double m_x;
	double m_y;

	double m_dx;
	double m_dy;

	int m_speed;
	int m_radious;

	int  m_cnt;
	int  m_time;

	bool m_alive;

	queue<Slope> slopes;

public:
	void init(void);
	void release(void);
	void update();
	void render(HDC hdc);

	WormBody();
	WormBody(double x, double y, double dx, double dy, int speed, int m_radious);
	~WormBody();

	bool getAlive() { return m_alive; }
	double getX() { return m_x; }
	double getY() { return m_y; }
	double getDx() { return m_dx; }
	double getDy() { return m_dy; }
	int getRadious() { return m_radious; }
	int getCnt() { return m_cnt; }

	void setDx(double dx) { m_dx = dx; }
	void setDy(double dy) { m_dy = dy; }
	void setRadious(int radious) { m_radious = radious; }
	void setCnt(int cnt) { m_cnt = cnt; }
};

