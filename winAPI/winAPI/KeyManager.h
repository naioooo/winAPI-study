#pragma once
#include "Stdafx.h"
#include "SingletonBase.h"

#define KEY_MAX 256

class KeyManager : public SingletonBase<KeyManager>
{
private:
	//BOOL _keyUp[KEY_MAX];
	//BOOL _keyDown[KEY_MAX];

	bitset<KEY_MAX> _keyUp;
	bitset<KEY_MAX> _keyDown;

public:
	HRESULT init(void);

	bool isOnceKeyUp(int key);
	bool isOnceKeyDown(int key);
	bool isStayKeyDown(int key);
	bool isToggleKey(int key);

	bitset<KEY_MAX> getKeyUp(void) const { return _keyUp; }
	bitset<KEY_MAX> getKeyDown(void) const { return _keyDown; }

	void setKeyUp(int key, bool state) { _keyUp.set(key, state); };
	void setKeyDown(int key, bool state) { _keyDown.set(key, state); };

	KeyManager();
	~KeyManager();
};

