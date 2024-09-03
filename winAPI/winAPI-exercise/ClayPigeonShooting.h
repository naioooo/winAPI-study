#pragma once
#include "GameNode.h"
#include "stdafx.h"
#include "CPolygon.h"
#include "CRect.h"
#include "CEllipse.h"
#include <sstream> 

class ClayPigeonShooting : public GameNode
{
private:
	shared_ptr<GImage> m_bgImage;

	vector<shared_ptr<Object>> m_objects;


	bool m_reGame;

	int m_gameTime;
	int m_genTime;
	int m_genCnt;
	int m_score;

public:
	HRESULT init(void)override;
	void release(void)override;
	void update(void)override;
	void render(HDC hdc)override;
	void input()override;
	void mouseInput(UINT message, LPARAM lParam)override;

	ClayPigeonShooting();
	~ClayPigeonShooting();

	void GameReset();
	void CreateObject();
	void CheckPtCollision(POINT pt);
};

/*

2. 클레이 사격
 좌 우 에서 무작위로 출현하는 타켓을 마우스로 제거
 타켓을 제거하면 점수를 획득 -> 제거된 타겟을 그자리에서 떨어져야한다
 등장하는 타겟의 종류는 무작위 도형처리를 할것
 사각형 50점 원 100점 다각형 100점

 시간은 60초 동안 지속 / 시간이 끝나면 다시시작할 수 있게 만들 것

 충돌함수 봉인 해제
*/