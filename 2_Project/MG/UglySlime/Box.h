#pragma once

/// <summary>
/// Box Ŭ����
/// Ŭ��� �ʿ��� ������ ���� �� �ִ�.
/// 
/// �÷��̾ �ͼ� ��ȣ�ۿ��ϸ� ������.
/// </summary>

enum class BoxState
{
	Closed,		// ���� ����
	Opening,	// ���� ��
	Opened,		// ���� ����
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

	// �ʱ�ȭ
	virtual void Initialize(const float spawnPosX, const float spawnPosY, const JewelryAttribute jewelry);

	virtual void Reset();

	// ������Ʈ
	virtual void Update();

	// �浹ó��
	virtual void Collision() override;

	// ���ڰ� �����ִ��� Ȯ��
	bool IsOpened();

	// ���ڸ� ���� �Լ�
	void OpenBox();

protected:

private:
	// �ִϸ��̼�
	Animation* m_Anim;

	BoxState m_BoxState;					// ������ ���� �Ǻ� ����
	JewelryAttribute m_JewelryAttribute;	// ���ڰ� ������ �ִ� ������ �Ӽ�

	float m_BoxOpenTime;					// �ڽ��� ������ �ð�(�ӵ�)
	float openTimer;						// Ÿ�̸�

};

