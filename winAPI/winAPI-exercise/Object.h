#pragma once
#include "stdafx.h"
#include "GImage.h"



class Object
{
public:
	enum class TYPE
	{
		ELLIPSE,
		RECT,
		POLYGON
	};

	enum State
	{
		Idle,
		Die,
		None
	};

protected:
	TYPE  m_type;
	State m_state;
	int   m_dir;
	double m_speed;

	double m_gradient;
	double m_interceptX;
	double m_interceptY;

	POINT m_center;
	vector<POINT> m_points;

	RECT  m_rect;
	shared_ptr<GImage> m_image;

	int  m_Cnt;
public:
	virtual void init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	TYPE getType() const { return m_type; }
	RECT getRect() const { return m_rect; }
	State getState() const { return m_state; }
	POINT getCenter() const { return m_center; }

	void setState(State state) { m_state = state;}

	Object();
	~Object();

	double Parabola(double x, double gradient, double interceptX, double interceptY)
	{
		return (gradient * x) * (x - interceptX) + interceptY;
	}
};