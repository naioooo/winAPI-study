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
4. ��Ȧ
 ������ �����Ǵ� ������Ʈ ��ü
 �ֺ� ������Ʈ�� ���Ƶ��̴� ��Ȧ ����
 ������Ʈ�� ������ ��ġ�� �˱� ���� ���
*/

