#pragma once
/// <summary>
/// ǥ���� Ŭ����
/// �ʿ� ������ ǥ������ �ִ�.
/// ǥ���ǿ� �ٰ����� ȭ�鿡 ������ ��Ʈ�� ǥ�õȴ�.(UI)
/// 
/// �ֿ�ȯ
/// 2021.02.25
/// </summary>


class Sign : public Gimmick
{
public:
	Sign(float spawnPosX = 300.0f, float spawnPosY = 300.0f, string str = "Statue");
	~Sign();


	// �ʱ�ȭ
	virtual void Initialize(const float spawnPosX, const float spawnPosY) override;

	// ������Ʈ
	virtual void Update() override;

	// �浹ó��
	virtual void Collision() override;


protected:

private:
	float m_WaitTime = 0.0f;

public:
	Sprite* m_SignSprite;
	Sprite* m_ContentsSprite;
	ImageUI* m_SignUI;
};

