#pragma once
#include <windows.h>
#include "stdafx.h"
#include "GImage.h"

class Chikorita
{
public:
	enum State
	{
		Idle = 0,
		Up,
		Hurt,
		Die,
		None
	};

private:
	State m_state;
	RECT  m_rect;
	shared_ptr<GImage> m_image;

	int   m_Hp;
	int  m_Cnt;

public:
	void init();
	void init(int x, int y);
	void release();
	void update();
	void render(HDC hdc);

	RECT getRect() const { return m_rect; }
	int getHp() const { return m_Hp; }
	State getState() const { return m_state; }

	void setHp(int hp) { m_Hp = hp; }
	void setState(State state) { m_state = state; m_Cnt = 0;}

	Chikorita(); 
	Chikorita(int x, int y);
	~Chikorita();

};

