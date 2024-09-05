#pragma once
#include "GameNode.h"
#include "stdafx.h"

class MainGame : public GameNode
{
private:
	GImage* _bgImage;
	GImage* _plImage;

	GImage* _nine;

	RECT _rc;

	int _countA, _countB;
	int _alphaA, _alphaB;

	bool _isAlphaIncrease;

	int _count;
	int _index;
	int _isLeft;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);
	void input();

	MainGame();
	~MainGame();
};

