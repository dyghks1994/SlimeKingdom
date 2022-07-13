#pragma once

class Object
{
public:
	Object();
	virtual ~Object();

public:
	Transform m_Transform;	//위치, 크기, 회전값
	bool m_Active;			//기능 활성화 여부
	bool m_Visible;			//가시성 활성화 여부

protected:
	Object* m_Parent;			//부모 객체
	vector<Object*> m_Children;	//자식 객체

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
	//이미 설정된 부모가 있었다면 부모의 자식목록에서 해제
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
	m_Parent = parent;		//부모 설정
	m_Parent->m_Children.push_back(this);	//부모의 자식목록에 등록
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