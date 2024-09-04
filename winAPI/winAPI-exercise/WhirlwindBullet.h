#pragma once
#include "GameNode.h"
#include "stdafx.h"
#include "Bullet.h"



class WhirlwindBullet : public GameNode
{
private:
	shared_ptr<GImage> m_bgImage;
	vector<Bullet> m_bullets;


	double m_shootAngle;
	int m_genTime;
	int m_genCnt;

public:
	HRESULT init(void)override;
	void release(void)override;
	void update(void)override;
	void render(HDC hdc)override;
	void input()override;
	void mouseInput(UINT message, LPARAM lParam)override;

	WhirlwindBullet();
	~WhirlwindBullet();

	void generateBullet();
};

/*
3. ȸ���� �Ѿ� ����
 Ŭ���̾�Ʈ ������ �������� 360�� ȸ���� �ϸ� �߻��ϴ� �Ѿ��� ������ ��
 ��� ����
*/

