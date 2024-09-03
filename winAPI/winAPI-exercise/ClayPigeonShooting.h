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

2. Ŭ���� ���
 �� �� ���� �������� �����ϴ� Ÿ���� ���콺�� ����
 Ÿ���� �����ϸ� ������ ȹ�� -> ���ŵ� Ÿ���� ���ڸ����� ���������Ѵ�
 �����ϴ� Ÿ���� ������ ������ ����ó���� �Ұ�
 �簢�� 50�� �� 100�� �ٰ��� 100��

 �ð��� 60�� ���� ���� / �ð��� ������ �ٽý����� �� �ְ� ���� ��

 �浹�Լ� ���� ����
*/