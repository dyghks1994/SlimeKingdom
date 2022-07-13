#pragma once
#include "macro.h"

class Collision : public Object
{
public:
	Collision();

public:
	D2D1_SIZE_F m_Size;
	vector<Object*> m_Hits;
	bool m_IsTrigger;

public:
	virtual void SetSize(D2D1_SIZE_F size);
	virtual void ResetHits();

	virtual void Draw() = 0;
	virtual bool IsHit(Collision* target) = 0;
	virtual void ResistHits(Collision* target);
	virtual MG_Rect GetBoundingBox();
	
	virtual Transform GetTransform();
};

inline Collision::Collision()
{
	m_Size.width = 100.0f;
	m_Size.height = 100.0f;

	m_IsTrigger = false;
}

inline void Collision::SetSize(D2D1_SIZE_F size)
{
	m_Size = size;
}

inline void Collision::ResetHits()
{
	m_Hits.clear();
}

inline void Collision::ResistHits(Collision* target)
{
	m_Hits.push_back(target->GetParent());
	target->m_Hits.push_back(this->GetParent());
}

inline MG_Rect Collision::GetBoundingBox()
{
	D2D1_RECT_F myBB;
	myBB.left = m_Transform.Position.x - (m_Size.width * 0.5f);
	myBB.top = m_Transform.Position.y - (m_Size.height * 0.5f);
	myBB.right = m_Transform.Position.x + (m_Size.width * 0.5f);
	myBB.bottom = m_Transform.Position.y + (m_Size.height * 0.5f);

	Transform worldTransform = GetTransform();

	MG_Rect rect;
	rect.pt[0] = { myBB.left, myBB.top };
	rect.pt[1] = { myBB.right, myBB.top };
	rect.pt[2] = { myBB.right, myBB.bottom };
	rect.pt[3] = { myBB.left, myBB.bottom };

	for (int i = 0; i < 4; i++)
	{
		rect.pt[i] = GetResultPoint(rect.pt[i], worldTransform);
	}

	return rect;
}

inline Transform Collision::GetTransform()
{
	return m_Parent->GetTransform() + m_Transform;
}
