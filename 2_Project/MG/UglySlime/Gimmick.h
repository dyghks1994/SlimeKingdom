#pragma once
/// <summary>
/// Gimmick 클래스
/// 게임에 배치되는 나무, 바위, 돌, 상자 따위들
/// 플레이어의 공격 속성에 따라 특정 액션을 취하거나
/// 파괴 가능하다.
/// 
/// 최요환
/// 2021.02.21
/// </summary>

class Gimmick : public GameObject
{
public:
	Gimmick(string name = "Gimmick");
	virtual ~Gimmick();

	// 초기화
	virtual void Initialize(const float spawnPosX, const float spawnPosY) {}

	// 업데이트
	virtual void Update() {}

	virtual void Reset() {}

	bool IsDestroyed();

	virtual void Collision() {}

	// 이동(플레이어의 동작에 따라 밀린다)
	virtual void Move() {}
	virtual void Move(Player* player) {}	// Wall 이나 Box는 안쓰겠지만...

	// 피격( 플레이어에게 공격당했을 때 )
	virtual void ReceiveAttack(GameObject* gameObject) {}	// Wall 이나 Box는 안쓰겠지만...

protected:
	float m_MoveSpeed;		// 이동 속도(플레이어가 밀때 밀리는 양)
	bool m_IsDestroyed;		// 파괴 여부 판별 변수
private:
};

