#pragma once
#include "GameNode.h"
#include "stdafx.h"
#include <sstream> 

class ClayPigeonShooting : public GameNode
{
private:
	shared_ptr<GImage> m_bgImage;

public:
	HRESULT init(void)override;
	void release(void)override;
	void update(void)override;
	void render(HDC hdc)override;
	void input()override;
	void mouseInput(UINT message, LPARAM lParam)override;

	ClayPigeonShooting();
	~ClayPigeonShooting();

	//void parseCoordinates(const std::string& data, vector<POINT>& points);
	//void CreateChikorita();
	//void CheckPtCollision(POINT pt);
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