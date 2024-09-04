	#pragma once
#include "GameNode.h"
#include "stdafx.h"
#include "Dust.h"

struct Hole
{
	POINT pos;
	int radious;
};

class BlackHole : public GameNode
{
private:
	shared_ptr<GImage> m_bgImage;

	int m_genTime;
	int m_genCnt;

	Hole m_hole;
	vector<Dust> m_dusts;

public:
	HRESULT init(void)override;
	void release(void)override;
	void update(void)override;
	void render(HDC hdc)override;
	void input()override;
	void mouseInput(UINT message, LPARAM lParam)override;

	BlackHole();
	~BlackHole();

	void generateDust();
};

/*
4. 블랙홀
 무작위 생성되는 오브젝트 객체
 주변 오브젝트를 빨아들이는 블랙홀 구현
 오브젝트는 생성된 위치를 알기 쉽게 출력
*/

