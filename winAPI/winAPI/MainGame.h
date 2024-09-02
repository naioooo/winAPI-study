#pragma once
#include "GameNode.h"
#include "stdafx.h"

class MainGame : public GameNode
{
private:
	RECT rc;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);
	void input();

	MainGame();
	~MainGame();
};

