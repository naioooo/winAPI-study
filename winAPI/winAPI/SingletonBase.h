#pragma once
/*
�̱��� : ������Ʈ ��ü���� 1���� �����ϴ� ��ü/ Ŭ���� -> �Ǵ� �����ϴ� Ŭ����
���� : �ν��Ͻ� X -> �޸� x
���� : ���յ�
*/

template<class T>
class SingletonBase
{
protected:
	static T* singleton;

	SingletonBase() {}
	~SingletonBase() {} // �Ҹ��� �̸� ����

public:
	static T* getSingleton(void);
	void releaseSingleton(void);
};

template<typename T>
T* SingletonBase<T>::singleton = nullptr; // �ʱ�ȭ�� nullptr�� ����

// �������� �Լ�
template<typename T>
T* SingletonBase<T>::getSingleton(void)
{
	if (!singleton)
		singleton = new T;

	return singleton;
}

template<typename T>
void SingletonBase<T>::releaseSingleton(void)
{
	if (!singleton)
	{
		delete singleton;
		singleton = 0;
	}
}
