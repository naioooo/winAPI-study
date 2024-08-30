#pragma once
#include "SingletonBase.h";

class RandomFunction : public SingletonBase <RandomFunction>
{
public:
	RandomFunction()
	{
		//API �����Լ�
		//GetTickCount() API �Լ��� OS�� ���õ� �� ��� �ð��� üũ 
		//������ �и� ������, �Ը� ũ���ʴ� ������ ����
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