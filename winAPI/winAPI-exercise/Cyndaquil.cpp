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
			m_pt.x - 20 , m_pt.y - 20,                 // ������
			40, 40, // �׸� ������
			m_image->getMemDC(),                         // ����� ��� �޸� DC
			0, 0,                           // ���� ��������
			20, 40,   // ���� ������
			COLOR_MAGENTA                            // ������ ����
		);
		break;
	case Cyndaquil::Click:
		GdiTransparentBlt
		(
			hdc,
			m_pt.x - 20, m_pt.y - 20,                 // ������
			40, 40, // �׸� ������
			m_image->getMemDC(),                         // ����� ��� �޸� DC
			20, 0,                           // ���� ��������
			20, 40,   // ���� ������
			COLOR_MAGENTA                            // ������ ����
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
