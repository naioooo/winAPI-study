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
a. ��ũ
 �����̴� �ִϸ��̼� ����
 �����̱� �����ϰ� �������� ���⶧ �ڿ��������� �ٽ�
*/

