#pragma once
/// <summary>
/// 표지판 클래스
/// 맵에 곳곳에 표지판이 있다.
/// 표지판에 다가가면 화면에 게임의 힌트가 표시된다.(UI)
/// 
/// 최요환
/// 2021.02.25
/// </summary>


class Sign : public Gimmick
{
public:
	Sign(float spawnPosX = 300.0f, float spawnPosY = 300.0f, string str = "Statue");
	~Sign();


	// 초기화
	virtual void Initialize(const float spawnPosX, const float spawnPosY) override;

	// 업데이트
	virtual void Update() override;

	// 충돌처리
	virtual void Collision() override;


protected:

private:
	float m_WaitTime = 0.0f;

public:
	Sprite* m_SignSprite;
	Sprite* m_ContentsSprite;
	ImageUI* m_SignUI;
};

