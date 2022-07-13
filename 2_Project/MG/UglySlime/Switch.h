#pragma once
/// <summary>
/// Switch Ŭ����
/// �÷��̾��� Ǯ�Ӽ� ���ݿ� ������
/// �ΰ��� ������ ��򰡿� ��ġ�ϴ� ���� ���� ��ġ�̴�.
/// 
/// ���ӳ����� �� 5���� ����ġ�� ��ġ�� ����
/// ������ ����ġ�� ����� ���� ����� �Ѵ�.
/// 
/// �ֿ�ȯ
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

	//����ġ �� ����
	void SetSwitchOn(const SwitchState val);

	// �� ����
	void SetDoor(Door* door);

	// �ʱ�ȭ
	virtual void Initialize(const float spawnPosX, const float spawnPosY);

	// ������Ʈ
	virtual void Update();

	// �浹 ���μ���
	virtual void Collision();

	// �ǰ�( �÷��̾�� ���ݴ����� �� )
	virtual void ReceiveAttack(Bullet* bulletObject);

	bool IsSwitchOn();

protected:

private:
	Door* m_Door;
	SwitchState m_SwitchState;	// ����ġ�� On �ΰ�?

	Sprite* m_Sprite[static_cast<int>(SwitchState::Max)];
};

