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


	//1. 1개의 퍼즐을 제외하고 나머지는 정렬
	void cheat1();
	//2. 플레이어가 남은 1개를 맞추면서 종료되는버전
	void cheat2();

};

/*

1. 슬라이스 게임
 치트 필수
  1. 1개의 퍼즐을 제외하고 나머지는 정렬
  2. 플레이어가 남은 1개를 맞추면서 종료되는버전

  화면 왼쪽에는 원본사진 출력 -> 화면 오른쪽에는 9등분된 이미지 출력할것
  9등분된 이미지 제일 아래 오른쪽칸이 시작칸
  퍼즐이 완성되면 알파블랜딩 효과로 이미지 중앙에서 나타나게 처리 할 것
*/