#include "Cyndaquil.h"

void Cyndaquil::init()
{
	m_pt = POINT();
	m_state = Idle;
	m_image = make_shared<GImage>();
	m_image->init("Resource/Images/Object/Cyndaquil.bmp", 40, 40);
}

void Cyndaquil::release()
{
}

void Cyndaquil::render(HDC hdc)
{
	switch (m_state)
	{
	case Cyndaquil::Idle:
		GdiTransparentBlt
		(
			hdc,
			m_pt.x - 20 , m_pt.y - 20,                 // 시작점
			40, 40, // 그릴 사이즈
			m_image->getMemDC(),                         // 복사될 대상 메모리 DC
			0, 0,                           // 복사 시작지점
			20, 40,   // 복사 사이즈
			COLOR_MAGENTA                            // 제외할 색상
		);
		break;
	case Cyndaquil::Click:
		GdiTransparentBlt
		(
			hdc,
			m_pt.x - 20, m_pt.y - 20,                 // 시작점
			40, 40, // 그릴 사이즈
			m_image->getMemDC(),                         // 복사될 대상 메모리 DC
			20, 0,                           // 복사 시작지점
			20, 40,   // 복사 사이즈
			COLOR_MAGENTA                            // 제외할 색상
		);
		break;
	}
}

Cyndaquil::Cyndaquil()
{
	m_pt = POINT();
	m_state = Idle;
	m_image = make_shared<GImage>();
	m_image->init("Resource/Images/Object/Cyndaquil.bmp", 40, 40);
}

Cyndaquil::~Cyndaquil()
{
}
