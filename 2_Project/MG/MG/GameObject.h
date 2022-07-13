#pragma once

class GameObject : public Object
{
public:
	GameObject(string name = "GameObject");
	virtual ~GameObject();

public:
	Renderer* m_pRenderer;		//������
	Collision* m_pCollider;		//�ݶ��̴�
	Animation* m_pAnimation;	//�ִϸ��̼�
	Animator* m_pAnimator;		//�ִϸ�����(FSM)

	Object m_PrevObjState;		//���������ӿ����� ����

	int m_Layer;				//Collider üũ�ϴ� �з�
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