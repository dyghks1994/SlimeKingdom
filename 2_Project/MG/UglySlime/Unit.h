#pragma once

/// Unit 클래스
/// 게임에 등장하는 유닛들
/// 최요환, 김경재
/// 2021.02.15


#include "GameObject.h"

#define MAX_BULLET_SIZE 5		// 발사체 최대 사이즈

enum class UnitAttribute 
{
	None,		// 무속성
	Water,		// 물속성
	Fire,		// 불속성
	Grass,		// 풀속성

	AttributeNum
};

class Bullet;

class Unit : public GameObject
{
public:
	Unit(string = "GameObject");
	~Unit();


	//============================================
	// Geeter / Setter
	//============================================
	int GetLife() const;
	void SetLife(const int life);

	int GetCurrentHp() const;
	void SetCurrentHp(const int hp);

	int GetMaxHp() const;
	void SetMaxHp(const int hp);

	D2D1_POINT_2F GetLookVector();

	float GetMoveSpeed() const;
	void SetMoveSpeed(const float moveSpeed);
	
	float GetShootSpeed() const;
	void SetShootSpeed(const float attackSpeed);

	UnitAttribute GetAttribute() const;

	// 이동
	virtual void Move() {}

	// 충돌
	virtual void Collision() {}

	// 발사
	virtual void Shoot() {}

	// 피격
	virtual void ReceiveAttack() {}
	virtual void ReceiveAttack(GameObject* gameObject) {}

	// 사망했나?
	virtual bool IsDead() const { return false; }

protected:
	int m_Life;							// 라이프
	int m_MaxHp;						// 최대 생명력
	int m_CurrentHp;					// 현재 생명력

	D2D_POINT_2F m_LookVector;			// 바라보고 있는 방향
	float m_MoveSpeed;					// 이동속도

	bool m_IsCanAttack;					// 현재 공격가능한지 판단
	float m_AttackSpeed;				// 공격속도
	float m_DelayCount;					// 딜레이 카운트 변수

	UnitAttribute m_Attribute;			// 유닛의 속성	(무속, 불, 물, 풀)
	Bullet* m_Bullets[MAX_BULLET_SIZE];	// 현재 가지고 있는 스킬(탄환 정도..)

private:

};