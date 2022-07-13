#pragma once

/// <summary>
/// Rock 클래스
/// 초기 상태엔 움직임 X
/// 풀 속성 공격에 맞으면 움직임 O(플레이어가 밀어야함)
/// 불 속성 공격에 맞으면 파괴
/// 물 속성 공격에 맞으면 아무 변화 X
/// </summary>

class Rock : public Gimmick
{
public:
	Rock(float spawnPosX = 300.0f, float spawnPosY = 300.0f, string = "Rock");
	~Rock();

	// 초기화
	virtual void Initialize(const float spawnPosX, const float spawnPosY) override;

	// 업데이트
	virtual void Update() override;

	// 충돌처리
	virtual void Collision() override;

	// 이동(이동가능 상태라면 플레이어의 동작에 따라 밀린다)
	virtual void Move(Player* player) override;

	// 피격( 플레이어에게 공격당했을 때 )
	virtual void ReceiveAttack(Bullet* bulletObject);

protected:


private:
	bool m_IsMoving;		// 움직일 수 있는가 없는가?(처음엔 false, Grass 속성 공격에 맞으면 활성화)
};


