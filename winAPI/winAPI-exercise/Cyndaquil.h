#pragma once
#include "stdafx.h"
#include "GImage.h"

class Cyndaquil
{

public:
	enum State
	{
		Idle,
		Click
	};

private:
	POINT m_pt;
	shared_ptr<GImage> m_image;
	State m_state;

public:
	void init();
	void release();
	void render(HDC hdc);

	State getState() const { return m_state; }
	void setPoint(POINT pt) { m_pt = pt; }
	void setState(State state) { m_state = state; }

	Cyndaquil();
	~Cyndaquil();
};

