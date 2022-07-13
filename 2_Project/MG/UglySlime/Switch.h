#pragma once
/// <summary>
/// Switch 클래스
/// 플레이어의 풀속성 공격에 맞으면
/// 인게임 내에서 어딘가에 위치하는 문을 여는 장치이다.
/// 
/// 게임내에서 총 5개의 스위치가 설치될 예정
/// 각가의 스위치가 연결된 문을 열어야 한다.
/// 
/// 최요환
/// 2021.02.23
/// </summary>

enum class SwitchState
{
	Off,
	On,
	Max,
};

class Door;

class Switch : public Gimmick
{
public:
	Switch(float spawnPosX = 300.0f, float spawnPosY = 300.0f, string = "Switch");
	~Switch();

	//스위치 값 설정
	void SetSwitchOn(const SwitchState val);

	// 문 설정
	void SetDoor(Door* door);

	// 초기화
	virtual void Initialize(const float spawnPosX, const float spawnPosY);

	// 업데이트
	virtual void Update();

	// 충돌 프로세스
	virtual void Collision();

	// 피격( 플레이어에게 공격당했을 때 )
	virtual void ReceiveAttack(Bullet* bulletObject);

	bool IsSwitchOn();

protected:

private:
	Door* m_Door;
	SwitchState m_SwitchState;	// 스위치가 On 인가?

	Sprite* m_Sprite[static_cast<int>(SwitchState::Max)];
};

