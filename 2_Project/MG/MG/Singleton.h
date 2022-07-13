#pragma once

template <class T>
class Singleton
{
protected:
    static T* m_Instance;    // 인스턴스 (단일 객체)

    Singleton() {}
    ~Singleton() {}

public:
    static T* GetInstance();
    void ReleaseInstance();
};

// 정적 변수인 인스턴스 초기화
template <class T>
T* Singleton<T>::m_Instance = 0;

// 인스턴스 가져오기
template<class T>
inline T* Singleton<T>::GetInstance()
{
    if (!m_Instance) m_Instance = new T;

    return m_Instance;
}

// 인스턴스 해제
template<class T>
inline void Singleton<T>::ReleaseInstance()
{
    if (m_Instance)
    {
        delete m_Instance;
        m_Instance = 0;
    }
}