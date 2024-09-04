#include "GameNode.h"
#include "stdafx.h"

class MakeMiniMap : public GameNode
{
private:
	shared_ptr<GImage> m_bgImage;
	vector<shared_ptr<GImage>> m_Images;
	shared_ptr<GImage> m_miniMapBuffer;

public:
	HRESULT init(void)override;
	void release(void)override;
	void update(void)override;
	void render(HDC hdc)override;
	void input()override;
	void mouseInput(UINT message, LPARAM lParam)override;

	MakeMiniMap();
	~MakeMiniMap();
};

/*
2. �̴ϸ� �����
 �ΰ��� �������� �����
  1. ȭ������ ǥ�õǴ� GUI ������ ���� �̴ϸ�
  2. ȭ������ �׷����� ������ ���� ��üȭ�� �̴ϸ�

 �÷��̾��� �������� �̴ϸʿ����� Ȯ�� �� �� �յ���
*/

