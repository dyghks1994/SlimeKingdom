#pragma once
class Bush : public Gimmick
{
public:
	Bush(float spawnPosX = 300.0f, float spawnPosY = 300.0f, bool fruit = false, string = "Bush");
	~Bush();

	// 초기화
	virtual void Initialize(const float spawnPosX, const float spawnPosY) override;

	// 업데이트
	virtual void Update() override;

	// 충돌처리
	virtual void Collision() override;

	// 이동(플레이어의 동작에 따라 밀린다)
	virtual void Move();
	virtual void Move(Player* player) override;

	// 피격( 플레이어에게 공격당했을 때 )
	virtual void ReceiveAttack(Bullet* bulletObject);

protected:


private:
	bool m_Fruit;			// 열매 유무(있으면 회복, 없으면 X)
	bool m_IsMoving;		// 움직일 수 있는가 없는가?(처음엔 false, Grass 속성 공격에 맞으면 활성화)
};

