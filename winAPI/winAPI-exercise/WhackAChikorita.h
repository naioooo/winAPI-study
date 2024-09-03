#pragma once
#include "GameNode.h"
#include "stdafx.h"
#include "Chikorita.h"
#include "Cyndaquil.h"
#include <sstream> 

class WhackAChikorita : public GameNode
{
private:
	RECT rc;

	shared_ptr<GImage> m_bgImage;
	vector<shared_ptr<Chikorita>> m_chikoritas;
	shared_ptr<Cyndaquil> m_cyndaquil;

	vector<POINT> m_genPoints;
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

	WhackAChikorita();
	~WhackAChikorita();

	void parseCoordinates(const std::string& data, vector<POINT>& points);
	void CreateChikorita();
	void CheckPtCollision(POINT pt);
};

/*

�̹��������ʹ� OOP�� ������� �Ұ�

����

1. �δ��� ���� �����
 �δ����� ���� �ּ� 8�������� ����
 ȭ�鿡 ���� ���� ǥ��
 ����ó�� : �δ��� �ѹ�Ŭ�� -> ���� ���� -> ���� �δ����� Ŭ���϶����� ������ ������ �ȵȴ� -> �δ����� �����������

2. Ŭ���� ���
 �� �� ���� �������� �����ϴ� Ÿ���� ���콺�� ����
 Ÿ���� �����ϸ� ������ ȹ�� -> ���ŵ� Ÿ���� ���ڸ����� ���������Ѵ�
 �����ϴ� Ÿ���� ������ ������ ����ó���� �Ұ�
 �簢�� 50�� �� 100�� �ٰ��� 100��

 �ð��� 60�� ���� ���� / �ð��� ������ �ٽý����� �� �ְ� ���� ��

 �浹�Լ� ���� ����

3. 1 + 2 ���� �̹��� �߰�
 ��� + ���� �̹��� �߰� �ؿ��� �ȴ�.
 �δ��� ������ ���ö� �������� ��ġ


�������� IMAGE Ŭ������ ��޵� �Լ��� ����

*/