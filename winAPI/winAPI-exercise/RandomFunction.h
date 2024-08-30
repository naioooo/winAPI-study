#pragma once
#include "SingletonBase.h";

class RandomFunction : public SingletonBase <RandomFunction>
{
public:
	RandomFunction()
	{
		//API 공용함수
		//GetTickCount() API 함수로 OS가 부팅된 후 경과 시간을 체크 
		//단위는 밀리 세컨드, 규모가 크지않는 난수에 좋다
		srand(GetTickCount());
	}
	~RandomFunction() {}

	inline int getInt(int num)
	{
		return rand() % num;
	}
	
	inline int getFromIntTo(int fromNum, int toNum)
	{
		return rand() % (toNum - fromNum + 1) + fromNum;
	}

	float getFloat(void)
	{
		return (float)rand() / (float)RAND_MAX;
	}

	float getFloat(float num)
	{
		return (float)rand() / (float)RAND_MAX * num;
	}

	float getFromFloatTo(float fromNum, float toNum)
	{
		float rnd = (float)rand() / (float)RAND_MAX;
		return (rnd * (toNum - fromNum) + fromNum);
	}
};