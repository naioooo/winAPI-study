#pragma once
#include "stdafx.h"
#include "WhackAChikorita.h"




HRESULT WhackAChikorita::init(void)
{
	GameNode::init();

	m_bgImage = make_shared<GImage>();
	m_bgImage->init("Resource/Images/Background/background.bmp", WINSIZE_X, WINSIZE_Y);

	m_cyndaquil = make_shared<Cyndaquil>();

	string genPoint = "{x=118 y=334} {x=154 y=346} {x=182 y=314} {x=192 y=327} {x=225 y=269} {x=248 y=213} {x=269 y=253} {x=300 y=203} {x=343 y=164} {x=367 y=148} {x=323 y=221} {x=387 y=218} {x=434 y=177} {x=446 y=172} {x=464 y=220} {x=465 y=233} {x=516 y=207} {x=525 y=232} {x=509 y=261} {x=557 y=271} {x=590 y=274} {x=566 y=293} {x=559 y=314} {x=582 y=322} {x=584 y=347} {x=629 y=356} {x=668 y=337} {x=656 y=317} {x=622 y=446} {x=644 y=464} {x=633 y=486} {x=582 y=463} {x=574 y=501} {x=565 y=543} {x=569 y=560} {x=536 y=580} {x=530 y=543} {x=486 y=548} {x=500 y=603} {x=477 y=624} {x=449 y=648} {x=436 y=611} {x=430 y=584} {x=379 y=602} {x=377 y=641} {x=344 y=639} {x=322 y=608} {x=322 y=585} {x=237 y=607} {x=214 y=571} {x=234 y=539} {x=198 y=522} {x=163 y=522} {x=194 y=475} {x=167 y=441} {x=120 y=449} {x=124 y=484}";
	
	parseCoordinates(genPoint, m_genPoints);
	m_genCnt = 0;
	m_genTime = RND->getFromIntTo(3, 10);
	m_score = 0;
	return S_OK;
}

void WhackAChikorita::release(void)
{
	GameNode::release();
	// 동적할당해제
}

void WhackAChikorita::update(void)
{
	CreateChikorita();

	for (auto& Chikorita : m_chikoritas)
	{
		Chikorita->update();
	}
	input();
	GameNode::update();
}

void WhackAChikorita::render(HDC hdc)
{
	// 백버퍼 가져오기
	HDC memDC = this->getBackBuffer()->getMemDC();
	// 검은색 비트맵
	PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, WHITENESS);

	m_bgImage->render(memDC, 0, 0);

	for (auto& Chikorita : m_chikoritas)
	{
		Chikorita->render(memDC);
	}

	m_cyndaquil->render(memDC);

	char strPT[120];
	wsprintf(strPT, "SCORE : %d ", m_score);
	TextOut(memDC, 10, 10, strPT, strlen(strPT));

	this->getBackBuffer()->render(hdc, 0, 0);
}

void WhackAChikorita::input()
{
}

void WhackAChikorita::parseCoordinates(const std::string& data, vector<POINT>& points)
{
	std::istringstream iss(data);
	std::string token;

	// 문자열을 토큰으로 나누고 POINT로 변환하여 벡터에 추가
	while (std::getline(iss, token, '}')) {
		if (token.empty()) continue;

		// 중괄호 제거
		size_t start = token.find('{');
		if (start != std::string::npos) {
			token = token.substr(start + 1);
		}

		// 좌표를 추출
		int x, y;
		char ignore;

		std::istringstream(token) >> ignore >> ignore >> x >> ignore >> ignore >> y;

		points.push_back(POINT{ x, y });
	}
}

void WhackAChikorita::mouseInput(UINT message, LPARAM lParam)
{
	_ptMouse.x = LOWORD(lParam);
	_ptMouse.y = HIWORD(lParam);
	m_cyndaquil->setPoint(_ptMouse);

	switch (message)
	{
	case WM_LBUTTONDOWN:
		CheckPtCollision(_ptMouse);
		m_cyndaquil->setState(Cyndaquil::Click);
		break;
	case WM_RBUTTONDOWN:

		break;
	case WM_LBUTTONUP:
		m_cyndaquil->setState(Cyndaquil::Idle);
		break;
	case WM_RBUTTONUP:

		break;
	case WM_MOUSEMOVE:
		break;
	}
}

WhackAChikorita::WhackAChikorita()
{
}

WhackAChikorita::~WhackAChikorita()
{
}

void WhackAChikorita::CreateChikorita()
{
	if (m_genCnt > m_genTime)
	{
		int rand = RND->getFromIntTo(0, m_genPoints.size() - 1);
		m_chikoritas.push_back(make_shared<Chikorita>(m_genPoints[rand].x, m_genPoints[rand].y));

		m_genCnt = 0;
		m_genTime = RND->getFromIntTo(100, 150);
	}
	m_genCnt++;
}

void WhackAChikorita::CheckPtCollision(POINT pt)
{
	for (auto& Chikorita : m_chikoritas)
	{
		if (Chikorita->getState() == Chikorita::Idle || Chikorita->getState() == Chikorita::Hurt)
		{
			if (PtInRect(&Chikorita->getRect(), pt))
			{
				Chikorita->setHp(Chikorita->getHp() - 50);

				if (Chikorita->getHp() <= 0)
				{
					m_score += 50;
					Chikorita->setState(Chikorita::Die);
				}
				else
				{
					Chikorita->setState(Chikorita::Hurt);
				}
			}
		}
	}

}

/*
API 프레임워크짜기
키매니저까지
*/