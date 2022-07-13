#pragma once

/// <summary>
/// Box 클래스
/// 클리어에 필요한 보석을 얻을 수 있다.
/// 
/// 플레이어가 와서 상호작용하면 열린다.
/// </summary>

enum class BoxState
{
	Closed,		// 닫힌 상태
	Opening,	// 여는 중
	Opened,		// 열린 상태
};

enum class JewelryAttribute
{
	Water = 1,
	Fire  = 2,
	Grass = 3,
	Max   = 4,
};

class Box : public Gimmick
{
public:
	Box(float spawnPosX = 300.0f, float spawnPosY = 300.0f, JewelryAttribute jewelry = JewelryAttribute::Water, string = "Box");
	~Box();

	// Getter
	BoxState GetState();

	// 초기화
	virtual void Initialize(const float spawnPosX, const float spawnPosY, const JewelryAttribute jewelry);

	virtual void Reset();

	// 업데이트
	virtual void Update();

	// 충돌처리
	virtual void Collision() override;

	// 상자가 열려있는지 확인
	bool IsOpened();

	// 상자를 여는 함수
	void OpenBox();

protected:

private:
	// 애니메이션
	Animation* m_Anim;

	BoxState m_BoxState;					// 상자의 상태 판별 변수
	JewelryAttribute m_JewelryAttribute;	// 상자가 가지고 있는 보석의 속성

	float m_BoxOpenTime;					// 박스가 열리는 시간(속도)
	float openTimer;						// 타이머

};

