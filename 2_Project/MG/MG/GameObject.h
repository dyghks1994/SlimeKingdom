#pragma once

class GameObject : public Object
{
public:
	GameObject(string name = "GameObject");
	virtual ~GameObject();

public:
	Renderer* m_pRenderer;		//랜더러
	Collision* m_pCollider;		//콜라이더
	Animation* m_pAnimation;	//애니메이션
	Animator* m_pAnimator;		//애니메이터(FSM)

	Object m_PrevObjState;		//이전프레임에서의 정보

	int m_Layer;				//Collider 체크하는 분류
	string m_Tag;				//tag

public:
	virtual void Update() {}
	void MGUpdate();
	void Draw();
	void SetSprite(Sprite* sprite);
	void SetAnimation(Animation* animation);
	void SetAnimator(Animator* animator);

	void SetBoxCollider();
	void SetCircleCollider();

	void CalculateReflectionVector(GameObject* target);
	D2D1_POINT_2F GetDirect();
	void prevUpdate();

	void SetLayer(int layer);

	D2D1_POINT_2F Normalized(D2D1_POINT_2F pos);
};