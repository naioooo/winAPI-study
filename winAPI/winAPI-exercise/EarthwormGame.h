#pragma once
#include "GameNode.h"
#include "stdafx.h"
#include "WormBody.h"

class EarthwormGame : public GameNode
{
private:
	shared_ptr<GImage> m_bgImage;

	vector<WormBody> m_wormBodies;

	int m_speedCnt;
	int m_speedTime;

public:
	HRESULT init(void)override;
	void release(void)override;
	void update(void)override;
	void render(HDC hdc)override;
	void input()override;
	void mouseInput(UINT message, LPARAM lParam)override;

	EarthwormGame();
	~EarthwormGame();

	void checkCollisionMap();
};

/*
��������
 ������ �����
  �����̴� ������ ������ ���� �̾����� ���¸� ��� �ִ�
   �� �������� ��ȣ�� ǥ��
  �����̴� ȭ����� ������ ��ġ���� ����
  ���� Ư���� Ű �Է��� ��� �����̴� ȭ�� �ȿ��� �����δ�
  ���� �ε����� �ðܾ� �ϰ� ���ʿ����� ����Ű�� ������ �����ؾ��Ѵ�

  ������� ������ �Ӹ��� ������ ư�ٰ� ���� Ʋ�� �ȵǰ� �Ӹ��� �ִ� ��ġ���� �̵��� �Ŀ� ������ȯ
  ������ ���۵ǰ� 10���Ŀ� ������ ���ڰ� ǥ�õ� �������� ������ �߰��ǰ� �����̰� �������� ������
  �ش��ϴ� ��ȣ�� ������ ������ Ŀ����

  �󸶳� �ڿ���������
*/