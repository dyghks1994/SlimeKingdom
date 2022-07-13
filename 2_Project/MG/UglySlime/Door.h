#pragma once

/// <summary>
/// Door 클래스
/// 자신과 연결된 스위치가 작동 되었을 때 열리는 문이다.
/// 인게임 내에 5개 존재할 예정이다. (스위치와 쌍을 이룸)
/// 
/// 최요환
/// 2021.02.23
/// </summary>

enum class DoorState
{
	Closed,		// 닫힌 상태
	Opening,	// 여는 중
	Opened,		// 열린 상태
};


class Door : public Gimmick
{
public:
	Door(float spawnPosX = 300.0f, float spawnPosY = 300.0f, string = "Door");
	~Door();

	// 애니메이션 얻기
	Animation* GetAnim();

	// 애니메이션 시작
	void StartAnim(Animation* anim);

	// 초기화
	virtual void Initialize(const float spawnPosX, const float spawnPosY);

	//업데이트
	virtual void Update();

	// 상자가 열려있는지 확인
	bool IsOpened();

	/// 연결된 스위치가 작동 했을 때 문을 여는 함수
	void OpenDoor();

protected:

private:
	// 스프라이트
	Sprite* m_Sprite[2];

	// 애니메이션
	Animation* m_Anim;

	DoorState m_State;		// 문 상태

	float m_DoorOpenTime;	// 문이 열리는 시간(속도)
	float openTimer;		// 타이머
};

