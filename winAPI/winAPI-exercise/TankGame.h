#pragma once
#include "GameNode.h"
#include "stdafx.h"

class TankGame : public GameNode
{
private:
	shared_ptr<GImage> m_bgImage;
	shared_ptr<GImage> m_tankImage;
	shared_ptr<GImage> m_tankSprite;

	int m_count;
	int m_index;
	bool m_isLeft;

public:
	HRESULT init(void)override;
	void release(void)override;
	void update(void)override;
	void render(HDC hdc)override;
	void input()override;
	void mouseInput(UINT message, LPARAM lParam)override;

	TankGame();
	~TankGame();

};

/*
a. 탱크
 움직이는 애니메이션 구현
 움직이기 시작하고 움직임이 멈출때 자연스러움이 핵심
*/

