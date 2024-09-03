#pragma once
#include <Windows.h>
#include "GImage.h"

class GameNode
{
private:
	GImage* _backBuffer;
	void setBackBuffer();

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);
	virtual void input();
	virtual void mouseInput(UINT message, LPARAM lParam);

	GImage* getBackBuffer() { return _backBuffer; };

	LRESULT MainProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	GameNode();
	virtual ~GameNode();
};
