#pragma once
/*
싱글톤 : 프로젝트 전체에서 1개만 존재하는 객체/ 클래스 -> 또는 공유하는 클래스
장점 : 인스턴스 X -> 메모리 x
단점 : 결합도
*/

template<class T>
class SingletonBase
{
protected:
	static T* singleton;

	SingletonBase() {}
	~SingletonBase() {} // 소멸자 이름 수정

public:
	static T* getSingleton(void);
	void releaseSingleton(void);
};

template<typename T>
T* SingletonBase<T>::singleton = nullptr; // 초기화를 nullptr로 변경

// 가져오는 함수
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
