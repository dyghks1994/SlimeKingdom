#pragma once
/// <summary>
/// 석상 클래스
/// 물, 불, 풀, 킹슬라임석상 4개 존재
/// 
/// 플레이어가 보석을 획득해서 각 속성 석상과 상호작용하면 이미지가 바뀌어야 한다.
/// 
/// 물, 불, 풀 석상이 모두 활성화 되면 게임 클리어
/// 
/// 최요환
/// 2021.02.24
/// </summary>

enum class StatueType
{
	Water,
	Fire,
	Grass,
	King,
};

class Statue : public Gimmick
{
public:
	Statue(float spawnPosX = 300.0f, float spawnPosY = 300.0f, StatueType type = StatueType::Water, string str= "Statue");
	~Statue();

	// 초기화
	virtual void Initialize(const float spawnPosX, const float spawnPosY) override;

	// 업데이트
	virtual void Update() override;

	// 충돌처리
	virtual void Collision() override;

	// 보석 장착
	void AttachJewelry(uint bag);

	// 석상의 보석 장착 유무 판별
	bool IsAttachedJewelry();

protected:

private:
	StatueType m_Type;			//	생성할 때 지정할 석상의 타입
	bool m_AttachedJewelry;		// 석상이 보석을 가지고 있나 판별하는 변수
};

