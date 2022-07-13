#pragma once

class Object
{
public:
	Object();
	virtual ~Object();

public:
	Transform m_Transform;	//��ġ, ũ��, ȸ����
	bool m_Active;			//��� Ȱ��ȭ ����
	bool m_Visible;			//���ü� Ȱ��ȭ ����

protected:
	Object* m_Parent;			//�θ� ��ü
	vector<Object*> m_Children;	//�ڽ� ��ü

#pragma region Getter & Setter
public:
	void SetActive(bool active);
	void SetVisible(bool visibility);

	void SetParent(Object* parent);
	Object* GetParent() const;
	Object* GetChild(int num) const;
	int GetChildCount();

	Transform GetTransform();
#pragma endregion
};

inline Object::Object()
	:m_Parent(nullptr), m_Active(true), m_Visible(true)
{
	m_Children.clear();
}

inline Object::~Object()
{
	m_Parent = nullptr;
	m_Children.clear();
}

inline void Object::SetActive(bool active)
{
	m_Active = active;
}

inline void Object::SetVisible(bool visibility)
{
	m_Visible = visibility;
}

inline void Object::SetParent(Object* parent)
{
	//�̹� ������ �θ� �־��ٸ� �θ��� �ڽĸ�Ͽ��� ����
	if (m_Parent != nullptr)
	{
		for (vector<Object*>::iterator iter = m_Parent->m_Children.begin(); iter != m_Parent->m_Children.end(); iter++)
		{
			if (*iter == this)
			{
				m_Parent->m_Children.erase(iter);
				break;
			}
		}
	}
	m_Parent = parent;		//�θ� ����
	m_Parent->m_Children.push_back(this);	//�θ��� �ڽĸ�Ͽ� ���
}

inline Object* Object::GetParent() const
{
	return m_Parent;
}

inline Object* Object::GetChild(int num) const
{
	return m_Children.at(num);
}

inline int Object::GetChildCount()
{
	return m_Children.size();
}

inline Transform Object::GetTransform()
{
	if (m_Parent == nullptr) return m_Transform;
	return m_Parent->GetTransform() + m_Transform;
}