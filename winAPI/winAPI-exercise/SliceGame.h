#pragma once
#include "GameNode.h"
#include "stdafx.h"

struct Slice
{
	int m_num;

	int m_sourStartX;
	int m_sourStartY;

	int m_startX;
	int m_startY;

	int m_width;
	int m_height;
};

class SliceGame : public GameNode
{
private:
	shared_ptr<GImage> m_puzzleImage;

	vector<Slice> slices;
	vector<int> choiceSlices;
	int choiceSlice;


public:
	HRESULT init(void)override;
	void release(void)override;
	void update(void)override;
	void render(HDC hdc)override;
	void input()override;
	void mouseInput(UINT message, LPARAM lParam)override;

	SliceGame();
	~SliceGame();

	void gameReset();
	void generateSlice(shared_ptr<GImage> puzzleImage);
	void shuffleSlice();
	void checkPtCollision(POINT pt);
	bool checkFinish();

	void swapSlice(int a, int b);


	//1. 1���� ������ �����ϰ� �������� ����
	void cheat1();
	//2. �÷��̾ ���� 1���� ���߸鼭 ����Ǵ¹���
	void cheat2();

};

/*

1. �����̽� ����
 ġƮ �ʼ�
  1. 1���� ������ �����ϰ� �������� ����
  2. �÷��̾ ���� 1���� ���߸鼭 ����Ǵ¹���

  ȭ�� ���ʿ��� �������� ��� -> ȭ�� �����ʿ��� 9��е� �̹��� ����Ұ�
  9��е� �̹��� ���� �Ʒ� ������ĭ�� ����ĭ
  ������ �ϼ��Ǹ� ���ĺ��� ȿ���� �̹��� �߾ӿ��� ��Ÿ���� ó�� �� ��
*/