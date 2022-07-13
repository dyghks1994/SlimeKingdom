#pragma once

/// <summary>
/// Bullet 클래스
/// 플레이어나 몬스터가 공격할 때 사용하는 발사체
/// 속성과 이동방향, 속도 등을 설정해 줘야 한다.
/// 최요환
/// 2021.02.16
/// </summary>

class Bullet : public GameObject
{
public:
	Bullet(Unit* shooter);
	~Bullet();

	void Initialize();

	virtual void Update();

	void Collision();

	// 속성 설정
	UnitAttribute GetAttribute();
	void SetAttribute(const UnitAttribute attribute);

	// 방향 설정
	void SetDirection(Unit* shooter);

	// 발사 되었는지 체크
	bool GetIsFired() const;
	void SetIsFired(const bool val);

	// 발사
	void Shoot();

	// 이동
	void Move();

	// 발사체가 유효한 위치에 있는지 확인(카메라 영역 안)
	bool CheekValidPosition();

protected:

public:
	bool m_IsFired;						// 발사 되었나? 판별

	Unit* m_Shooter;					// 쏜 주인

	UnitAttribute m_Attribute;			// 발사체의 속성
	int m_AttackPower;					// 데미지

	float m_MoveSpeed;					// 이동 속도
	D2D1_POINT_2F m_Dir;				// 이동 방향


	// 태그? 나 뭐 이런걸로 생성된 발사체의 주체(플레이어 or 몬스터)가 누군지 알게 해야 한다.
	// ...

	// 그리고 충돌 받은 대상이 발사체의 주체가 누군지에 따라 처리를 해주자.

};

