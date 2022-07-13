#pragma once

template <class T>
class Singleton
{
protected:
    static T* m_Instance;    // �ν��Ͻ� (���� ��ü)

    Singleton() {}
    ~Singleton() {}

public:
    static T* GetInstance();
    void ReleaseInstance();
};

// ���� ������ �ν��Ͻ� �ʱ�ȭ
template <class T>
T* Singleton<T>::m_Instance = 0;

// �ν��Ͻ� ��������
template<class T>
inline T* Singleton<T>::GetInstance()
{
    if (!m_Instance) m_Instance = new T;

    return m_Instance;
}

// �ν��Ͻ� ����
template<class T>
inline void Singleton<T>::ReleaseInstance()
{
    if (m_Instance)
    {
        delete m_Instance;
        m_Instance = 0;
    }
}